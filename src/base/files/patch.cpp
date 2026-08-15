#include "patch.h"

#include "base/files/file_util.h"

#include <xdelta3_wrapper.h>

#include <algorithm>
#include <filesystem>

namespace
{
    void AppendIpsRecord(std::vector<u8> &result, int offset, const std::vector<u8> &data)
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
            bool isRlePossible = std::all_of(data.begin(), data.end(), [&](u8 b) { return b == data[0]; });
            if (isRlePossible && data.size() > 2)
            {
                result.push_back(0);
                result.push_back(0);

                u16 rle_count = static_cast<u16>(data.size());
                result.push_back((rle_count >> 8) & 0xff);
                result.push_back(rle_count & 0xff);
                result.push_back(data[0]);
            }
            else
            {
                u16 size = static_cast<u16>(data.size());
                result.push_back((size >> 8) & 0xff);
                result.push_back(size & 0xff);
                result.insert(result.end(), data.begin(), data.end());
            }
        }
    }
}

base::CreatePatchResult base::CreateIpsPatch(const std::filesystem::path &writeToPath, const std::filesystem::path &originalPath, const std::filesystem::path &modifiedPath)
{
    if (!std::filesystem::exists(originalPath))
        return CreatePatchResult::OriginalFileNotFound;

    if (!std::filesystem::exists(modifiedPath))
        return CreatePatchResult::ModifiedFileNotFound;

    auto originalBytes = base::ReadBytesFromFile(originalPath);
    auto modifiedBytes = base::ReadBytesFromFile(modifiedPath);

    int originalLength = static_cast<int>(originalBytes.size());
    int modifiedLength = static_cast<int>(modifiedBytes.size());
    if (originalLength < modifiedLength)
        return CreatePatchResult::ReadFailure;

    std::vector<u8> result;
    result.push_back('P');
    result.push_back('A');
    result.push_back('T');
    result.push_back('C');
    result.push_back('H');

    int i = 0;
    while (i < std::min(originalLength, modifiedLength))
    {
        if (originalBytes[i] != modifiedBytes[i])
        {
            int start = i;
            std::vector<u8> diff_data;

            while (i < std::min(originalLength, modifiedLength) && originalBytes[i] != modifiedBytes[i])
            {
                diff_data.push_back(modifiedBytes[i]);
                ++i;
            }

            AppendIpsRecord(result, start, diff_data);
        }
        else
        {
            i++;
        }
    }

    if (modifiedLength > originalLength)
    {
        std::vector<u8> tail(modifiedBytes.begin() + originalLength, modifiedBytes.end());
        AppendIpsRecord(result, originalLength, tail);
    }

    result.push_back('E');
    result.push_back('O');
    result.push_back('F');

    if (!base::WriteBytesToFile(writeToPath, result))
        return CreatePatchResult::WriteFailure;

    return CreatePatchResult::Successful;
}

base::CreatePatchResult base::CreateDeltaPatch(const std::filesystem::path &writeToPath, const std::filesystem::path &originalPath, const std::filesystem::path &modifiedPath)
{
    if (!std::filesystem::exists(originalPath))
        return CreatePatchResult::OriginalFileNotFound;

    if (!std::filesystem::exists(modifiedPath))
        return CreatePatchResult::ModifiedFileNotFound;

    int xdeltaResult = xd3_main_exec({"-e", "-n", "-s", originalPath.string(), modifiedPath.string(), writeToPath.string()});
    if (xdeltaResult != 0)
        return CreatePatchResult::WriteFailure;

    return CreatePatchResult::Successful;
}
