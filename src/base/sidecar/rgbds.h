#pragma once

#include "base/sidecar/sidecar.h"

namespace base
{
    /**
     * @brief rgbds 어셈블러 실행
     *
     * @param args 인자값
     * @param cwd 작업 경로
     * @return SidecarResult
     */
    SidecarResult RunRgbasm(const std::string &args, const std::string &cwd);

    /**
     * @brief rgbds 링커 실행
     *
     * @param args 인자값
     * @param cwd 작업 경로
     * @return SidecarResult
     */
    SidecarResult RunRgblink(const std::string &args, const std::string &cwd);

    /**
     * @brief rgbds fixer 실행
     *
     * @param args 인자값
     * @param cwd 작업 경로
     * @return SidecarResult
     */
    SidecarResult RunRgbfix(const std::string &args, const std::string &cwd);

    namespace internal
    {
        void InitializeRgbds();
    }
}
