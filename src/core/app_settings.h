#ifndef _CORE_APP_SETTINGS_H_
#define _CORE_APP_SETTINGS_H_

#include "utils.h"
#include <filesystem>

namespace app_settings {

void init();
void write();

inline utils::event<std::filesystem::path> emulator_path_changed;

std::filesystem::path get_emulator_path();
void set_emulator_path(const std::filesystem::path &path);

} // namespace app_settings

#endif
