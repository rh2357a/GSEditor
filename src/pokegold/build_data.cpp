#include "pokegold.h"

#include "lib/json.hpp"

#include <fstream>
#include <filesystem>

using json = nlohmann::json;

void pokegold::parse_build_data()
{
    data::assets.clear();
    data::scripts.clear();

    if (!is_rom_opened)
        return;

    const auto data_path = rom.build_data_path();
    if (!std::filesystem::exists(data_path))
    {
        debug_log("pokegold::parse_build_data", "build data does not exist(path={})", data_path.string());
        return;
    }

    debug_log("pokegold::parse_build_data", "read build data (path={})", data_path.string());
    std::ifstream ifs(data_path, std::ios::binary);
    std::vector<std::uint8_t> bson((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    json data = json::from_bson(bson);

    debug_log("pokegold::parse_build_data", "assets size={}", data["assets"].size());
    for (const auto &e : data["assets"])
    {
        data::asset_info new_entry;
        new_entry.name = e.at("name").get<std::string>();
        new_entry.description = e.at("description").get<std::string>();
        new_entry.data = bytes(e.at("data").get_binary());
        data::assets.push_back(new_entry);
    }

    debug_log("pokegold::parse_build_data", "scripts size={}", data["scripts"].size());
    for (const auto &e : data["scripts"])
    {
        data::script_info new_entry;
        new_entry.name = e.at("name").get<std::string>();
        new_entry.description = e.at("description").get<std::string>();
        new_entry.script = e.at("script").get<std::string>();
        data::scripts.push_back(new_entry);
    }
}

void pokegold::save_build_data()
{
    if (!is_rom_opened)
        return;

    // 스크립트, 에셋이 비어있으면 설정을 저장 x
    if (data::assets.empty() && data::scripts.empty())
        return;

    auto data = json::object();
    data["assets"] = json::array();
    data["scripts"] = json::array();

    for (const auto &e : data::assets)
    {
        auto new_entry = json::object();
        new_entry["name"] = e.name;
        new_entry["description"] = e.description;
        new_entry["data"] = json::binary(e.data);
        data["assets"].push_back(new_entry);
    }

    for (const auto &e : data::scripts)
    {
        auto new_entry = json::object();
        new_entry["name"] = e.name;
        new_entry["description"] = e.description;
        new_entry["data"] = e.script;
        data["scripts"].push_back(new_entry);
    }

    const auto data_path = rom.build_data_path();
    debug_log("pokegold::save_build_data", "write build data (path={})", data_path.string());

    const auto bson = json::to_bson(data);
    std::ofstream ofs(rom.build_data_path(), std::ios::binary);
    ofs.write(reinterpret_cast<const char *>(bson.data()), bson.size());
}
