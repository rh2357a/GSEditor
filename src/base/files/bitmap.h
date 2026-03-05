#pragma once

#include "base/types/types.h"

#include <wx/bitmap.h>
#include <wx/colour.h>

#include <filesystem>
#include <span>
#include <vector>

namespace base
{
    enum class WriteIndexedPngResult
    {
        EncodeError,
        WriteFailure,
        Successful,
    };

    class ImportIndexedPngResult
    {
    public:
        static ImportIndexedPngResult PngError;

    private:
        int m_code;
        std::vector<u8> m_data1bpp, m_data2bpp;
        std::vector<wxColour> m_palette;
        wxBitmap m_bitmap;

    public:
        ImportIndexedPngResult(int code, std::vector<u8> data1bpp, std::vector<u8> data2bpp, std::vector<wxColour> palette, wxBitmap bitmap)
            : m_code(code),
              m_data1bpp(std::move(data1bpp)),
              m_data2bpp(std::move(data2bpp)),
              m_palette(std::move(palette)),
              m_bitmap(std::move(bitmap)) {}

    public:
        bool operator==(const ImportIndexedPngResult &other) const { return m_code == other.m_code; }

    public:
        std::vector<u8> Get1bppData() { return m_data1bpp; }
        std::vector<u8> Get2bppData() { return m_data2bpp; }
        std::vector<wxColour> GetPalette() { return m_palette; }
        wxBitmap GetBitmap() { return m_bitmap; }
    };
}

namespace base
{
    /**
     * @brief 팔레트 형식의 png 비트맵 기록
     *
     * @param path 저장할 png 경로
     * @param bitmap wx 비트맵
     * @param palette 팔레트 (색상 정보)
     * @return 결과
     */
    WriteIndexedPngResult WriteIndexedPngFile(const std::filesystem::path &path, const wxBitmap &bitmap, std::span<const wxColour> palette);

    /**
     * @brief 팔레트 형식의 png를 로딩
     *
     * @param path png 파일 경로
     * @return 결과
     */
    ImportIndexedPngResult ImportIndexedPngFile(const std::filesystem::path &path);
}
