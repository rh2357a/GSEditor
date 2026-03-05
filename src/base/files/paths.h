#pragma once

#include <filesystem>

namespace base
{
    /**
     * @brief 초기값 전용 경로
     *
     * @return std::filesystem::path
     *
     * TODO: `if (foo == base::GetNullPath())` > `if (foo == base::NullPath)`: getter 대신 constants 처럼 용도로 쓰이게 바꿀 것
     */
    std::filesystem::path GetNullPath();

    /**
     * @brief 앱 데이터 경로
     *
     * @return std::filesystem::path
     */
    std::filesystem::path GetAppDataPath();

    /**
     * @brief 앱 데이터 경로 (구버전)
     *
     * @return std::filesystem::path
     */
    std::filesystem::path GetAppLegacyDataPath();

    /**
     * @brief 임시 파일 경로 생성 (디렉터리는 자동 생성)
     *
     * @param key 임시 파일 키
     * @return std::filesystem::path 생성된 경로
     */
    std::filesystem::path CreateTempFilePath(std::string_view key);
}
