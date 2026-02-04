#pragma once

#include <filesystem>

namespace base
{
    /// @return 초기값 전용 경로
    std::filesystem::path GetNullPath();

    /// @return 앱 데이터 경로
    std::filesystem::path GetAppDataPath();

    /// @return 앱 데이터 경로 (구버전)
    std::filesystem::path GetAppLegacyDataPath();

    /// @brief 임시 파일 경로 생성, 디렉터리는 자동 생성됨
    /// @param key 문자열 키
    /// @return 생성된 임시 경로
    std::filesystem::path CreateTempFilePath(std::string_view key);
}
