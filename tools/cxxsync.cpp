/// cxxsync: `compile_commands.json`을 자동으로 관리

#include "../src/lib/argparse.hpp"
#include "../src/lib/json.hpp"

#include <windows.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <format>
#include <unordered_set>

namespace utils {

std::string strip_quotes(const std::string &s)
{
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
        return s.substr(1, s.size() - 2);
    return s;
}

std::string to_string(const std::wstring &wstr)
{
    if (wstr.empty())
        return std::string();

    int size = ::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    if (size <= 0)
        return std::string();

    std::string str(size - 1, 0);
    ::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size, NULL, NULL);

    return str;
}

std::wstring to_wstring(const std::string &str)
{
    if (str.empty())
        return std::wstring();

    int size = ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    if (size <= 0)
        return std::wstring();

    std::wstring wstr(size - 1, 0);
    ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size);

    return wstr;
}

std::string replace_all(std::string s, const std::string &from, const std::string &to)
{
    if (from.empty())
        return s;

    size_t pos = 0;
    while ((pos = s.find(from, pos)) != std::string::npos)
    {
        s.replace(pos, from.length(), to);
        pos += to.length();
    }

    return s;
}

std::vector<std::string> split(const std::string &str, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter))
        result.push_back(item);

    return result;
}

} // namespace utils

int main(int argc, char *argv[])
{
    // std::cout .imbue(std::locale(""));
    ::SetConsoleOutputCP(CP_UTF8);

    std::ios::sync_with_stdio(false);

    argparse::ArgumentParser parser("cxxsync");
    parser.add_argument("--toolchain-includes").nargs(argparse::nargs_pattern::any);
    parser.add_argument("--cxx");
    parser.add_argument("--cc");
    parser.add_argument("--cxx-flags");
    parser.add_argument("--cc-flags");
    parser.add_argument("--output-dir");
    parser.add_argument("--workspace-dir");
    parser.parse_known_args(argc, argv);

    auto cxx = parser.get<std::string>("--cxx");
    auto cc = parser.get<std::string>("--cc");

    auto cxxflags = utils::strip_quotes(parser.get<std::string>("--cxx-flags"));
    auto ccflags = utils::strip_quotes(parser.get<std::string>("--cc-flags"));
    for (const auto &path : parser.get<std::vector<std::string>>("--toolchain-includes"))
    {
        cxxflags += " -I" + path;
        ccflags += " -I" + path;
    }

    auto output_dir = utils::replace_all(parser.get<std::string>("--output-dir"), "/", "\\");
    auto workdir = parser.get<std::string>("--workspace-dir");

    std::vector<std::string> cxx_std_flags, cc_std_flags;
    std::vector<std::string> include_flags;
    std::vector<std::string> include_files;
    std::vector<std::string> defines;

    std::vector<std::string> tokens = utils::split(ccflags, ' ');
    for (size_t i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].rfind("-std=", 0) == 0)
            cc_std_flags.push_back(tokens[i].substr(5));
    }

    tokens = utils::split(cxxflags, ' ');
    for (size_t i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].rfind("-std=", 0) == 0)
        {
            cxx_std_flags.push_back(tokens[i].substr(5));
        }
        else if (tokens[i] == "-I")
        {
            if (i + 1 < tokens.size())
                include_flags.push_back(tokens[i + 1]);
            i++;
        }
        else if (tokens[i].rfind("-I", 0) == 0)
        {
            include_flags.push_back(tokens[i].substr(2));
        }
        else if (tokens[i] == "-include")
        {
            if (i + 1 < tokens.size())
                include_files.push_back(tokens[i + 1]);
            i++;
        }
        else if (tokens[i].rfind("-D", 0) == 0)
        {
            defines.push_back(tokens[i].substr(2));
        }
    }

    // std::cout
    //     << "$(CC): " << cc << '\n'
    //     << "$(CXX): " << cxx << '\n'
    //     << "$(CXXFLAGS): " << cxxflags << '\n'
    //     << "$(CCFLAGS): " << ccflags << '\n'
    //     << "output_dir: " << output_dir << '\n'
    //     << "workspace: " << workdir << '\n'
    //     << '\n';

    HANDLE workdir_handle = ::CreateFileW(
        utils::to_wstring(workdir).c_str(),
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
        nullptr);

    char buffer[1024 * 64];
    DWORD changed_return;
    std::cout << "cxxsync start." << std::endl;

    std::unordered_set<std::string> files;
    auto scan_sources = [&](const std::filesystem::path &dir) {
        for (auto &entry : std::filesystem::recursive_directory_iterator(dir))
        {
            if (entry.is_regular_file())
            {
                auto path = entry.path();
                if (path.extension() == ".cpp" || path.extension() == ".c")
                {
                    auto filepath = path.string();
                    files.insert(filepath);
                }
            }
        }
    };
    scan_sources(workdir);

    bool need_update_output = true;
    while (true)
    {
        if (need_update_output)
        {
            // c_cpp_properties.json
            {
                nlohmann::json output_json = nlohmann::json::object();
                output_json["version"] = 4;
                output_json["configurations"] = nlohmann::json::array();

                nlohmann::json new_config = nlohmann::json::object();
                new_config["name"] = "C/C++";
                new_config["compileCommands"] = (std::filesystem::path(output_dir) / "compile_commands.json").string();
                new_config["compilerPath"] = cxx;
                new_config["intelliSenseMode"] = "windows-gcc-x64";

                new_config["forcedInclude"] = nlohmann::json::array();
                for (const auto &e : include_files)
                    new_config["forcedInclude"].push_back(e);

                new_config["includePath"] = nlohmann::json::array();
                for (const auto &e : include_flags)
                    new_config["includePath"].push_back(e);

                new_config["defines"] = nlohmann::json::array();
                for (const auto &e : defines)
                    new_config["defines"].push_back(e);

                if (!cc_std_flags.empty())
                    new_config["cStandard"] = cc_std_flags[0];
                if (!cxx_std_flags.empty())
                    new_config["cppStandard"] = cxx_std_flags[0];

                output_json["configurations"].push_back(new_config);

                std::ofstream output(std::filesystem::path(output_dir) / "c_cpp_properties.json");
                output << output_json.dump(2);
                output.close();
            }

            // compile_commands.json
            {
                nlohmann::json output_json = nlohmann::json::array();
                for (const auto &e : files)
                {
                    auto new_entry = nlohmann::json::object();
                    new_entry["directory"] = workdir;
                    new_entry["file"] = e;
                    new_entry["command"] = (e.ends_with(".cpp") ? cxx + " " + cxxflags : cc + " " + ccflags);
                    output_json.push_back(new_entry);
                }

                std::ofstream output(std::filesystem::path(output_dir) / "compile_commands.json");
                output << output_json.dump(2);
                output.close();
            }

            need_update_output = false;
        }

        const auto is_error = !::ReadDirectoryChangesW(
            workdir_handle,
            buffer,
            sizeof(buffer),
            true,
            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
            &changed_return,
            nullptr,
            nullptr);

        if (is_error)
        {
            std::cerr << "ReadDirectoryChangesW failed." << std::endl;
            ::CloseHandle(workdir_handle);
            return -1;
        }

        auto *info = reinterpret_cast<FILE_NOTIFY_INFORMATION *>(buffer);
        do
        {
            std::string filename = utils::to_string(std::wstring(info->FileName, info->FileName + info->FileNameLength / sizeof(WCHAR)));

            if ((filename.ends_with("c_cpp_properties.json") || filename.ends_with("compile_commands.json")) && (info->Action == FILE_ACTION_REMOVED || info->Action == FILE_ACTION_RENAMED_OLD_NAME))
            {
                std::cout << "Removed: " << filename << std::endl;
                need_update_output = true;
            }
            else if (filename.ends_with(".c") || filename.ends_with(".cpp"))
            {
                switch (info->Action)
                {
                case FILE_ACTION_MODIFIED:
                    std::cout << "Modified: " << filename << std::endl;
                    need_update_output = true;
                    break;

                case FILE_ACTION_ADDED:
                case FILE_ACTION_RENAMED_NEW_NAME:
                    std::cout << "Added: " << filename << std::endl;
                    files.insert((std::filesystem::path(workdir) / filename).string());
                    need_update_output = true;
                    break;
                case FILE_ACTION_REMOVED:
                case FILE_ACTION_RENAMED_OLD_NAME:
                    std::cout << "Removed: " << filename << std::endl;
                    files.erase((std::filesystem::path(workdir) / filename).string());
                    need_update_output = true;
                    break;
                }
            }

            if (info->NextEntryOffset == 0)
                break;

            info = reinterpret_cast<FILE_NOTIFY_INFORMATION *>(reinterpret_cast<char *>(info) + info->NextEntryOffset);
        } while (true);
    }

    ::CloseHandle(workdir_handle);
    return 0;
}
