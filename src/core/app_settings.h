#ifndef _CORE_APP_SETTINGS_H_
#define _CORE_APP_SETTINGS_H_

#include "core/event.h"
#include <filesystem>

namespace core::app_settings {

void init();
void write();

inline core::event<std::filesystem::path> emulator_path_changed;

std::filesystem::path get_emulator_path();
void set_emulator_path(const std::filesystem::path &path);

} // namespace core::app_settings

#endif
