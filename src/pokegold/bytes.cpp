#include "bytes.h"

#include "utils.h"
#include "embed.h"

#include <filesystem>
#include <charconv>
#include <format>
#include <sstream>
#include <array>
#include <unordered_map>

std::unordered_map<uint16_t, std::string_view> charmap;
std::unordered_map<std::string_view, uint16_t> charmap_reverse;

std::filesystem::path lzcomp_src_path = utils::files::create_temp_file_path("lzcomp_src");
std::filesystem::path lzcomp_dst_path = utils::files::create_temp_file_path("lzcomp_dst");

// clang-format off

const std::array<uint8_t, 256> BIT_REVERSED{
    0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0, 0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
    0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8, 0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
    0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4, 0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
    0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec, 0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
    0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2, 0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
    0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea, 0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
    0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6, 0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
    0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee, 0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
    0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1, 0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
    0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9, 0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
    0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5, 0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
    0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed, 0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
    0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3, 0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
    0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb, 0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
    0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7, 0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
    0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef, 0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
};

// clang-format on

pokegold::bytes::bytes(const std::string &str)
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
                    m_bytes.push_back(static_cast<uint8_t>((code & 0xff00) >> 8));
                    m_bytes.push_back(static_cast<uint8_t>(code & 0x00ff));
                }
                else
                {
                    m_bytes.push_back(static_cast<uint8_t>(code));
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
                        m_bytes.push_back(static_cast<uint8_t>(value));
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

pokegold::bytes::bytes(std::vector<uint8_t> bytes) : m_bytes(std::move(bytes))
{
#ifdef DEBUG
    // 디버그 변수 미리보기용 강제 호출
    string();
#endif
}

void pokegold::bytes::init_charmap()
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

        uint16_t code = 0;
        const auto conv_result = std::from_chars(val.data(), val.data() + val.size(), code, 16);
        if (conv_result.ec != std::errc{})
            continue;

        charmap[code] = ch;
        charmap_reverse[ch] = code;
    }
}

bool pokegold::bytes::is_charmap_string(const std::string &str)
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

            std::string ch = str.substr(i, j + 1);

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
                    std::string hex = ch.substr(1, ch.size() - 2);
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

std::string pokegold::bytes::string()
{
    if (m_cached_str != s_unk_string)
        return m_cached_str;

    std::stringstream ss;

    for (size_t i = 0; i < m_bytes.size(); i++)
    {
        uint8_t b = m_bytes[i];

        // 한글
        if (b >= 1 && b <= 0xb)
        {
            if (i + 1 >= m_bytes.size())
                return m_cached_str = s_unk_string;

            uint16_t char_id = (m_bytes[i] << 8) | m_bytes[i + 1];
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

void pokegold::bytes::setup_lzcomp_workdir(const std::filesystem::path &dir)
{
    const auto tmp_dir = dir / "tmp";
    std::filesystem::create_directories(tmp_dir);

    lzcomp_src_path = tmp_dir / utils::crypto::hash("lzcomp_src");
    lzcomp_dst_path = tmp_dir / utils::crypto::hash("lzcomp_dst");
}

bool pokegold::bytes::is_lz_compressed(const std::vector<uint8_t> &bytes)
{
    size_t index = 0;
    while (index < bytes.size())
    {
        uint8_t cmd = bytes[index++];
        if (cmd == 0xff)
            return true;

        uint8_t type = cmd & 0xe0;
        uint16_t length = cmd & 0x1f;

    extended_cmd:
        switch (type)
        {
        case 0x00:
            index += length + 1;
            break;

        case 0x20:
            index += 1;
            break;

        case 0x40:
            index += 2;
            break;

        case 0x60:
            break;

        case 0x80:
        case 0xa0:
        case 0xc0: {
            uint8_t offset = bytes[index++];
            if ((offset & 0x80) == 0)
                index++;
            break;
        }

        case 0xe0: {
            cmd = (cmd & 0x1c) * 8;
            type = cmd & 0xe0;
            length = (length & 0x03) * 0x100 + bytes[index++];
            goto extended_cmd;
        }

        default:
            return false;
        }
    }

    return false;
}

size_t pokegold::bytes::scan_lz_size(const std::vector<uint8_t> &bytes)
{
    size_t index = 0;
    while (index < bytes.size())
    {
        uint8_t cmd = bytes[index++];
        if (cmd == 0xff)
            return index;

        uint8_t type = cmd & 0xe0;
        uint16_t length = cmd & 0x1f;

    extended_cmd:
        switch (type)
        {
        case 0x00:
            index += length + 1;
            break;

        case 0x20:
            index += 1;
            break;

        case 0x40:
            index += 2;
            break;

        case 0x60:
            break;

        case 0x80:
        case 0xa0:
        case 0xc0: {
            uint8_t offset = bytes[index++];
            if ((offset & 0x80) == 0)
                index++;
            break;
        }

        case 0xe0: {
            cmd = (cmd & 0x1c) * 8;
            type = cmd & 0xe0;
            length = (length & 0x03) * 0x100 + bytes[index++];
            goto extended_cmd;
        }

        default:
            return 0;
        }
    }

    return 0;
}

pokegold::bytes pokegold::bytes::compressed() const
{
    // std::filesystem::remove(lzcomp_src_path);
    // std::filesystem::remove(lzcomp_dst_path);

    utils::files::write_bytes_to_file(lzcomp_src_path, m_bytes);

    const auto args = std::format("--compressor multipass {} {}", lzcomp_src_path.string(), lzcomp_dst_path.string());
    utils::lzcomp(args);

    const auto result = utils::files::read_bytes_from_file(lzcomp_dst_path);

    // std::filesystem::remove(lzcomp_src_path);
    // std::filesystem::remove(lzcomp_dst_path);

    return result;
}

pokegold::bytes pokegold::bytes::decompressed() const
{
    std::vector<uint8_t> output;

    size_t index = 0;
    while (index < m_bytes.size())
    {
        uint8_t cmd = m_bytes[index++];
        if (cmd == 0xff)
            return output;

        uint8_t type = cmd & 0xe0;
        uint16_t length = cmd & 0x1f;

    extended_cmd:
        switch (type)
        {
        // 원본 복사
        case 0x00: {
            for (int i = 0; i < length + 1; ++i)
                output.push_back(m_bytes[index++]);
            break;
        }

        // 바이트 채우기
        case 0x20: {
            uint8_t b = m_bytes[index++];
            for (int i = 0; i < length + 1; ++i)
                output.push_back(b);
            break;
        }

        // 교차 반복 채우기
        case 0x40: {
            uint8_t first = m_bytes[index++];
            uint8_t second = m_bytes[index++];
            for (int i = 0; i < length + 1; ++i)
                output.push_back((i % 2 == 0) ? first : second);
            break;
        }

        // 0 채우기
        case 0x60: {
            for (int i = 0; i < length + 1; ++i)
                output.push_back(0);
            break;
        }

        // 이전 데이터 반복
        case 0x80: {
            uint8_t offset = m_bytes[index++];
            if ((offset & 0x80) == 0)
            {
                size_t real_offset = offset * 0x100 + m_bytes[index++] + 1;
                for (int i = 0; i < length + 1; ++i)
                    output.push_back(output[real_offset + i - 1]);
            }
            else
            {
                size_t back = (offset & 0x7f) + 1;
                for (int i = 0; i < length + 1; ++i)
                    output.push_back(output[output.size() - back - 1]);
            }
            break;
        }

        // 이전 데이터 반복 + 비트 반전
        case 0xa0: {
            uint8_t offset = m_bytes[index++];
            if ((offset & 0x80) == 0)
            {
                size_t real_offset = offset * 0x100 + m_bytes[index++] + 1;
                for (int i = 0; i < length + 1; ++i)
                    output.push_back(BIT_REVERSED[output[real_offset + i - 1]]);
            }
            else
            {
                size_t back = (offset & 0x7f) + 1;
                for (int i = 0; i < length + 1; ++i)
                    output.push_back(BIT_REVERSED[output[output.size() - back - 1]]);
            }
            break;
        }

        // 이전 데이터 역순 반복
        case 0xc0: {
            uint8_t offset = m_bytes[index++];
            size_t count = output.size();
            if ((offset & 0x80) == 0)
            {
                size_t real_offset = offset * 0x100 + m_bytes[index++] + 1;
                for (int i = 0; i < length + 1; ++i)
                    output.push_back(output[real_offset - i - 1]);
            }
            else
            {
                size_t back = offset & 0x7f;
                for (int i = 0; i < length + 1; ++i)
                    output.push_back(output[count - back - i - 1]);
            }
            break;
        }

        // 확장 명령
        case 0xe0: {
            cmd = (cmd & 0x1c) * 8;
            type = cmd & 0xe0;
            length = (length & 0x03) * 0x100 + m_bytes[index++];
            goto extended_cmd;
        }

        default:
            return {};
        }
    }

    return {};
}

pokegold::bytes pokegold::bytes::operator+(const bytes &rhs) const
{
    std::vector<uint8_t> new_bytes;
    new_bytes.reserve(m_bytes.size() + rhs.m_bytes.size());
    new_bytes.insert(new_bytes.end(), m_bytes.begin(), m_bytes.end());
    new_bytes.insert(new_bytes.end(), rhs.m_bytes.begin(), rhs.m_bytes.end());
    return pokegold::bytes(new_bytes);
}

pokegold::bytes &pokegold::bytes::operator+=(const bytes &rhs)
{
    m_bytes.insert(m_bytes.end(), rhs.m_bytes.begin(), rhs.m_bytes.end());
    m_cached_str = s_unk_string;
    string();
    return *this;
}
