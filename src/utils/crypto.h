#ifndef _UTILS_CRYPTO_H_
#define _UTILS_CRYPTO_H_

#include <xxhash.h>

#include <iomanip>
#include <sstream>
#include <vector>

namespace utils::crypto {

/// @brief 파일 해시 계산
/// @param input
/// @return 문자열 형식 해시
inline std::string hash(const std::vector<u8> &input)
{
    size_t length = input.size();
    XXH128_hash_t hash = XXH3_128bits(input.data(), length);

    std::ostringstream oss;
    oss << std::hex << std::setfill('0')
        << std::setw(16) << hash.high64
        << std::setw(16) << hash.low64;

    return oss.str();
}

/// @brief 문자열 해시 계산
/// @param input 문자열
/// @return 문자열 형식 해시
inline std::string hash(const std::string &input)
{
    size_t length = input.size();
    XXH128_hash_t hash = XXH3_128bits(input.data(), length);

    std::ostringstream oss;
    oss << std::hex << std::setfill('0')
        << std::setw(16) << hash.high64
        << std::setw(16) << hash.low64;

    return oss.str();
}

} // namespace utils::crypto

#endif
