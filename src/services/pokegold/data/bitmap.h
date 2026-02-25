#pragma once

#include "base/types/types.h"
#include "services/pokegold/data/color.h"

#include <wx/bitmap.h>

#include <span>
#include <vector>

namespace pokegold
{
    struct BitmapTileData
    {
        u8 TileId;
        u8 PaletteId;
    };

    class Bitmap
    {
    private:
        inline static const auto TAG = "pokegold::Bitmap";

        std::vector<u8> m_data;
        std::vector<std::array<Color, 4>> m_palettes;

    public:
        void SetData(std::span<const u8> data);
        void SetPalettes(std::span<std::array<Color, 4>> palettes);

        wxBitmap Build_1bpp(int rows, int columns, std::span<const BitmapTileData> tiles);
        wxBitmap Build_2bpp(int rows, int columns, std::span<const BitmapTileData> tiles);
    };
}
