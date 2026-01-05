#ifndef _POKEGOLD_H_
#define _POKEGOLD_H_

#include "pokegold/address.h"
#include "pokegold/string.h"
#include "pokegold/data.h"
#include "pokegold/romfile.h"
#include "pokegold/config.h"

#include "lib/json.hpp"

#include <vector>
#include <filesystem>

namespace pokegold {

inline bool is_rom_opened = false;
inline pokegold::romfile rom;
inline std::filesystem::path workspace_path;

} // namespace pokegold

namespace pokegold {

/// @brief 롬 파일 열기
/// @param filepath 파일 경로
/// @return 로딩 문제 벡터
std::vector<data::bad_data> read(const std::filesystem::path &filepath);

/// @brief 롬 빌드
/// @return 빌드 바이너리
std::vector<u8> build();

} // namespace pokegold

#endif
