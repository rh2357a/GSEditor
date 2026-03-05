#pragma once

#include "base/types/types.h"

#include <span>
#include <string>
#include <vector>

namespace pokegold
{
    /**
     * @brief 빈 공간의 주소 범위
     */
    struct FreeSpaceRange
    {
        size_t From;
        size_t To;
    };

    /**
     * @brief 데이터 블록
     */
    struct FreeSpaceDataBlock
    {
        std::string Label;
        std::vector<u8> Data;
    };

    /**
     * @brief 빈 공간에 해당하는 데이터 블록 목록
     */
    struct DataBlocksEntry
    {
        FreeSpaceRange FreeSpaceRange;
        std::vector<FreeSpaceDataBlock> DataBlocks;
    };

    /**
     * @brief 빈 공간 데이터 입력 클래스
     */
    class FreeSpaceDataResolver
    {
    private:
        std::vector<FreeSpaceDataBlock> m_dataBlocks;

    public:
        /**
         * @brief 데이터 추가
         *
         * @param label 라벨
         * @param data 바이너리 데이터
         */
        void Push(std::string label, std::span<const u8> data);

        /**
         * @brief 입력된 모든 데이터를 빈 공간에 알맞게 처리
         *
         * @param freeSpaceRanges 빈 공간의 범위 벡터
         * @return 정리된 데이터 블록 모음
         */
        std::vector<DataBlocksEntry> Resolve(const std::vector<FreeSpaceRange> &freeSpaceRanges);
    };
}
