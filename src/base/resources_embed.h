#pragma once

#include "base/types/embed_types.h"

EMBED_WX_BITMAP(AppIcon, wxBITMAP_TYPE_ICO, "GSEditor.exe.ico")

EMBED_BINARY(AppVersionsHtml, "app_versions.html")
EMBED_BINARY(AppThirdPartyNotices, "third_party_notices.txt")

EMBED_BINARY(PokegoldCharmapList, "pokegold/charmap.txt")
EMBED_BINARY(PokegoldMacrosSource, "pokegold/macros.asm")
EMBED_BINARY(PokegoldHacksSource, "pokegold/hacks.asm")
EMBED_BINARY(PokegoldSmallPicturesSource, "pokegold/small_pics.asm")
EMBED_BINARY(PokegoldDefaultTypeMatchupsData, "pokegold/default_type_matchups.bin")
EMBED_BINARY(PokegoldDefaultTypeWeatherModifiersData, "pokegold/default_type_weather_modifiers.bin")
EMBED_BINARY(PokegoldDefaultMoveEffectWeatherModifiersData, "pokegold/default_move_effect_weather_modifiers.bin")
EMBED_BINARY(PokegoldDefaultSmallPicturesData, "pokegold/default_small_pictures.bin")
EMBED_BINARY(PokegoldDefaultSmallPicturesPaletteData, "pokegold/default_small_pictures_palette_id.bin")
EMBED_BINARY(PokegoldDefaultSmallPicturesAttributes, "pokegold/default_small_pictures_attributes.bin")
