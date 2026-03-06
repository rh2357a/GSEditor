#pragma once

#include "base/types/embed_types.h"

EMBED_WX_BITMAP(AppIcon, wxBITMAP_TYPE_ICO, "GSEditor.exe.ico")

EMBED_BINARY(AppVersionsHtml, "app_versions.html")
EMBED_BINARY(AppThirdPartyNotices, "third_party_notices.txt")

EMBED_BINARY(PokegoldCharmapList, "pokegold/charmap.txt")
EMBED_BINARY(PokegoldMacrosSource, "pokegold/macros.asm")
EMBED_BINARY(PokegoldHacksSource, "pokegold/hacks.asm")
EMBED_BINARY(PokegoldDefaultTypeMatchupsData, "pokegold/default_type_matchups.bin")
EMBED_BINARY(PokegoldDefaultWeatherTypeModifiersData, "pokegold/default_weather_type_modifiers.bin")
EMBED_BINARY(PokegoldDefaultWeatherMoveModifiersData, "pokegold/default_weather_move_modifiers.bin")
