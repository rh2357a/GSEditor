#include "bitmap.h"

#include "base/files/file_util.h"
#include "base/types/types.h"

#include <lodepng/lodepng.h>
#include <wx/colour.h>
#include <wx/gdicmn.h>
#include <wx/msw/colour.h>

#include <array>
#include <unordered_map>
#include <vector>

namespace
{
    struct wxColourHash
    {
        size_t operator()(const wxColour &c) const
        {
            return (static_cast<size_t>(c.Red()) << 24)
                   | (static_cast<size_t>(c.Green()) << 16)
                   | (static_cast<size_t>(c.Blue()) << 8)
                   | static_cast<size_t>(c.Alpha());
        }
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

base::ImportIndexedPngResult base::ImportIndexedPngResult::PngError = {-1, {}, {}, {}, wxNullBitmap};

base::WriteIndexedPngResult base::WriteIndexedPngFile(const std::filesystem::path &path, const wxBitmap &bitmap, std::span<const wxColour> palette)
{
    std::unordered_map<wxColour, u8, wxColourHash> paletteMap;
    for (size_t i = 0; i < palette.size(); i++)
    {
        const auto &color = palette[i];
        paletteMap[color] = u8(i);
    }

    wxImage image = bitmap.ConvertToImage();

    u32 width = image.GetWidth();
    u32 height = image.GetHeight();

    u8 *rgb = image.GetData();
    std::vector<u8> indexData(width * height);

    for (u32 i = 0; i < width * height; i++)
    {
        wxColour color(rgb[i * 3 + 0], rgb[i * 3 + 1], rgb[i * 3 + 2]);
        indexData[i] = paletteMap[color];
    }

    lodepng::State state;
    {
        state.info_raw.colortype = LCT_PALETTE;
        state.info_raw.bitdepth = 8;

        state.info_png.color.colortype = LCT_PALETTE;
        state.info_png.color.bitdepth = 8;
        state.info_png.interlace_method = 0;
        state.info_png.gama_defined = 1;
        state.info_png.srgb_defined = 1;

        state.encoder.filter_strategy = LFS_ZERO;
        state.encoder.zlibsettings.btype = 1;
        state.encoder.zlibsettings.use_lz77 = 1;
        state.encoder.zlibsettings.windowsize = 4096;
        state.encoder.auto_convert = 0;
    }

    for (u32 i = 0; i <= 255; i++)
    {
        if (i < palette.size())
        {
            const auto &color = palette[i];
            lodepng_palette_add(&state.info_png.color, color.Red(), color.Green(), color.Blue(), 255);
            lodepng_palette_add(&state.info_raw, color.Red(), color.Green(), color.Blue(), 255);
        }
        else
        {
            lodepng_palette_add(&state.info_png.color, 0, 0, 0, 255);
            lodepng_palette_add(&state.info_raw, 0, 0, 0, 255);
        }
    }

    std::vector<u8> png;
    if (lodepng::encode(png, indexData, width, height, state) != 0)
        return WriteIndexedPngResult::EncodeError;

    if (lodepng::save_file(png, path.string()) != 0)
        return WriteIndexedPngResult::WriteFailure;

    return WriteIndexedPngResult::Successful;
}

base::ImportIndexedPngResult base::ImportIndexedPngFile(const std::filesystem::path &path)
{
    const auto pngBytes = base::ReadBytesFromFile(path);

    std::vector<u8> indexData;
    u32 width, height;
    lodepng::State state;
    if (lodepng::decode(indexData, width, height, state, pngBytes.data(), pngBytes.size()) != 0)
        return ImportIndexedPngResult::PngError;

    if (state.info_png.color.colortype != LCT_PALETTE)
        return ImportIndexedPngResult::PngError;
    if (state.info_png.color.bitdepth != 8)
        return ImportIndexedPngResult::PngError;
    if (state.info_png.color.palettesize == 0)
        return ImportIndexedPngResult::PngError;

    std::vector<wxColour> palette;
    std::unordered_map<wxColour, u8, wxColourHash> paletteMap;
    {
        const auto &color = state.info_png.color;
        for (u32 i = 0; i < color.palettesize; i++)
        {
            u8 r = color.palette[i * 4 + 0];
            u8 g = color.palette[i * 4 + 1];
            u8 b = color.palette[i * 4 + 2];

            const wxColour newColor(r, g, b);
            if (!paletteMap.contains(newColor))
            {
                palette.push_back(newColor);
                paletteMap[newColor] = i;
            }
        }
    }

    wxImage image(width, height);
    {
        u8 *rgb = image.GetData();
        for (u32 i = 0; i < width * height; i++)
        {
            rgb[i * 3 + 0] = indexData[i * 4 + 0];
            rgb[i * 3 + 1] = indexData[i * 4 + 1];
            rgb[i * 3 + 2] = indexData[i * 4 + 2];
        }
    }

    int rows = int(height / 8);
    int columns = int(width / 8);

    std::vector<u8> data1bpp(rows * columns * 8, 0);
    std::vector<u8> data2bpp(rows * columns * 16, 0);

    for (int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            int index = row + (column * rows);

            for (int y = 0; y < 8; y++)
            {
                int idx1bpp = (index * 16) + y;
                int idx2bpp = (index * 16) + (y * 2);

                for (int x = 0; x < 8; x++)
                {
                    int idx = ((y + (row * 8)) * width * 4) + ((x + (column * 8)) * 4);
                    wxColour color(indexData[idx], indexData[idx + 1], indexData[idx + 2]);
                    u8 paletteIdx = paletteMap[color];

                    auto &hi = data2bpp[idx2bpp];
                    auto &lo = data2bpp[idx2bpp + 1];

                    if (paletteIdx == 1)
                    {
                        hi |= k_reverseBits[x];
                    }
                    else if (paletteIdx == 2)
                    {
                        lo |= k_reverseBits[x];
                    }
                    else if (paletteIdx == 3)
                    {
                        hi |= k_reverseBits[x];
                        lo |= k_reverseBits[x];
                    }
                }
            }

            // TODO: 1bpp
        }
    }

    return {0, data1bpp, data2bpp, palette, wxBitmap(image)};
}
