#include "lzcomp.h"

extern "C"
{
#include "proto.h"
}

namespace
{
    unsigned short get_compressed_size(const unsigned char *data, unsigned short *size)
    {
        const unsigned char *rp = data;
        const unsigned char *end = data + *size;

        while (1)
        {
            if (rp >= end)
                return 0;

            unsigned cmd = *rp >> 5;
            unsigned count = *(rp++) & 31;

            if (cmd == 7)
            {
                cmd = count >> 2;
                count = (count & 3) << 8;

                if (cmd == 7)
                {
                    if (count == 0x300)
                        break;
                    return 0;
                }

                if (rp >= end)
                    return 0;
                count |= *(rp++);
            }

            count++;

            switch (cmd)
            {
            case 0:
                if (rp + count > end)
                    return 0;
                rp += count;
                break;
            case 1:
            case 2:
                if (rp + cmd > end)
                    return 0;
                rp += cmd;
                break;
            case 3:
                break;
            default:
                if (rp >= end)
                    return 0;
                if (*rp & 128)
                    rp++;
                else
                {
                    if (rp + 2 > end)
                        return 0;
                    rp += 2;
                }
                break;
            }
        }

        return rp - data;
    }

    unsigned short write_uncompressed_data(unsigned char *result, const struct command *commands, const unsigned char *compressed, unsigned short *size, unsigned short maxsize)
    {
        const struct command *limit = commands + *size;
        unsigned char *current = result;
        unsigned short p;
        for (; commands < limit; commands++)
        {
            switch (commands->command)
            {
            case 0:
                if (((current - result) + commands->count) > maxsize)
                {
                    *size = 0;
                    return 0;
                }
                memcpy(current, compressed + commands->value, commands->count);
                current += commands->count;
                break;
            case 1:
            case 2:
                if (((current - result) + commands->count) > maxsize)
                {
                    *size = 0;
                    return 0;
                }
                for (p = 0; p < commands->count; p++)
                    *(current++) = commands->value >> ((p % commands->command) << 3);
                break;
            case 3:
                if (((current - result) + commands->count) > maxsize)
                {
                    *size = 0;
                    return 0;
                }
                memset(current, 0, commands->count);
                current += commands->count;
                break;
            default:
                {
                    if (((current - result) + commands->count) > maxsize)
                    {
                        *size = 0;
                        return 0;
                    }
                    const unsigned char *ref = ((commands->value < 0) ? current : result) + commands->value;
                    for (p = 0; p < commands->count; p++)
                    {
                        current[p] = ref[(commands->command == 6) ? -(int)p : p];
                        if (commands->command == 5)
                            current[p] = bit_flipping_table[current[p]];
                    }
                    current += commands->count;
                }
            }
            if ((current - result) > maxsize)
            {
                *size = 0;
                return 0;
            }
        }
        *size = current - result;
        return *size;
    }

    unsigned char *write_command_to_buffer(unsigned char *buffer, struct command command, const unsigned char *input_stream)
    {
        if ((!command.count) || (command.count > MAX_COMMAND_COUNT))
            error_exit(2, "invalid command in output stream");
        unsigned char buf[4];
        unsigned char *pos = buf;
        int n;
        command.count--;
        if (command.count < SHORT_COMMAND_COUNT)
            *(pos++) = (command.command << 5) + command.count;
        else
        {
            *(pos++) = 224 + (command.command << 2) + (command.count >> 8);
            *(pos++) = command.count;
        }
        switch (command.command)
        {
        case 1:
        case 2:
            if ((command.value < 0) || (command.value >= (1 << (command.command << 3))))
                error_exit(2, "invalid command in output stream");
            for (n = 0; n < command.command; n++)
                *(pos++) = command.value >> (n << 3);
        case 0:
        case 3:
            break;
        default:
            if ((command.value < -LOOKBACK_LIMIT) || (command.value >= MAX_FILE_SIZE))
                error_exit(2, "invalid command in output stream");
            if (command.value < 0)
                *(pos++) = command.value ^ 127;
            else
            {
                *(pos++) = command.value >> 8;
                *(pos++) = command.value;
            }
        }
        size_t len = (size_t)(pos - buf);
        memcpy(buffer, buf, len);
        buffer += len;
        if (command.command)
            return buffer;
        command.count++;
        memcpy(buffer, input_stream + command.value, command.count);
        buffer += command.count;
        return buffer;
    }

    size_t write_commands_to_buffer(unsigned char *buffer, const struct command *commands, unsigned count, const unsigned char *input_stream, unsigned char alignment)
    {
        unsigned char *current = buffer;
        unsigned length = 0;
        while (count--)
        {
            current = write_command_to_buffer(current, *commands, input_stream);
            length += command_size(*(commands++));
        }
        *current = 0xff;
        current++;
        length = ~length & ((1 << alignment) - 1);
        while (length--)
        {
            *current = 0;
            current++;
        }
        return current - buffer;
    }

    struct command *compress_internal(const unsigned char *data, unsigned short *size, unsigned method)
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
}

size_t lzcomp::ScanLzDataSize(std::span<const u8> src)
{
    unsigned short size = static_cast<unsigned short>(src.size());
    return get_compressed_size(src.data(), &size);
}

size_t lzcomp::Compress(std::span<u8> dst, std::span<const u8> src)
{
    unsigned short size = src.size();

    struct command *commands = compress_internal(src.data(), &size, 0 /* singlepass */);
    // struct command *commands = CompressInternal(src.data(), &size, 80 /* multipass */);
    size_t lz_size = write_commands_to_buffer(dst.data(), commands, size, src.data(), 0);
    free(commands);

    return lz_size;
}

size_t lzcomp::Uncompress(std::span<u8> dst, std::span<const u8> src)
{
    unsigned short size = static_cast<unsigned short>(src.size());
    unsigned short originalSize = size;

    struct command *commands = get_commands_from_file(src.data(), &size, nullptr);
    if (commands == nullptr)
        return 0;

    write_uncompressed_data(dst.data(), commands, src.data(), &size, originalSize);
    free(commands);

    return size > originalSize ? 0 : size;
}
