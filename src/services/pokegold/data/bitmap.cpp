#include "bitmap.h"

#include "base/log.h"

#include <wx/gdicmn.h>
#include <wx/rawbmp.h>

#include <array>

namespace
{
    const std::array<u8, 8> k_bits = {
        0b00000001,
        0b00000010,
        0b00000100,
        0b00001000,
        0b00010000,
        0b00100000,
        0b01000000,
        0b10000000,
    };

    const std::array<u8, 8> k_reverseBits = {
        0b10000000,
        0b01000000,
        0b00100000,
        0b00010000,
        0b00001000,
        0b00000100,
        0b00000010,
        0b00000001,
    };
}

void pokegold::Bitmap::SetData(std::span<const u8> data)
{
    m_data.clear();
    m_data.insert(m_data.begin(), data.begin(), data.end());
}

void pokegold::Bitmap::SetPalettes(std::span<std::array<Color, 4>> palettes)
{
    m_palettes.clear();
    m_palettes.insert(m_palettes.begin(), palettes.begin(), palettes.end());
}

wxBitmap pokegold::Bitmap::Build_1bpp(int rows, int columns, std::span<const BitmapTileData> tiles)
{
    // TODO: 발자국 에디터, 폰트 에디터...
    return wxNullBitmap;
}

// https://www.huderlem.com/demos/gameboy2bpp.html
//
//  Tile:                                     Image:
//
//  .33333..                     .33333.. -> 01111100 -> $7C
//  22...22.                                 01111100 -> $7C
//  11...11.                     22...22. -> 00000000 -> $00
//  2222222. <-- digits                      11000110 -> $C6
//  33...33.     represent       11...11. -> 11000110 -> $C6
//  22...22.     color                       00000000 -> $00
//  11...11.     numbers         2222222. -> 00000000 -> $00
//  ........                                 11111110 -> $FE
//                               33...33. -> 11000110 -> $C6
//                                           11000110 -> $C6
//                               22...22. -> 00000000 -> $00
//                                           11000110 -> $C6
//                               11...11. -> 11000110 -> $C6
//                                           00000000 -> $00
//                               ........ -> 00000000 -> $00
//                                           00000000 -> $00

wxBitmap pokegold::Bitmap::Build_2bpp(int rows, int columns, std::span<const BitmapTileData> tiles)
{
    if (rows == 0 || columns == 0)
    {
        base::Log(TAG, "Build_2bpp: rows = 0 or columns = 0");
        return wxNullBitmap;
    }

    wxBitmap resultBitmap(columns * 8, rows * 8);
    wxNativePixelData data(resultBitmap);
    wxNativePixelData::Iterator p(data);

    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            const auto &tile = tiles[(rows * column) + row];

            int dataIndex = tile.TileId * 16;
            for (int y = 0; y < 8; y++)
            {
                u8 hi = m_data[dataIndex + (y * 2)];
                u8 lo = m_data[dataIndex + (y * 2) + 1];

                for (int x = 0; x < 8; x++)
                {
                    p.MoveTo(data, (column * 8) + x, (row * 8) + y);

                    int paletteIndex = 0;
                    if ((hi & k_reverseBits[x]) != 0)
                        paletteIndex += 1;
                    if ((lo & k_reverseBits[x]) != 0)
                        paletteIndex += 2;

                    const auto &palette = m_palettes[tile.PaletteId][paletteIndex];
                    p.Red() = palette.R();
                    p.Green() = palette.G();
                    p.Blue() = palette.B();
                }
            }
        }
    }

    return resultBitmap;
}
