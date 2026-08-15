#include "free_space.h"

#include <algorithm>
#include <functional>

void pokegold::FreeSpaceDataResolver::Push(std::string label, std::span<const u8> data)
{
    m_dataBlocks.push_back({
        label,
        {data.begin(), data.end()},
    });
}

std::vector<pokegold::DataBlocksEntry> pokegold::FreeSpaceDataResolver::Resolve(const std::vector<FreeSpaceRange> &freeSpaceRanges)
{
    std::vector<pokegold::DataBlocksEntry> result(freeSpaceRanges.size());
    for (size_t i = 0; i < freeSpaceRanges.size(); i++)
    {
        const auto &e = freeSpaceRanges[i];
        result[i].FreeSpaceRange = e;
    }

    std::vector<size_t> currentOffsets;
    {
        for (const auto &e : freeSpaceRanges)
            currentOffsets.push_back(e.From);
    }

    std::vector<std::reference_wrapper<FreeSpaceDataBlock>> sortedDataBlocks;
    {
        for (auto &e : m_dataBlocks)
            sortedDataBlocks.push_back(e);

        std::sort(
            sortedDataBlocks.begin(),
            sortedDataBlocks.end(),
            [&](const FreeSpaceDataBlock &a, const FreeSpaceDataBlock &b) {
                return a.Data.size() > b.Data.size();
            });
    }

    for (const auto &label : sortedDataBlocks)
    {
        size_t size = label.get().Data.size();
        for (size_t j = 0; j < freeSpaceRanges.size(); j++)
        {
            if (currentOffsets[j] + size < freeSpaceRanges[j].To)
            {
                result[j].DataBlocks.push_back(label.get());
                currentOffsets[j] += size;
                break;
            }
        }
    }

    return result;
}
