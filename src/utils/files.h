#ifndef _UTILS_FILES_H_
#define _UTILS_FILES_H_

#include "crypto.h"

#include <shlobj.h>

#include <span>
#include <vector>
#include <fstream>
#include <filesystem>

namespace utils::files {

constexpr size_t CHUNK_SIZE = 16 * 1024 * 1024;

/// @brief 파일로부터 바이트 로딩
/// @param path 파일 경로
/// @param index 오프셋
/// @param length 길이
/// @return 바이트
inline std::vector<u8> read_bytes_from_file(const std::filesystem::path &path, size_t index, size_t length)
{
    std::ifstream file(path, std::ios::binary);
    if (!file)
        return {};

    size_t file_size = std::filesystem::file_size(path);
    if (index >= file_size)
        return {};

    if (index + length > file_size)
        length = file_size - index;

    file.seekg(index, std::ios::beg);

    std::vector<u8> buffer(length);
    size_t remaining = length;
    size_t offset = 0;

    while (remaining > 0)
    {
        std::streamsize chunk = static_cast<std::streamsize>(std::min<size_t>(remaining, CHUNK_SIZE));
        file.read(reinterpret_cast<char *>(buffer.data() + offset), chunk);
        std::streamsize read_count = file.gcount();
        offset += read_count;
        remaining -= read_count;

        if (read_count == 0)
            break;
    }

    buffer.resize(offset);
    return buffer;
}

/// @brief 파일로부터 바이트 로딩
/// @param path 파일 경로
/// @return 바이트
inline std::vector<u8> read_bytes_from_file(const std::filesystem::path &path)
{
    size_t length = std::filesystem::file_size(path);
    std::ifstream file(path, std::ios::binary);
    if (!file)
        return {};

    std::vector<u8> buffer(length);
    size_t remaining = length;
    size_t offset = 0;

    while (remaining > 0)
    {
        std::streamsize chunk = static_cast<std::streamsize>(std::min<size_t>(remaining, CHUNK_SIZE));
        file.read(reinterpret_cast<char *>(buffer.data() + offset), chunk);
        std::streamsize read_count = file.gcount();
        offset += read_count;
        remaining -= read_count;

        if (read_count == 0)
            break;
    }

    buffer.resize(offset);
    return buffer;
}

/// @brief 바이트 파일 기록
/// @param path 파일 경로
/// @param bytes 바이트
inline void write_bytes_to_file(const std::filesystem::path &path, std::span<const u8> bytes)
{
    std::ofstream output(path, std::ios::binary);
    if (!output)
        return;

    size_t remaining = bytes.size();
    size_t offset = 0;

    while (remaining > 0)
    {
        std::streamsize chunk = static_cast<std::streamsize>(std::min<size_t>(remaining, CHUNK_SIZE));
        output.write(reinterpret_cast<const char *>(bytes.data() + offset), chunk);
        offset += chunk;
        remaining -= chunk;
    }
}

/// @brief 앱 데이터 경로 반환
/// @return 앱 데이터 경로
inline std::filesystem::path get_app_data_path()
{
    static const std::filesystem::path app_data_path = [] {
        PWSTR path = nullptr;
        ::SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &path);

        std::filesystem::path result(path);
        ::CoTaskMemFree(path);

        result = result / "GSEditor";
        std::filesystem::create_directories(result);
        return result;
    }();
    return app_data_path;
}

/// @brief 앱 데이터 경로 반환 (구버전 호환용)
/// @return 앱 데이터 경로
inline std::filesystem::path get_app_data_path_legacy()
{
    static const std::filesystem::path app_data_path = [] {
        PWSTR path = nullptr;
        ::SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &path);

        std::filesystem::path result(path);
        ::CoTaskMemFree(path);

        result /= "GSEditor";
        std::filesystem::create_directories(result);
        return result;
    }();
    return app_data_path;
}

/// @brief 임시 파일 경로 생성
/// @param key 문자열 키
/// @return 생성된 임시 경로
inline std::filesystem::path create_temp_file_path(std::string_view key)
{
    static const auto tmp_dir = get_app_data_path() / "tmp";
    std::filesystem::create_directories(tmp_dir);
    return tmp_dir / utils::crypto::hash(key);
}

} // namespace utils::files

#endif
