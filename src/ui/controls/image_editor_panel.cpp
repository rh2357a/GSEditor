#include "image_editor_panel.h"

#include "base/files/bitmap.h"
#include "base/files/file_util.h"
#include "base/log.h"
#include "base/types/types.h"
#include "services/pokegold/data/bitmap.h"
#include "services/pokegold/data/color.h"
#include "services/pokegold/data/game_data.h"
#include "ui/dialogs/file_dialogs.h"

#include <wx/dcbuffer.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/menu.h>

#include <array>
#include <vector>

namespace
{
    pokegold::Color k_blackColor = {0, 0, 0};
    pokegold::Color k_whiteColor = {255, 255, 255};
    pokegold::Color k_lightGrayColor = {33, 33, 33};
    pokegold::Color k_darkGrayColor = {128, 128, 128};

    // clang-format off

    std::vector<pokegold::BitmapTileData> k_tiles_2x2 = {
        { 0, 0 }, { 1, 0 },
        { 2, 0 }, { 3, 0 },
    };

    std::vector<pokegold::BitmapTileData> k_tiles_4x2 = {
        { 0, 0 }, { 1, 0 }, { 4, 0 }, { 5, 0 },
        { 2, 0 }, { 3, 0 }, { 6, 0 }, { 7, 0 },
    };

    std::vector<pokegold::BitmapTileData> k_tiles_5x5 = {
        { 0, 0 }, { 5, 0 }, { 10, 0 }, { 15, 0 }, { 20, 0 },
        { 1, 0 }, { 6, 0 }, { 11, 0 }, { 16, 0 }, { 21, 0 },
        { 2, 0 }, { 7, 0 }, { 12, 0 }, { 17, 0 }, { 22, 0 },
        { 3, 0 }, { 8, 0 }, { 13, 0 }, { 18, 0 }, { 23, 0 },
        { 4, 0 }, { 9, 0 }, { 14, 0 }, { 19, 0 }, { 24, 0 },
    };

    std::vector<pokegold::BitmapTileData> k_tiles_6x6 = {
        { 0, 0 }, {  6, 0 }, { 12, 0 }, { 18, 0 }, { 24, 0 } , { 30, 0 },
        { 1, 0 }, {  7, 0 }, { 13, 0 }, { 19, 0 }, { 25, 0 } , { 31, 0 },
        { 2, 0 }, {  8, 0 }, { 14, 0 }, { 20, 0 }, { 26, 0 } , { 32, 0 },
        { 3, 0 }, {  9, 0 }, { 15, 0 }, { 21, 0 }, { 27, 0 } , { 33, 0 },
        { 4, 0 }, { 10, 0 }, { 16, 0 }, { 22, 0 }, { 28, 0 } , { 34, 0 },
        { 5, 0 }, { 11, 0 }, { 17, 0 }, { 23, 0 }, { 29, 0 } , { 35, 0 },
    };

    std::vector<pokegold::BitmapTileData> k_tiles_7x7 = {
        { 0, 0 }, {  7, 0 }, { 14, 0 }, { 21, 0 }, { 28, 0 },  {35, 0 }, { 42, 0 },
        { 1, 0 }, {  8, 0 }, { 15, 0 }, { 22, 0 }, { 29, 0 },  {36, 0 }, { 43, 0 },
        { 2, 0 }, {  9, 0 }, { 16, 0 }, { 23, 0 }, { 30, 0 },  {37, 0 }, { 44, 0 },
        { 3, 0 }, { 10, 0 }, { 17, 0 }, { 24, 0 }, { 31, 0 },  {38, 0 }, { 45, 0 },
        { 4, 0 }, { 11, 0 }, { 18, 0 }, { 25, 0 }, { 32, 0 },  {39, 0 }, { 46, 0 },
        { 5, 0 }, { 12, 0 }, { 19, 0 }, { 26, 0 }, { 33, 0 },  {40, 0 }, { 47, 0 },
        { 6, 0 }, { 13, 0 }, { 20, 0 }, { 27, 0 }, { 34, 0 },  {41, 0 }, { 48, 0 },
    };

    // clang-format on

    std::array<wxString, 38> k_templateNames = {
        wxT("발챙이"),
        wxT("푸린"),
        wxT("디그다"),
        wxT("피카츄"),
        wxT("별가사리"),
        wxT("잉어킹"),
        wxT("새 모양"),
        wxT("공룡 모양"),
        wxT("삐삐"),
        wxT("풀 모양"),
        wxT("벌레 모양"),
        wxT("유령 모양"),
        wxT("라프라스"),
        wxT("요정 모양"),
        wxT("강아지 모양"),
        wxT("소 모양"),
        wxT("조개 모양"),
        wxT("메타몽"),
        wxT("뱀 모양"),
        wxT("찌리리공"),
        wxT("꼬부기"),
        wxT("이상해씨"),
        wxT("파이리"),
        wxT("뿔충이"),
        wxT("안농"),
        wxT("꼬마돌"),
        wxT("격투가 모양"),
        wxT("알 모양"),
        wxT("해파리 모양"),
        wxT("나비 모양"),
        wxT("박쥐 모양"),
        wxT("잠만보"),
        wxT("칠색조"),
        wxT("루기아"),
        wxT("갸라도스"),
        wxT("야도"),
        wxT("꼬지모"),
        wxT("드래곤 모양"),
    };
}

void ui::ImageEditorPanel::MenuInitialize()
{
    m_menu.Append(ImageEditorPopupMenu::Import, wxT("이미지 교체..."));
    m_menu.AppendSeparator();
    m_menu.Append(ImageEditorPopupMenu::WritePng, wxT("png 저장..."));
    m_menu.Append(ImageEditorPopupMenu::WriteBinary, wxT("bin 저장..."));
}

void ui::ImageEditorPanel::OnPaint(wxPaintEvent &ev)
{
    wxAutoBufferedPaintDC dc(this);

    auto size = GetClientSize();
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(*wxWHITE_BRUSH);
    dc.DrawRectangle(0, 0, size.x, size.y);

    if (m_cacheBitmap.IsOk())
    {
        auto bitmapSize = m_cacheBitmap.GetSize();
        int x = (size.x - bitmapSize.x) / 2;
        int y = (size.y - bitmapSize.y) / 2;
        dc.DrawBitmap(m_cacheBitmap, x, y);
    }
}

void ui::ImageEditorPanel::OnImportFromPng(wxCommandEvent &ev)
{
    base::Log(TAG, "OnImportFromPng");
    m_importRequested();
}

void ui::ImageEditorPanel::OnWritePng(wxCommandEvent &ev)
{
    base::Log(TAG, "OnWritePng");

    if (!m_cacheBitmap.IsOk())
    {
        base::Log(TAG, "OnWritePng: failure (m_cacheBitmap = null)");
        return;
    }

    const auto path = ShowSaveFileDialog(this, "png 저장...", {"png 파일|*.png"});
    if (path.has_value())
    {
        std::vector<wxColour> palette;
        for (auto &pal : m_bitmapBuilder.GetPalette()[0])
            palette.push_back(pal.ToWxColor());

        base::WriteIndexedPngFile(*path, m_cacheBitmap, palette);
    }
}

void ui::ImageEditorPanel::OnWriteBinary(wxCommandEvent &ev)
{
    base::Log(TAG, "OnWriteBinary");

    const auto path = ShowSaveFileDialog(this, "bin 저장...", {"bin 파일|*.bin", "모든 형식|*.*"});
    if (path.has_value())
    {
        const auto bytes = m_bitmapBuilder.GetData();
        base::WriteBytesToFile(*path, bytes);
    }
}

void ui::ImageEditorPanel::Clear()
{
    m_cacheBitmap = wxNullBitmap;
    Refresh();
}

void ui::ImageEditorPanel::Set2bppData(pokegold::ImageDimensions size, std::span<const u8> data, std::optional<std::span<pokegold::Color>> colors)
{
    if (colors.has_value())
    {
        const auto realColors = *colors;
        if (realColors.size() == 2)
        {
            std::vector<std::array<pokegold::Color, 4>> palette = {
                // 0
                {
                    k_whiteColor,
                    realColors[0],
                    realColors[1],
                    k_blackColor,
                },
            };

            m_bitmapBuilder.SetPalette(palette);
        }
        else
        {
            std::vector<std::array<pokegold::Color, 4>> palette = {
                // 0
                {
                    realColors[0],
                    realColors[1],
                    realColors[2],
                    realColors[3],
                },
            };

            m_bitmapBuilder.SetPalette(palette);
        }
    }
    else
    {
        std::vector<std::array<pokegold::Color, 4>> palette = {
            // 0
            {
                k_whiteColor,
                k_lightGrayColor,
                k_darkGrayColor,
                k_blackColor,
            },
        };

        m_bitmapBuilder.SetPalette(palette);
    }

    m_bitmapBuilder.SetData(data);

    if (size == pokegold::ImageDimensions::Size_40x40)
        m_cacheBitmap = m_bitmapBuilder.Build_2bpp(5, 5, k_tiles_5x5);
    else if (size == pokegold::ImageDimensions::Size_48x48)
        m_cacheBitmap = m_bitmapBuilder.Build_2bpp(6, 6, k_tiles_6x6);
    else if (size == pokegold::ImageDimensions::Size_56x56)
        m_cacheBitmap = m_bitmapBuilder.Build_2bpp(7, 7, k_tiles_7x7);
    else if (size == pokegold::ImageDimensions::Size_16x16)
        m_cacheBitmap = m_bitmapBuilder.Build_2bpp(2, 2, k_tiles_2x2);
    else if (size == pokegold::ImageDimensions::Size_32x16)
        m_cacheBitmap = m_bitmapBuilder.Build_2bpp(2, 4, k_tiles_4x2);

    Refresh();
}

void ui::ImageEditorPanel::Set1bppData(pokegold::ImageDimensions size, std::span<const u8> data, std::optional<std::span<pokegold::Color>> colors)
{
    std::vector<std::array<pokegold::Color, 4>> palette = {
        // 0
        {
            k_whiteColor,
            k_blackColor,
        },
    };

    m_bitmapBuilder.SetPalette(palette);
    m_bitmapBuilder.SetData(data);

    m_cacheBitmap = m_bitmapBuilder.Build_1bpp(2, 2, k_tiles_2x2);

    Refresh();
}
