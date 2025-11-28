#include "romfile.h"
#include "utils.h"

pokegold::romfile::romfile(std::filesystem::path filepath) : m_path(std::move(filepath))
{
    const auto bytes = utils::files::read_bytes_from_file(m_path);
    m_bytes.insert(m_bytes.end(), bytes.begin(), bytes.end());
}

void pokegold::romfile::read_bytes(std::vector<uint8_t> &bytes, size_t addr, size_t len)
{
    if (len == 0 || addr >= m_bytes.size() || len > m_bytes.size() - addr)
        return;

    std::copy(m_bytes.begin() + addr, m_bytes.begin() + addr + len, bytes.begin());
}

uint8_t pokegold::romfile::get_byte(size_t addr)
{
    return m_bytes[addr];
}

pokegold::bytes pokegold::romfile::get_bytes(size_t addr, size_t len)
{
    if (len == 0 || addr >= m_bytes.size() || len > m_bytes.size() - addr)
        return {};

    std::vector<uint8_t> result;
    for (size_t i = 0; i < len; i++)
        result.push_back(m_bytes[addr + i]);

    return result;
}

pokegold::bytes pokegold::romfile::get_bytes_until(size_t addr, std::function<bool(size_t, uint8_t)> predicate, bool include_end)
{
    if (addr >= m_bytes.size())
        return {};

    std::vector<uint8_t> result;
    size_t i = 0;
    while (true)
    {
        uint8_t b = m_bytes[addr + i];
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

void pokegold::romfile::set_byte(size_t addr, uint8_t byte)
{
    m_bytes[addr] = byte;
}

void pokegold::romfile::set_bytes(size_t addr, const std::vector<uint8_t> &bytes)
{
    if (addr >= m_bytes.size() || bytes.size() > m_bytes.size() - addr)
        return;

    for (size_t i = 0; i < bytes.size(); i++)
        m_bytes[addr + i] = bytes[i];
}

void pokegold::romfile::fill_bytes(uint8_t byte, size_t addr, size_t len)
{
    if (addr >= m_bytes.size() || len > m_bytes.size() - addr)
        return;

    for (size_t i = 0; i < len; i++)
        m_bytes[addr + i] = byte;
}
