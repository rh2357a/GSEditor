#pragma once

#include "base/types/types.h"

#include <filesystem>
#include <span>
#include <vector>

namespace base
{
    /// @brief 파일에서 바이트 배열을 읽기
    /// @param path 경로
    /// @return 바이트 배열, 실패 시 비어있는 벡터 반환
    std::vector<u8> ReadBytesFromFile(const std::filesystem::path &path);

    /// @brief 바이트 배열을 파일에 기록
    /// @param path 기록 경로
    /// @param bytes 바이트 배열
    /// @return 성공 유무
    bool WriteBytesToFile(const std::filesystem::path &path, std::span<const u8> bytes);
}
