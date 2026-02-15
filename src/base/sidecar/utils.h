#pragma once

#include <windows.h>

#include <filesystem>
#include <string>

namespace base::internal
{
    /**
     * @brief sidecar 바이너리 디렉터리 경로
     *
     * @return std::filesystem::path&
     */
    const std::filesystem::path &GetSidecarDir();

    /**
     * @brief sidecar 바이너리 구성
     *
     * @param name 바이너리 파일명
     * @param resId RCDATA 리소스 ID
     */
    void PrepareSidecar(const std::string &name, int resId);
}
