#ifndef _POKEGOLD_CONFIG_H_
#define _POKEGOLD_CONFIG_H_

#include <string>
#include <vector>

namespace pokegold::config {

class asset_info
{
public:
    std::string name;
    std::string description;
    std::vector<u8> data;
};

class script_info
{
public:
    std::string name;
    std::string description;
    std::string script;
};

} // namespace pokegold::config

namespace pokegold::config {

inline std::vector<asset_info> assets;
inline std::vector<script_info> scripts;

inline std::string emulator_path = "";

void close();

void read();
void write();

} // namespace pokegold::config

#endif
