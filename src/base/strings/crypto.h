#pragma once

#include "base/types/types.h"

#include <span>
#include <string>

namespace base
{
    /// @brief 파일 해시 계산
    /// @param input
    /// @return 문자열 형식 해시
    std::string Hash(std::span<const u8> input);

    /// @brief 문자열 해시 계산
    /// @param input 문자열
    /// @return 문자열 형식 해시
    std::string Hash(std::string_view input);
}
