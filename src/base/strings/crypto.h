#pragma once

#include "base/types/types.h"

#include <span>
#include <string>

namespace base
{
    /**
     * @brief 해시값 계산
     *
     * @param input 바이트 배열
     * @return std::string 문자열 형태의 해시값
     */
    std::string Hash(std::span<const u8> input);

    /**
     * @brief 해시값 계산
     *
     * @param input 입력 문자열
     * @return std::string 문자열 형태의 해시값
     */
    std::string Hash(std::string_view input);
}
