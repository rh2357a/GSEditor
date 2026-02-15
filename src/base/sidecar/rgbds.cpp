#include "rgbds.h"

#include "base/resources.h"
#include "base/sidecar/utils.h"

#include <filesystem>

void base::internal::InitializeRgbds()
{
    PrepareSidecar("rgbasm.exe", RES_ID_RGBASM);
    PrepareSidecar("rgblink.exe", RES_ID_RGBLINK);
    PrepareSidecar("rgbfix.exe", RES_ID_RGBFIX);
}

base::SidecarResult base::RunRgbasm(const std::string &args, const std::string &cwd)
{
    static const auto path = internal::GetSidecarDir() / "rgbasm.exe";
    return base::RunSidecar(path, args, cwd);
}

base::SidecarResult base::RunRgblink(const std::string &args, const std::string &cwd)
{
    static const auto path = internal::GetSidecarDir() / "rgblink.exe";
    return base::RunSidecar(path, args, cwd);
}

base::SidecarResult base::RunRgbfix(const std::string &args, const std::string &cwd)
{
    static const auto path = internal::GetSidecarDir() / "rgbfix.exe";
    return base::RunSidecar(path, args, cwd);
}
