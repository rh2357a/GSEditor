#include "file_util.h"

constexpr size_t CHUNK_SIZE = 16 * 1024 * 1024;

std::vector<u8> base::ReadBytesFromFile(const std::filesystem::path &path)
{
    size_t length = std::filesystem::file_size(path);
    std::ifstream file(path, std::ios::binary);
    if (!file)
        return {};

    std::vector<u8> buffer(length);
    size_t remaining = length;
    size_t offset = 0;

    while (remaining > 0)
    {
        std::streamsize chunk = static_cast<std::streamsize>(std::min<size_t>(remaining, CHUNK_SIZE));
        file.read(reinterpret_cast<char *>(buffer.data() + offset), chunk);
        std::streamsize read_count = file.gcount();
        offset += read_count;
        remaining -= read_count;

        if (read_count == 0)
            break;
    }

    buffer.resize(offset);
    return buffer;
}

bool base::WriteBytesToFile(const std::filesystem::path &path, std::span<const u8> bytes)
{
    std::ofstream output(path, std::ios::binary);
    if (!output)
        return false;

    size_t remaining = bytes.size();
    size_t offset = 0;

    while (remaining > 0)
    {
        std::streamsize chunk = static_cast<std::streamsize>(std::min<size_t>(remaining, CHUNK_SIZE));
        output.write(reinterpret_cast<const char *>(bytes.data() + offset), chunk);
        if (!output)
            return false;

        offset += chunk;
        remaining -= chunk;
    }

    output.flush();
    return output.good();
}
