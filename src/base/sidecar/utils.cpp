#include "utils.h"

#include "base/files/file_util.h"
#include "base/files/paths.h"
#include "base/sidecar/utils.h"
#include "base/strings/crypto.h"
#include "base/types/types.h"

#include <filesystem>
#include <vector>

namespace
{
    std::vector<u8> GetRcDataByResId(int resId)
    {
        const auto module = ::GetModuleHandle(nullptr);

        const auto res = ::FindResource(module, MAKEINTRESOURCE(resId), RT_RCDATA);
        const auto resData = ::LoadResource(module, res);
        const auto resSize = ::SizeofResource(module, res);

        const u8 *data = static_cast<const u8 *>(::LockResource(resData));
        return std::vector<u8>(data, data + resSize);
    }

    const std::filesystem::path k_binDir = [] {
        auto binDir = base::GetAppDataPath() / "bin";
        std::filesystem::create_directories(binDir);
        return binDir;
    }();
}

const std::filesystem::path &base::internal::GetSidecarDir()
{
    return k_binDir;
}

void base::internal::PrepareSidecar(const std::string &name, int resId)
{
    const auto exePath = k_binDir / name;
    const auto binBytes = GetRcDataByResId(resId);

    if (std::filesystem::exists(exePath))
    {
        const auto currentBinBytes = base::ReadBytesFromFile(exePath);
        const auto hash = base::Hash(binBytes);
        const auto currentBinHash = base::Hash(currentBinBytes);
        if (currentBinHash != hash)
        {
            std::filesystem::remove(exePath);
            base::WriteBytesToFile(exePath, binBytes);
        }
    }
    else
    {
        base::WriteBytesToFile(exePath, binBytes);
    }
}
