#include "lzcomp.h"

extern "C" {
#include "lib/lzcomp/proto.h"
}

u8 comp_buffer[0x400];
u8 uncomp_buffer[0x400];

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

size_t lzcomp::scan_lz_size(const std::vector<u8> &src)
{
    unsigned short size = static_cast<unsigned short>(src.size());
    return get_compressed_size(src.data(), &size);
}

std::vector<u8> lzcomp::compress(const std::vector<u8> &src)
{
    unsigned short size = static_cast<unsigned short>(src.size());

    // 80: multipass
    struct command *commands = lzcomp_compress(src.data(), &size, 80);
    size_t lz_size = write_commands_to_buffer(comp_buffer, commands, size, src.data(), 0);
    free(commands);

    std::vector<u8> result(std::begin(comp_buffer), std::end(comp_buffer));
    result.resize(lz_size);
    return result;
}

std::vector<u8> lzcomp::uncompress(const std::vector<u8> &src)
{
    unsigned short size = static_cast<unsigned short>(src.size());
    unsigned short original_size = size, remainder;

    struct command *commands = get_commands_from_file(src.data(), &size, &remainder);
    write_uncompressed_data(uncomp_buffer, commands, src.data(), &size);
    free(commands);

    std::vector<u8> result(std::begin(uncomp_buffer), std::end(uncomp_buffer));
    result.resize(size);
    return result;
}
