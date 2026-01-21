#include "app_settings.h"

#include "lib/lzcomp.h"
#include "utils.h"
#include "lib/json.hpp"

#include <fstream>
#include <filesystem>

nlohmann::json app_settings_json;
std::filesystem::path app_setting_path = utils::files::get_app_data_path() / "app_settings.json";

void app_settings::init()
{
    if (std::filesystem::exists(app_setting_path))
    {
        try
        {
            std::ifstream f(app_setting_path);
            app_settings_json = nlohmann::json::parse(f);
            return;
        } catch (...)
        {}
    }

    app_settings_json = nlohmann::json::object();
}

void app_settings::write()
{
    std::filesystem::remove(app_setting_path);
    std::ofstream output(app_setting_path);
    output << std::setw(2) << app_settings_json << std::endl;
    output.close();
}

std::filesystem::path app_settings::get_emulator_path()
{
    const auto v = app_settings_json["emulator"];
    return v.is_null() ? "" : v.get<std::string>();
}

void app_settings::set_emulator_path(const std::filesystem::path &path)
{
    app_settings_json["emulator"] = path.string();
    emulator_path_changed.emit(path);
}
