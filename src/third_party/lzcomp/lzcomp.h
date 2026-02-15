#pragma once

#include "base/types/types.h"

#include <span>

namespace lzcomp
{
    /**
     * @brief 압축 데이터 길이 구하기
     *
     * @param src 압축 데이터 버퍼
     * @return size_t 결과
     */
    size_t ScanLzDataSize(std::span<const u8> src);

    /**
     * @brief 바이트 배열 압축
     *
     * @param dst 결과 버퍼
     * @param src 입력 버퍼
     * @return size_t 압축된 길이
     * @return 0 실패
     */
    size_t Compress(std::span<u8> dst, std::span<const u8> src);

    /**
     * @brief 바이트 배열 압축 해제
     *
     * @param dst 결과 버퍼
     * @param src 입력 버퍼
     * @return size_t 압축 해제 길이
     * @return 0 실패
     */
    size_t Uncompress(std::span<u8> dst, std::span<const u8> src);
}
