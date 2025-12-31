#ifndef _UTILS_H_
#define _UTILS_H_

#include "utils/crypto.h"
#include "utils/files.h"
#include "utils/patch.h"
#include "utils/strings.h"
#include "utils/exec.h"

#include <vector>
#include <span>

namespace utils {

/// @brief 바이트 배열 검사
/// @param data 원본 바이트 배열
/// @param index 검사 위치
/// @param find_bytes 검사 바이트
/// @return 일치 유무
inline bool match_bytes(std::span<const u8> data, size_t index, const std::vector<u8> &find_bytes)
{
    if (index + find_bytes.size() > data.size())
        return false;

    for (size_t j = 0; j < find_bytes.size(); j++)
    {
        if (data[index + j] != find_bytes[j])
            return false;
    }

    return true;
}

} // namespace utils

#endif
