#pragma once

#include "base/types/types.h"

#include <cstdint>
#include <span>

namespace lzcomp
{
    /// @brief 버퍼에 있는 압축 데이터의 길이 계산
    /// @param src 압축된 데이터
    /// @return 압축 데이터의 길이
    size_t GetLzSize(std::span<const u8> src);

    /// @brief 데이터 압축
    /// @param dst 압축될 바이트 배열 버퍼
    /// @param src 원본 바이트 배열
    /// @return 압축된 길이, 실패 시 0을 반환
    size_t Compress(std::span<u8> dst, std::span<const u8> src);

    /// @brief 데이터 압축 해제
    /// @param dst 압축 해제될 바이트 배열 버퍼
    /// @param src 압축 바이트 배열
    /// @return 압축 해제된 길이, 실패 시 0을 반환
    size_t Uncompress(std::span<u8> dst, std::span<const u8> src);
}
