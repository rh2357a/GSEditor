#include "paths.h"

#include "base/resources.h"
#include "base/strings/crypto.h"

#include <shlobj.h>
#include <windows.h>

std::filesystem::path base::GetAppDataPath()
{
    static const std::filesystem::path pathImpl = [] {
        PWSTR path = nullptr;
        ::SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &path);

        std::filesystem::path result(path);
        ::CoTaskMemFree(path);

        result = result / APP_NAME;
        return result;
    }();
    return pathImpl;
}

std::filesystem::path base::GetAppLegacyDataPath()
{
    static const std::filesystem::path pathImpl = [] {
        PWSTR path = nullptr;
        ::SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path);

        std::filesystem::path result(path);
        ::CoTaskMemFree(path);

        result /= APP_NAME;
        return result;
    }();
    return pathImpl;
}

std::filesystem::path base::CreateTempFilePath(std::string_view key)
{
    static const auto tempDir = GetAppDataPath() / "tmp";
    std::filesystem::create_directories(tempDir);
    return tempDir / base::Hash(key);
}
