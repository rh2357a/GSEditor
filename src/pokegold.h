#ifndef _POKEGOLD_H_
#define _POKEGOLD_H_

#include "pokegold/address.h"
#include "pokegold/string.h"
#include "pokegold/data.h"
#include "pokegold/romfile.h"
#include "pokegold/config.h"
#include "pokegold/event.h"

#include "utils.h"
#include "lib/json.hpp"

#include <vector>
#include <filesystem>

namespace pokegold {

/// @brief 롬 파일 열기
/// @param filepath 파일 경로
/// @return 로딩 문제 벡터
std::vector<data::bad_data> open(const std::filesystem::path &filepath);

/// @brief 롬 파일 닫기
void close();

/// @brief 롬 빌드
/// @return 빌드된 롬 파일 경로
std::filesystem::path build();

} // namespace pokegold

#endif
