#include "lzcomp.h"

extern "C" {
#include "lib/lzcomp/proto.h"
}

#include <array>
#include <vector>

struct command *lzcomp_compress(const unsigned char *data, unsigned short *size, unsigned method)
{
    unsigned char *bitflipped = (unsigned char *)malloc(*size);
    unsigned current;
    for (current = 0; current < *size; current++)
        bitflipped[current] = bit_flipping_table[data[current]];
    const struct compressor *compressor = compressors;
    struct command *result;
    if (method < COMPRESSION_METHODS)
    {
        while (method >= compressor->methods)
            method -= (compressor++)->methods;
        result = compressor->function(data, bitflipped, size, method);
    }
    else
    {
        struct command *compressed_sequences[COMPRESSION_METHODS];
        unsigned short lengths[COMPRESSION_METHODS];
        unsigned flags = 0;
        for (current = 0; current < COMPRESSION_METHODS; current++)
        {
            lengths[current] = *size;
            if (flags == compressor->methods)
            {
                flags = 0;
                compressor++;
            }
            compressed_sequences[current] = compressor->function(data, bitflipped, lengths + current, flags++);
        }
        result = select_optimal_sequence(compressed_sequences, lengths, size);
        for (current = 0; current < COMPRESSION_METHODS; current++)
            free(compressed_sequences[current]);
    }
    free(bitflipped);
    return result;
}

size_t lzcomp::scan_lz_size(std::span<const u8> src)
{
    unsigned short size = static_cast<unsigned short>(src.size());
    return get_compressed_size(src.data(), &size);
}

size_t lzcomp::compress(std::span<u8> dst, std::span<const u8> src)
{
    unsigned short size = src.size();

    struct command *commands = lzcomp_compress(src.data(), &size, 0 /* singlepass */);
    // struct command *commands = lzcomp_compress(src.data(), &size, 80 /* multipass */);
    size_t lz_size = write_commands_to_buffer(dst.data(), commands, size, src.data(), 0);
    free(commands);

    return lz_size;
}

size_t lzcomp::uncompress(std::span<u8> dst, std::span<const u8> src, size_t src_offset, size_t src_size)
{
    unsigned short size = static_cast<unsigned short>(src_size);
    unsigned short original_size = size, remainder;

    struct command *commands = get_commands_from_file(src.data() + src_offset, &size, &remainder);
    write_uncompressed_data(dst.data(), commands, src.data() + src_offset, &size);
    free(commands);

    return size;
}
