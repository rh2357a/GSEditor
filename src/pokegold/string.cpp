#include "string.h"

#include "lib/lzcomp.h"
#include "utils.h"
#include "embed.h"

#include <filesystem>
#include <charconv>
#include <format>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>

std::unordered_map<u16, std::string_view> charmap;
std::unordered_map<std::string_view, u16> charmap_reverse;

pokegold::string::string(const std::string &str)
{
    m_cached_str = str;

    for (size_t i = 0; i < str.size();)
    {
        size_t current_len = 0;
        bool matched = false;

        for (size_t j = 0; j < 16; ++j)
        {
            current_len++;
            if (i + j >= str.size())
                return;

            std::string ch = str.substr(i, j + 1);

            auto it = charmap_reverse.find(ch);
            if (it != charmap_reverse.end())
            {
                int code = it->second;
                if (code > 255)
                {
                    m_bytes.push_back(static_cast<u8>((code & 0xff00) >> 8));
                    m_bytes.push_back(static_cast<u8>(code & 0x00ff));
                }
                else
                {
                    m_bytes.push_back(static_cast<u8>(code));
                }

                matched = true;
                break;
            }

            if (!ch.empty() && ch.front() == '[' && ch.back() == ']')
            {
                try
                {
                    std::string hex = ch.substr(1, ch.size() - 2);
                    int value = std::stoi(hex, nullptr, 16);
                    if (value <= 255)
                    {
                        m_bytes.push_back(static_cast<u8>(value));
                        matched = true;
                        break;
                    }
                    else
                    {
                        return;
                    }
                } catch (...)
                {
                    return;
                }
            }
        }

        if (!matched)
            return;

        i += current_len;
    }
}

pokegold::string::string(std::vector<u8> bytes) : m_bytes(std::move(bytes))
{
    if constexpr (DEBUG_MODE)
        u8string();
}

void pokegold::string::init_charmap()
{
    charmap.clear();

    std::string_view sv(reinterpret_cast<const char *>(embed::charmap_txt.data()), embed::charmap_txt.size());
    for (size_t pos = 0; pos < sv.size();)
    {
        size_t end = sv.find('\n', pos);
        if (end == std::string_view::npos)
            end = sv.size();

        std::string_view line = sv.substr(pos, end - pos);
        pos = end + 1;

        auto eq = line.find('=');
        if (eq == std::string_view::npos)
            continue;

        std::string_view val = line.substr(0, eq);
        std::string_view ch = line.substr(eq + 1);

        u16 code = 0;
        const auto conv_result = std::from_chars(val.data(), val.data() + val.size(), code, 16);
        if (conv_result.ec != std::errc{})
            continue;

        charmap[code] = ch;
        charmap_reverse[ch] = code;
    }
}

bool pokegold::string::is_charmap_string(std::string_view str)
{
    for (size_t i = 0; i < str.size();)
    {
        size_t current_len = 0;
        bool matched = false;

        for (size_t j = 0; j < 16; ++j)
        {
            current_len++;
            if (i + j >= str.size())
                return false;

            const auto ch = str.substr(i, j + 1);

            auto it = charmap_reverse.find(ch);
            if (it != charmap_reverse.end())
            {
                matched = true;
                break;
            }

            if (!ch.empty() && ch.front() == '[' && ch.back() == ']')
            {
                try
                {
                    const std::string hex(ch.substr(1, ch.size() - 2));
                    int value = std::stoi(hex, nullptr, 16);
                    if (value <= 255)
                    {
                        matched = true;
                        break;
                    }
                    else
                    {
                        return false;
                    }
                } catch (...)
                {
                    return false;
                }
            }
        }

        if (!matched)
            return false;

        i += current_len;
    }

    return true;
}

std::string pokegold::string::u8string()
{
    if (m_cached_str != s_unk_string)
        return m_cached_str;

    std::stringstream ss;

    for (size_t i = 0; i < m_bytes.size(); i++)
    {
        u8 b = m_bytes[i];

        // 한글
        if (b >= 1 && b <= 0xb)
        {
            if (i + 1 >= m_bytes.size())
                return m_cached_str = s_unk_string;

            u16 char_id = (m_bytes[i] << 8) | m_bytes[i + 1];
            ss << charmap[char_id];
            i++;
            continue;
        }

        // 영숫자 + 특수 문자
        if (charmap.contains(b))
        {
            ss << charmap[b];
            continue;
        }

        // hex
        ss << '[' << std::format("{:x}", b) << ']';
    }

    return m_cached_str = ss.str();
}

pokegold::string pokegold::string::operator+(const string &rhs) const
{
    std::vector<u8> new_bytes;
    new_bytes.reserve(m_bytes.size() + rhs.m_bytes.size());
    new_bytes.insert(new_bytes.end(), m_bytes.begin(), m_bytes.end());
    new_bytes.insert(new_bytes.end(), rhs.m_bytes.begin(), rhs.m_bytes.end());
    return pokegold::string(new_bytes);
}

pokegold::string &pokegold::string::operator+=(const string &rhs)
{
    m_bytes.insert(m_bytes.end(), rhs.m_bytes.begin(), rhs.m_bytes.end());
    m_cached_str = s_unk_string;

    if constexpr (DEBUG_MODE)
        u8string();

    return *this;
}
