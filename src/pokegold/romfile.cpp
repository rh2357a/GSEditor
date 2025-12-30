#include "romfile.h"

#include "lib/lzcomp.h"
#include "utils.h"

pokegold::romfile::romfile(std::filesystem::path filepath)
    : m_path(std::move(filepath)), m_build_data_path(m_path.parent_path() / (m_path.stem().string() + ".gsb"))
{
    const auto bytes = utils::files::read_bytes_from_file(m_path);
    m_bytes.insert(m_bytes.end(), bytes.begin(), bytes.end());
}

u8 pokegold::romfile::get_byte(size_t addr)
{
    return m_bytes[addr];
}

std::vector<u8> pokegold::romfile::get_bytes(size_t addr, size_t len)
{
    if (len == 0 || addr >= m_bytes.size() || len > m_bytes.size() - addr)
        return {};

    std::vector<u8> result;
    for (size_t i = 0; i < len; i++)
        result.push_back(m_bytes[addr + i]);

    return result;
}

std::vector<u8> pokegold::romfile::get_bytes_until(size_t addr, std::function<bool(size_t, u8)> predicate, bool include_end)
{
    if (addr >= m_bytes.size())
        return {};

    std::vector<u8> result;
    size_t i = 0;
    while (true)
    {
        u8 b = m_bytes[addr + i];
        if (predicate(i, b))
        {
            if (include_end)
                result.push_back(b);
            break;
        }

        result.push_back(b);
        i++;
    }

    return result;
}

size_t pokegold::romfile::calc_lz_size(size_t offset, size_t buffer_size)
{
    std::span<const u8> buf(m_bytes.data() + offset, buffer_size);
    return lzcomp::scan_lz_size(buf);
}

size_t pokegold::romfile::read_lz_decompressed(std::span<u8> dst, size_t offset, size_t size)
{
    return lzcomp::uncompress(dst, m_bytes, offset, size);
}

void pokegold::romfile::set_byte(size_t addr, u8 byte)
{
    m_bytes[addr] = byte;
}

void pokegold::romfile::set_bytes(size_t addr, std::span<const u8> bytes)
{
    if (addr >= m_bytes.size() || bytes.size() > m_bytes.size() - addr)
        return;

    for (size_t i = 0; i < bytes.size(); i++)
        m_bytes[addr + i] = bytes[i];
}

void pokegold::romfile::fill_bytes(u8 byte, size_t addr, size_t len)
{
    if (addr >= m_bytes.size() || len > m_bytes.size() - addr)
        return;

    for (size_t i = 0; i < len; i++)
        m_bytes[addr + i] = byte;
}
