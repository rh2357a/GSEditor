#include "../src/lib/json.hpp"
#include "../src/lib/argparse.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>

std::string strip_quotes(const std::string &s)
{
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
        return s.substr(1, s.size() - 2);
    return s;
}

int main(int argc, char *argv[])
{
    argparse::ArgumentParser parser("cpcmd");
    parser.add_argument("--sources").nargs(argparse::nargs_pattern::any);
    parser.add_argument("--toolchain-includes").nargs(argparse::nargs_pattern::any);
    parser.add_argument("--cxx").required();
    parser.add_argument("--cc").required();
    parser.add_argument("--cxx-flags").required();
    parser.add_argument("--cc-flags").required();
    parser.add_argument("--output").required();
    parser.add_argument("--workdir").required();
    parser.parse_args(argc, argv);

    auto cxx = parser.get<std::string>("--cxx");
    auto cc = parser.get<std::string>("--cc");
    auto cxxflags = strip_quotes(parser.get<std::string>("--cxx-flags"));
    auto ccflags = strip_quotes(parser.get<std::string>("--cc-flags"));

    for (const auto &path : parser.get<std::vector<std::string>>("--toolchain-includes"))
    {
        cxxflags += " -I" + path;
        ccflags += " -I" + path;
    }

    auto workdir = parser.get<std::string>("--workdir");

    auto output_json = nlohmann::json::array();
    for (const auto &src : parser.get<std::vector<std::string>>("--sources"))
    {
        auto new_entry = nlohmann::json::object();
        new_entry["directory"] = workdir;
        new_entry["file"] = src;
        new_entry["command"] = (src.ends_with(".cpp")
                                    ? cxx + " " + cxxflags
                                    : cc + " " + ccflags)
                               + " -c " + src;
        output_json.push_back(new_entry);
    }

    std::filesystem::path output_path(parser.get<std::string>("--output"));
    std::filesystem::remove(output_path);
    std::ofstream output(output_path);
    output << std::setw(2) << output_json << std::endl;
    output.close();

    return 0;
}
