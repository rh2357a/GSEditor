#include "patch.h"

#include "lib/xdelta3.h"
#include "utils.h"

#include <filesystem>
#include <algorithm>
#include <string>
#include <format>

void append_ips_record(std::vector<uint8_t> &result, int offset, const std::vector<uint8_t> &data)
{
    result.push_back((offset >> 16) & 0xff);
    result.push_back((offset >> 8) & 0xff);
    result.push_back(offset & 0xff);

    if (data.size() == 1)
    {
        result.push_back(0);
        result.push_back(1);
        result.push_back(data[0]);
    }
    else
    {
        bool rle_possible = std::all_of(data.begin(), data.end(), [&](uint8_t b) { return b == data[0]; });
        if (rle_possible && data.size() > 2)
        {
            // RLE 레코드
            result.push_back(0);
            result.push_back(0);
            uint16_t rle_count = static_cast<uint16_t>(data.size());
            result.push_back((rle_count >> 8) & 0xff);
            result.push_back(rle_count & 0xff);
            result.push_back(data[0]);
        }
        else
        {
            // 일반 레코드
            uint16_t size = static_cast<uint16_t>(data.size());
            result.push_back((size >> 8) & 0xff);
            result.push_back(size & 0xff);
            result.insert(result.end(), data.begin(), data.end());
        }
    }
}

std::vector<uint8_t> utils::patch::create_ips_patch(std::span<const uint8_t> original_bytes, std::span<const uint8_t> modified_bytes)
{
    int original_len = static_cast<int>(original_bytes.size());
    int modified_len = static_cast<int>(modified_bytes.size());
    if (original_len < modified_len)
        return {};

    std::vector<uint8_t> result;
    result.push_back('P');
    result.push_back('A');
    result.push_back('T');
    result.push_back('C');
    result.push_back('H');

    int i = 0;
    while (i < std::min(original_len, modified_len))
    {
        if (original_bytes[i] != modified_bytes[i])
        {
            int start = i;
            std::vector<uint8_t> diff_data;

            while (i < std::min(original_len, modified_len) && original_bytes[i] != modified_bytes[i])
            {
                diff_data.push_back(modified_bytes[i]);
                ++i;
            }

            append_ips_record(result, start, diff_data);
        }
        else
        {
            i++;
        }
    }

    if (modified_len > original_len)
    {
        std::vector<uint8_t> tail(modified_bytes.begin() + original_len, modified_bytes.end());
        append_ips_record(result, original_len, tail);
    }

    result.push_back('E');
    result.push_back('O');
    result.push_back('F');

    return result;
}

std::vector<uint8_t> utils::patch::create_xdelta_patch(std::span<const uint8_t> original_bytes, std::span<const uint8_t> modified_bytes)
{
    using namespace std;
    using namespace utils;

    const auto original_path = files::create_temp_file_path("xdelta_original");
    // filesystem::remove(original_path);
    files::write_bytes_to_file(original_path, original_bytes);

    const auto modified_path = files::create_temp_file_path("xdelta_modified");
    // filesystem::remove(modified_path);
    files::write_bytes_to_file(modified_path, modified_bytes);

    const auto xdelta_path = files::create_temp_file_path("xdelta_result");
    xdelta3::exec({"-e", "-n", "-s", original_path.string(), modified_path.string(), xdelta_path.string()});

    const auto result = files::read_bytes_from_file(xdelta_path);

    // filesystem::remove(original_path);
    // filesystem::remove(modified_path);
    // filesystem::remove(xdelta_path);

    return result;
}
