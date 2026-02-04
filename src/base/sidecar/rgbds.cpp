#include "rgbds.h"

void base::internal::InitializeRgbds()
{
}

base::SidecarResult base::RunRgbasm(const std::string &args, const std::string &cwd)
{
    return base::RunSidecar("", args, cwd);
}

base::SidecarResult base::RunRgblink(const std::string &args, const std::string &cwd)
{
    return base::RunSidecar("", args, cwd);
}

base::SidecarResult base::RunRgbfix(const std::string &args, const std::string &cwd)
{
    return base::RunSidecar("", args, cwd);
}
