#ifndef _CORE_PATCH_H_
#define _CORE_PATCH_H_

#include <cstdint>
#include <span>
#include <vector>

namespace gs::core::patch {

/// @brief IPS 패치 생성
/// @param original_bytes 원본 데이터
/// @param modified_bytes 변경 데이터
/// @return IPS 데이터
std::vector<uint8_t> create_ips_patch(std::span<const uint8_t> original_bytes, std::span<const uint8_t> modified_bytes);

/// @brief xdelta3 패치 생성
/// @param original_bytes 원본 데이터
/// @param modified_bytes 변경 데이터
/// @return xdelta3 데이터
std::vector<uint8_t> create_xdelta_patch(std::span<const uint8_t> original_bytes, std::span<const uint8_t> modified_bytes);

} // namespace gs::core::patch

#endif
