#include "pokegold.h"

#include "lib/json.hpp"

#include <fstream>
#include <filesystem>
#include "config.h"

using json = nlohmann::json;

void pokegold::config::close()
{
    assets.clear();
    scripts.clear();
}

void pokegold::config::read()
{
    assets.clear();
    scripts.clear();

    if (!romfile::is_opened)
        return;

    const auto data_path = romfile::build_data_path;
    if (!std::filesystem::exists(data_path))
    {
        debug_log("pokegold::parse_build_data", "build data does not exist(path={})", data_path.string());
        return;
    }

    try
    {
        debug_log("pokegold::parse_build_data", "read build data (path={})", data_path.string());
        std::ifstream ifs(data_path, std::ios::binary);
        std::vector<std::uint8_t> bson((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        json data = json::from_bson(bson);

        debug_log("pokegold::parse_build_data", "assets size={}", data["assets"].size());
        for (const auto &e : data["assets"])
        {
            asset_info new_entry;
            new_entry.name = e.at("name").get<std::string>();
            new_entry.description = e.at("description").get<std::string>();
            new_entry.data = e.at("data").get_binary();
            assets.push_back(new_entry);
        }

        debug_log("pokegold::parse_build_data", "scripts size={}", data["scripts"].size());
        for (const auto &e : data["scripts"])
        {
            script_info new_entry;
            new_entry.name = e.at("name").get<std::string>();
            new_entry.description = e.at("description").get<std::string>();
            new_entry.script = e.at("script").get<std::string>();
            scripts.push_back(new_entry);
        }
    } catch (...)
    {
        assets.clear();
        scripts.clear();
    }
}

void pokegold::config::write()
{
    if (!romfile::is_opened)
        return;

    auto data = json::object();
    data["assets"] = json::array();
    data["scripts"] = json::array();

    for (const auto &e : assets)
    {
        auto new_entry = json::object();
        new_entry["name"] = e.name;
        new_entry["description"] = e.description;
        new_entry["data"] = json::binary(e.data);
        data["assets"].push_back(new_entry);
    }

    for (const auto &e : scripts)
    {
        auto new_entry = json::object();
        new_entry["name"] = e.name;
        new_entry["description"] = e.description;
        new_entry["data"] = e.script;
        data["scripts"].push_back(new_entry);
    }

    const auto data_path = romfile::build_data_path;
    debug_log("pokegold::save_build_data", "write build data (path={})", data_path.string());

    const auto bson = json::to_bson(data);
    std::ofstream ofs(romfile::build_data_path, std::ios::binary);
    ofs.write(reinterpret_cast<const char *>(bson.data()), bson.size());
}
