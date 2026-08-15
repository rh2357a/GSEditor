#pragma once

#include <cmrc/cmrc.hpp>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/mstream.h>

#include <span>

#include "base/types/types.h"

CMRC_DECLARE(embed);

#define EMBED(name, path)                                                                    \
    inline const std::span<const u8> name = [] {                                             \
        const auto file = cmrc::embed::get_filesystem().open(path);                          \
        return std::span<const u8>(reinterpret_cast<const u8 *>(file.begin()), file.size()); \
    }();

#define EMBED_BITMAP(name, type, path)                                                           \
    namespace internal                                                                           \
    {                                                                                            \
        inline const std::span<const u8> name = [] {                                             \
            const auto file = cmrc::embed::get_filesystem().open(path);                          \
            return std::span<const u8>(reinterpret_cast<const u8 *>(file.begin()), file.size()); \
        }();                                                                                     \
    }                                                                                            \
    inline wxBitmap &Get##name##Bitmap()                                                         \
    {                                                                                            \
        static wxMemoryInputStream mis(internal::name.data(), internal::name.size());            \
        static wxImage image(mis, type);                                                         \
        static wxBitmap bmp(image);                                                              \
        return bmp;                                                                              \
    }

namespace embed
{
    EMBED_BITMAP(AppIcon, wxBITMAP_TYPE_ICO, "assets/app_icon.ico")
    EMBED(kThirdPartyNotices, "assets/ThirdPartyNotices.txt")
    EMBED(kChangelog, "assets/changelog.html")

    namespace pokegold
    {
        EMBED(kCharmapList, "assets/pokegold/charmap.txt")
        EMBED(kMacrosSource, "assets/pokegold/macros.asm")
        EMBED(kHacksSource, "assets/pokegold/hacks.asm")
        EMBED(kSmallPicturesSource, "assets/pokegold/small_pics.asm")
        EMBED(kTrainerCardSource, "assets/pokegold/trainer_card.asm")
        EMBED(kDefaultTypeMatchupsData, "assets/pokegold/default_type_matchups.bin")
        EMBED(kDefaultTypeWeatherModifiersData, "assets/pokegold/default_type_weather_modifiers.bin")
        EMBED(kDefaultMoveEffectWeatherModifiersData, "assets/pokegold/default_move_effect_weather_modifiers.bin")
        EMBED(kDefaultSmallPicturesData, "assets/pokegold/default_small_pictures.bin")
        EMBED(kDefaultSmallPicturesPaletteData, "assets/pokegold/default_small_pictures_palette_id.bin")
        EMBED(kDefaultSmallPicturesAttributes, "assets/pokegold/default_small_pictures_attributes.bin")
    }
}

#undef EMBED
#undef EMBED_BITMAP
