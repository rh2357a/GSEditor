#include <argparse/argparse.hpp>
#include <json/json.hpp>
#include <windows.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

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

int main(int argc, char *argv[])
{
    ::SetConsoleOutputCP(CP_UTF8);
    std::ios::sync_with_stdio(false);

    argparse::ArgumentParser parser("config-updater");
    parser.add_argument("--cxx");
    parser.add_argument("--cc");
    parser.add_argument("--cxx-flags");
    parser.add_argument("--cc-flags");
    parser.add_argument("--output-dir");
    parser.add_argument("--workspace-dir");
    parser.parse_known_args(argc, argv);

    auto cxx = parser.get<std::string>("--cxx");
    auto cc = parser.get<std::string>("--cc");

    auto cxxflags = strip_quotes(parser.get<std::string>("--cxx-flags"));
    auto ccflags = strip_quotes(parser.get<std::string>("--cc-flags"));
    auto outputDir = replace_all(parser.get<std::string>("--output-dir"), "/", "\\");
    auto workDir = parser.get<std::string>("--workspace-dir");

    std::vector<std::string> cxxStdFlags, ccStdFlags;
    std::vector<std::string> includeFlags;
    std::vector<std::string> includeFiles;
    std::vector<std::string> defines;

    std::vector<std::string> tokens = split(ccflags, ' ');
    for (size_t i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].rfind("-std=", 0) == 0)
            ccStdFlags.push_back(tokens[i].substr(5));
    }

    tokens = split(cxxflags, ' ');
    for (size_t i = 0; i < tokens.size(); i++)
    {
        if (tokens[i].rfind("-std=", 0) == 0)
        {
            cxxStdFlags.push_back(tokens[i].substr(5));
        }
        else if (tokens[i] == "-I")
        {
            if (i + 1 < tokens.size())
                includeFlags.push_back(tokens[i + 1]);
            i++;
        }
        else if (tokens[i].rfind("-I", 0) == 0)
        {
            includeFlags.push_back(tokens[i].substr(2));
        }
        else if (tokens[i] == "-include")
        {
            if (i + 1 < tokens.size())
                includeFiles.push_back(tokens[i + 1]);
            i++;
        }
        else if (tokens[i].rfind("-D", 0) == 0)
        {
            defines.push_back(tokens[i].substr(2));
        }
    }

    if constexpr (false)
    {
        std::cout
            << "$(CC): " << cc << '\n'
            << "$(CXX): " << cxx << '\n'
            << "$(CXXFLAGS): " << cxxflags << '\n'
            << "$(CCFLAGS): " << ccflags << '\n'
            << "outputDir: " << outputDir << '\n'
            << "workspace: " << workDir << '\n'
            << '\n';
    }

    HANDLE workDirHandle = ::CreateFileW(
        to_wstring(workDir).c_str(),
        FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        nullptr,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
        nullptr);

    char buffer[1024 * 64];
    DWORD changedReturn;
    std::cout << "source-watcher start." << std::endl;

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
    scan_sources(workDir);

    bool needUpdateOutput = true;
    while (true)
    {
        if (needUpdateOutput)
        {
            nlohmann::json outputJson = nlohmann::json::array();
            for (const auto &e : files)
            {
                auto newEntry = nlohmann::json::object();
                newEntry["directory"] = workDir;
                newEntry["file"] = e;
                newEntry["command"] = (e.ends_with(".cpp") ? cxx + " " + cxxflags : cc + " " + ccflags);
                outputJson.push_back(newEntry);
            }

            std::ofstream output(std::filesystem::path(outputDir) / "compile_commands.json");
            output << outputJson.dump(2);
            output.close();

            needUpdateOutput = false;
        }

        const auto isError = !::ReadDirectoryChangesW(
            workDirHandle,
            buffer,
            sizeof(buffer),
            true,
            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_LAST_WRITE,
            &changedReturn,
            nullptr,
            nullptr);

        if (isError)
        {
            std::cerr << "ReadDirectoryChangesW failed." << std::endl;
            ::CloseHandle(workDirHandle);
            return -1;
        }

        auto *info = reinterpret_cast<FILE_NOTIFY_INFORMATION *>(buffer);
        do
        {
            std::string filename = to_string(std::wstring(info->FileName, info->FileNameLength / sizeof(WCHAR)));
            if ((filename.ends_with("c_cpp_properties.json") || filename.ends_with("compile_commands.json")) && (info->Action == FILE_ACTION_REMOVED || info->Action == FILE_ACTION_RENAMED_OLD_NAME))
            {
                std::cout << "Removed: " << filename << std::endl;
                needUpdateOutput = true;
            }
            else if (filename.ends_with(".h") || filename.ends_with(".hpp"))
            {
                std::cout << "Modified: " << filename << std::endl;
                needUpdateOutput = true;
            }
            else if (filename.ends_with(".c") || filename.ends_with(".cpp"))
            {
                switch (info->Action)
                {
                case FILE_ACTION_MODIFIED:
                    std::cout << "Modified: " << filename << std::endl;
                    needUpdateOutput = true;
                    break;

                case FILE_ACTION_ADDED:
                case FILE_ACTION_RENAMED_NEW_NAME:
                    std::cout << "Added: " << filename << std::endl;
                    files.insert((std::filesystem::path(workDir) / filename).string());
                    needUpdateOutput = true;
                    break;

                case FILE_ACTION_REMOVED:
                case FILE_ACTION_RENAMED_OLD_NAME:
                    std::cout << "Removed: " << filename << std::endl;
                    files.erase((std::filesystem::path(workDir) / filename).string());
                    needUpdateOutput = true;
                    break;
                }
            }

            if (info->NextEntryOffset == 0)
                break;

            info = reinterpret_cast<FILE_NOTIFY_INFORMATION *>(reinterpret_cast<char *>(info) + info->NextEntryOffset);
        } while (true);
    }

    ::CloseHandle(workDirHandle);
    return 0;
}
