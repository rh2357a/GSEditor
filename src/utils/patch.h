#ifndef _UTILS_PATCH_H_
#define _UTILS_PATCH_H_

#include <span>
#include <vector>

namespace utils::patch {

/// @brief IPS 패치 생성
/// @param original_bytes 원본 데이터
/// @param modified_bytes 변경 데이터
/// @return IPS 데이터
std::vector<u8> create_ips_patch(std::span<const u8> original_bytes, std::span<const u8> modified_bytes);

/// @brief xdelta3 패치 생성
/// @param original_bytes 원본 데이터
/// @param modified_bytes 변경 데이터
/// @return xdelta3 데이터
std::vector<u8> create_xdelta_patch(std::span<const u8> original_bytes, std::span<const u8> modified_bytes);

} // namespace utils::patch

#endif
