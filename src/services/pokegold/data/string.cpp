#include "string.h"

#include "resources.h"

#include <charconv>
#include <unordered_map>

namespace
{
    std::unordered_map<u16, std::string_view> Charmap;
    std::unordered_map<std::string_view, u16> CharmapReverse;
}

pokegold::String::String(const std::string &str)
{
    for (size_t i = 0; i < str.size();)
    {
        size_t currentLength = 0;
        bool matched = false;

        for (size_t j = 0; j < 16; ++j)
        {
            currentLength++;
            if (i + j >= str.size())
                return;

            std::string ch = str.substr(i, j + 1);

            auto it = CharmapReverse.find(ch);
            if (it != CharmapReverse.end())
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

            if (ch == "\n")
            {
                m_bytes.push_back(0x59);
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

        i += currentLength;
    }

#ifdef DEBUG
    ToEditorString();
#endif
}

pokegold::String::String(std::span<const u8> bytes)
{
    m_bytes.insert(m_bytes.end(), bytes.begin(), bytes.end());

#ifdef DEBUG
    ToEditorString();
#endif
}

void pokegold::String::InitializeCharmap()
{
    Charmap.clear();

    const auto &charmapList = embed::GetPokegoldCharmapList();
    std::string_view sv(reinterpret_cast<const char *>(charmapList.data()), charmapList.size());
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
        const auto convResult = std::from_chars(val.data(), val.data() + val.size(), code, 16);
        if (convResult.ec != std::errc{})
            continue;

        Charmap[code] = ch;
        CharmapReverse[ch] = code;
    }
}

bool pokegold::String::IsCharmapString(std::string_view str)
{
    for (size_t i = 0; i < str.size();)
    {
        size_t currentLength = 0;
        bool matched = false;

        for (size_t j = 0; j < 16; ++j)
        {
            currentLength++;
            if (i + j >= str.size())
                return false;

            const auto ch = str.substr(i, j + 1);

            auto it = CharmapReverse.find(ch);
            if (it != CharmapReverse.end())
            {
                matched = true;
                break;
            }

            if (ch == "\n")
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

        i += currentLength;
    }

    return true;
}

std::string pokegold::String::ToEditorString()
{
    if (m_cachedStr != s_unkString)
        return m_cachedStr;

    std::string result;
    result.reserve(m_bytes.size() * 3);

    for (size_t i = 0; i < m_bytes.size(); i++)
    {
        u8 b = m_bytes[i];

        if (b >= 1 && b <= 0x0b)
        {
            if (i + 1 >= m_bytes.size())
                return m_cachedStr = s_unkString;

            u16 char_id = (m_bytes[i] << 8) | m_bytes[i + 1];
            result += Charmap[char_id];
            i++;
            continue;
        }

        // 예외처리
        {
            if (b == 0x50)
                continue;

            if (b == 0x59)
            {
                result += '\n';
                continue;
            }
        }

        if (Charmap.contains(b))
        {
            result += Charmap[b];
            continue;
        }

        char buf[5];
        std::snprintf(buf, sizeof(buf), "[%02x]", b);
        result += buf;
    }

    return m_cachedStr = result;
}

wxString pokegold::String::ToEditorWxString()
{
    if (m_cachedWxStr != s_unkWxString)
        return m_cachedWxStr;
    return m_cachedWxStr = wxString::FromUTF8(ToEditorString());
}

bool pokegold::String::HasBadData() const
{
    for (size_t i = 0; i < m_bytes.size(); i++)
    {
        u8 b = m_bytes[i];

        // 한글
        if (b >= 1 && b <= 0xb)
        {
            if (i + 1 >= m_bytes.size())
                return true;
            i++;
            continue;
        }

        // 영숫자 + 특수 문자
        if (Charmap.contains(b))
            continue;

        // 예외처리
        if (b == 0x50 || b == 0x59)
            continue;

        return true;
    }

    return false;
}
