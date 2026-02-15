#pragma once

#include <filesystem>

namespace base
{
    enum class CreatePatchResult
    {
        Successful,
        OriginalFileNotFound,
        ModifiedFileNotFound,
        ReadFailure,
        WriteFailure,
    };

    /**
     * @brief IPS 패치 생성
     *
     * @param writeToPath 기록될 파일 경로
     * @param originalPath 원본 파일 경로
     * @param modifiedPath 변경 파일 경로
     * @return CreatePatchResult
     */
    CreatePatchResult CreateIpsPatch(const std::filesystem::path &writeToPath, const std::filesystem::path &originalPath, const std::filesystem::path &modifiedPath);

    /**
     * @brief xdelta3 패치 생성
     *
     * @param writeToPath 기록될 파일 경로
     * @param originalPath 원본 파일 경로
     * @param modifiedPath 변경 파일 경로
     * @return CreatePatchResult
     */
    CreatePatchResult CreateDeltaPatch(const std::filesystem::path &writeToPath, const std::filesystem::path &originalPath, const std::filesystem::path &modifiedPath);
}
