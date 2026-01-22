#include "pokegold.h"

void pokegold::close()
{
    debug_log("pokegold::close", "clear items");
    for (size_t i = 0; i < 256; i++)
    {
        // props
        auto &item = data::items[i];
        item.price = 0;
        item.effect = 0;
        item.parameter = 0;
        item.property = 0;
        item.pocket = 0;
        item.field_menu = 0;
        item.battle_menu = 0;

        // name & desc
        item.name = "";
        item.description = "";
    }

    // TODO: ...

    debug_log("pokegold::close", "done");

    config::close();
    romfile::close();

    event::rom_data_changed();
    event::rom_changed();
}
