#ifndef _CORE_APP_SETTINGS_H_
#define _CORE_APP_SETTINGS_H_

#include <filesystem>

namespace app_settings {

void init();
void write();

std::filesystem::path get_emulator_path();
void set_emulator_path(const std::filesystem::path &path);

} // namespace app_settings

#endif
