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

    class BitmapBuilder
    {
    private:
        inline static const auto TAG = "pokegold::BitmapBuilder";

        std::vector<u8> m_data;
        std::vector<std::array<Color, 4>> m_palette;

    public:
        std::vector<u8> GetData() { return m_data; }
        void SetData(std::span<const u8> data);

        std::vector<std::array<Color, 4>> GetPalette() { return m_palette; }
        void SetPalette(std::span<const std::array<Color, 4>> palette);

        wxBitmap Build_1bpp(int rows, int columns, std::span<const BitmapTileData> tiles);
        wxBitmap Build_2bpp(int rows, int columns, std::span<const BitmapTileData> tiles);
    };
}
