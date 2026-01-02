#ifndef _EMBED_H_
#define _EMBED_H_

#include "embed_types.h"

EMBED_WX_BITMAP(app_ico, wxBITMAP_TYPE_ICO, "app.ico")
EMBED_BINARY(app_version_html, "app_versions.html")
EMBED_BINARY(charmap_txt, "charmap.txt")
EMBED_BINARY(pokegold_macros_asm, "pokegold/macros.asm")
EMBED_BINARY(pokegold_type_matchups_asm, "pokegold/type_matchups.asm")

#endif
