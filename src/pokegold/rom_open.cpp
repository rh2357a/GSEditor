#include "pokegold.h"
#include "embed.h"
#include "utils.h"
#include <array>

constexpr size_t IMG_55_SIZE = 400;
constexpr size_t IMG_66_SIZE = 576;
constexpr size_t IMG_77_SIZE = 784;

const std::array<u8, 8> BITS{
    0b00000001,
    0b00000010,
    0b00000100,
    0b00001000,
    0b00010000,
    0b00100000,
    0b01000000,
    0b10000000,
};

inline void image_addr_log(size_t addr, size_t len)
{
    if constexpr (DEBUG_MODE && false)
    {
        const auto s = std::format("img_addr={:x}, size={}", addr, len);
        debug_log("pokegold::open", s);
    }
}

std::vector<pokegold::data::bad_data> pokegold::open(const std::filesystem::path &filepath)
{
    romfile::open(filepath);
    config::read();

    std::vector<data::bad_data> bad_data_list;
    std::vector<u8> image_buffer(0x400);

    debug_log("pokegold::open", "parse items");
    {
        debug_log("pokegold::open", "  - props");
        for (size_t i = 0; i < 256; i++)
        {
            // debug_log("pokegold::open", "    - {}", i);

            auto bytes = romfile::get_bytes(0x697b + i * 7, 7);

            auto &item = data::items[i];
            item.price = bytes[0] | (static_cast<u16>(bytes[1]) << 8);
            item.effect = bytes[2];
            item.parameter = bytes[3];
            item.property = bytes[4];
            item.pocket = bytes[5];
            item.field_menu = (bytes[6] & 0xf0) >> 4;
            item.battle_menu = bytes[6] & 0x0f;
        }

        debug_log("pokegold::open", "  - names");
        size_t name_addr = addr::calc(romfile::get_bytes(0x35cc, 3));
        for (size_t i = 0; i < 256; i++)
        {
            // debug_log("pokegold::open", "    - {}", i);

            const auto bytes = romfile::get_bytes_until(name_addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            name_addr += bytes.size();
            data::items[i].name = bytes;
        }

        debug_log("pokegold::open", "  - descriptions");
        u8 desc_bank = addr::calc_bank(0x1b8000);
        for (size_t i = 0; i < 256; i++)
        {
            // debug_log("pokegold::open", "    - {}", i);

            size_t addr = addr::calc(desc_bank, romfile::get_bytes(0x1b8000 + (i * 2), 2));
            const auto bytes = romfile::get_bytes_until(addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            data::items[i].description = bytes;
        }
    }

    debug_log("pokegold::open", "parse moves");
    {
        debug_log("pokegold::open", "  - props");
        for (size_t i = 0; i < 251; i++)
        {
            // debug_log("pokegold::open", "    - {}", i);

            auto bytes = romfile::get_bytes(0x4172e + i * 7, 7);

            auto &move = data::moves[i];
            move.id = bytes[0];
            move.effect = bytes[1];
            move.power = bytes[2];
            move.type = bytes[3];
            move.accuracy = bytes[4];
            move.pp = bytes[5];
            move.effect_chance = bytes[6];

            move.weather_modifiers.clear();
        }

        debug_log("pokegold::open", "  - names");
        size_t name_addr = addr::calc(romfile::get_bytes(0x35c6, 3));
        for (size_t i = 0; i < 251; i++)
        {
            // debug_log("pokegold::open", "    - {}", i);

            const auto bytes = romfile::get_bytes_until(name_addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            name_addr += bytes.size();
            data::moves[i].name = bytes;
        }

        debug_log("pokegold::open", "  - descriptions");
        u8 desc_bank = addr::calc_bank(0x1b4000);
        for (size_t i = 0; i < 251; i++)
        {
            // debug_log("pokegold::open", "    - {}", i);

            size_t addr = addr::calc(desc_bank, romfile::get_bytes(0x1b4000 + (i * 2), 2));
            const auto bytes = romfile::get_bytes_until(addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            data::moves[i].description = bytes;
        }
    }

    debug_log("pokegold::open", "parse TMHMs");
    for (size_t i = 0; i < 57; i++)
    {
        // debug_log("pokegold::open", "    - {}", i);
        data::tmhms[i] = romfile::get_byte(0x119f5 + i);
    }

    debug_log("pokegold::open", "parse pokemons");
    {
        const u8 evos_bank = addr::calc_bank(0x423ed);
        size_t evos_addr = 0x423ed;
        size_t mon_name_addr = addr::calc(romfile::get_bytes(0x35c3, 3));
        size_t props_addr = 0x51bdf;

        debug_log("pokegold::open", "  - props, name, pokedex");
        for (size_t i = 0; i < 256; i++)
        {
            // debug_log("pokegold::open", "    - {}", i);

            const auto bytes = romfile::get_bytes(props_addr, 32);
            props_addr += 32;

            auto &mon = data::pokemons[i];

            if (i == 200)
                mon.type = data::pokemon_type::UNOWN;
            else if (i == 252)
                mon.type = data::pokemon_type::EGG;
            else if (i < 251)
                mon.type = data::pokemon_type::POKEMON;
            else
                mon.type = data::pokemon_type::DUMMY;

            if (mon.type == data::pokemon_type::POKEMON || mon.type == data::pokemon_type::UNOWN)
            {
                mon.id = bytes[0];
                mon.hp = bytes[1];
                mon.atk = bytes[2];
                mon.def = bytes[3];
                mon.spd = bytes[4];
                mon.sp_atk = bytes[5];
                mon.sp_def = bytes[6];
                mon.type_1_id = bytes[7];
                mon.type_2_id = bytes[8];
                mon.catch_rate = bytes[9];
                mon.base_exp = bytes[10];
                mon.item_1_id = bytes[11];
                mon.item_2_id = bytes[12];
                mon.gender_rate = data::gender_rate(bytes[13]);
                mon.egg_hatch_lv = bytes[15];
                mon.image_dimens = data::image_dimens(bytes[17]);
                mon.growth_rate = data::growth_rate(bytes[22]);
                mon.egg_group_1 = data::egg_group((bytes[23] & 0xf0) >> 4);
                mon.egg_group_2 = data::egg_group(bytes[23] & 0x0f);

                for (u8 j = 0; j < 8; j++)
                {
                    for (u8 a = 0; a < 8; a++)
                    {
                        u8 idx = (j * 8) + a;
                        mon.tmhms[idx] = (bytes[24 + j] & BITS[a]) != 0;
                    }
                }

                size_t evo_addr = addr::calc(evos_bank, romfile::get_bytes(evos_addr, 2));
                evos_addr += 2;

                mon.evolution_methods.clear();
                mon.learn_moves.clear();

                const auto evo_bytes = romfile::get_bytes_until(evo_addr, [&](size_t idx, u8 b) { return b == 0; }, true);
                bool bad_evolution_data = false;
                for (size_t j = 0; j < evo_bytes.size();)
                {
                    if (bad_evolution_data)
                        break;

                    data::evolution_method new_evolve;
                    new_evolve.evolution_type = evo_bytes[j++];

                    switch (new_evolve.evolution_type)
                    {
                    case 1:
                        new_evolve.level = evo_bytes[j++];
                        new_evolve.pokemon_id = evo_bytes[j++];
                        mon.evolution_methods.push_back(new_evolve);
                        break;

                    case 2:
                    case 3:
                        new_evolve.item_id = evo_bytes[j++];
                        new_evolve.pokemon_id = evo_bytes[j++];
                        mon.evolution_methods.push_back(new_evolve);
                        break;

                    case 4:
                        new_evolve.happiness = evo_bytes[j++];
                        new_evolve.pokemon_id = evo_bytes[j++];
                        mon.evolution_methods.push_back(new_evolve);
                        break;

                    case 5:
                        new_evolve.level = evo_bytes[j++];
                        new_evolve.stats = evo_bytes[j++];
                        new_evolve.pokemon_id = evo_bytes[j++];
                        mon.evolution_methods.push_back(new_evolve);
                        break;

                    case 0:
                        break;

                    default:
                        // debug_log("pokegold::open", "bad evolution");
                        bad_evolution_data = true;
                        mon.evolution_methods.clear();
                        mon.learn_moves.clear();
                        bad_data_list.push_back({data::bad_data_reason::EVOLUTION_MOVES, i});
                        break;
                    }
                }

                if (!bad_evolution_data)
                {
                    const auto move_bytes = romfile::get_bytes_until(evo_addr + evo_bytes.size(), [&](size_t idx, u8 b) { return b == 0; }, true);
                    for (size_t j = 0; j < move_bytes.size();)
                    {
                        const u8 b = move_bytes[j++];
                        if (b == 0 || j >= move_bytes.size())
                            break;

                        data::learn_move new_item;
                        new_item.level = b;
                        new_item.move_id = move_bytes[j++];
                        mon.learn_moves.push_back(new_item);
                    }
                }

                size_t addr;
                if (i < 128)
                    addr = addr::calc(0x68, romfile::get_bytes(0x442ff + (i * 2), 2));
                else
                    addr = addr::calc(0x69, romfile::get_bytes(0x443ff + ((i - 128) * 2), 2));

                auto &mon = data::pokemons[i];

                mon.species_name = romfile::get_bytes_until(addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
                addr += mon.species_name.size();

                mon.height = romfile::get_byte(addr);
                addr += 1;

                mon.weight = romfile::get_byte(addr) | (romfile::get_byte(addr + 1) << 8);
                addr += 2;

                mon.description = romfile::get_bytes_until(addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            }

            mon.name = romfile::get_bytes_until(mon_name_addr, [&](size_t idx, u8 b) { return idx == 9 || b == 0x50; }, true);
            mon_name_addr += 10;

            if (mon.name.has_bad_code())
            {
                mon.name = "[50]";
                bad_data_list.push_back({data::bad_data_reason::POKEMON_NAME, i});
            }
        }

        debug_log("pokegold::open", "  - image, color");
        for (size_t i = 0; i < 256; i++)
        {
            // debug_log("pokegold::open", "    - {}", i);

            const auto addr = 0xad15 + i * 8;
            data::pokemons[i].colors[0] = color(romfile::get_bytes(addr, 2));
            data::pokemons[i].colors[1] = color(romfile::get_bytes(addr + 2, 2));
            data::pokemons[i].shiny_colors[0] = color(romfile::get_bytes(addr + 4, 2));
            data::pokemons[i].shiny_colors[1] = color(romfile::get_bytes(addr + 6, 2));

            if (data::pokemons[i].type == data::pokemon_type::UNOWN || data::pokemons[i].type == data::pokemon_type::DUMMY)
                continue;

            if (data::pokemons[i].type == data::pokemon_type::EGG)
            {
                const size_t front_addr = addr::calc(romfile::get_byte(0x5189a), romfile::get_bytes(0x51897, 2));
                const auto front_size = romfile::read_lz_decompressed(image_buffer, front_addr, 0x400);

                if (front_size == 0)
                    bad_data_list.push_back({data::bad_data_reason::EGG_IMAGE, nullptr});

                data::pokemons[i].front_image = (front_size == 0)
                                                    ? std::vector<u8>(IMG_55_SIZE, 0)
                                                    : std::vector<u8>(image_buffer.begin(), image_buffer.begin() + front_size);
            }
            else
            {
                const auto front_ptr = romfile::get_bytes(0x48000 + i * 6, 3);
                const auto front_addr = addr::calc_from_encoded_bank(front_ptr);
                const auto front_size = romfile::read_lz_decompressed(image_buffer, front_addr, 0x400);

                image_addr_log(front_addr, romfile::calc_lz_size(front_addr, 0x400));

                if (front_size == 0)
                {
                    data::pokemons[i].image_dimens = data::image_dimens::SIZE_40;
                    bad_data_list.push_back({data::bad_data_reason::POKEMON_FRONT_IMAGE, i});
                }

                data::pokemons[i].front_image = (front_size == 0)
                                                    ? std::vector<u8>(IMG_55_SIZE, 0)
                                                    : std::vector<u8>(image_buffer.begin(), image_buffer.begin() + front_size);

                const auto back_ptr = romfile::get_bytes(0x48000 + i * 6 + 3, 3);
                const auto back_addr = addr::calc_from_encoded_bank(back_ptr);
                const auto back_size = romfile::read_lz_decompressed(image_buffer, back_addr, 0x400);

                image_addr_log(back_addr, romfile::calc_lz_size(back_addr, 0x400));

                if (back_size == 0)
                    bad_data_list.push_back({data::bad_data_reason::POKEMON_BACK_IMAGE, i});

                data::pokemons[i].back_image = (back_size == 0)
                                                   ? std::vector<u8>(IMG_66_SIZE, 0)
                                                   : std::vector<u8>(image_buffer.begin(), image_buffer.begin() + back_size);
            }
        }
    }

    debug_log("pokegold::open", "parse unown images");
    for (size_t i = 0; i < 26; i++)
    {
        // debug_log("pokegold::open", "  - {}", i);

        const auto front_ptr = romfile::get_bytes(0x7c000 + i * 6, 3);
        const auto front_addr = addr::calc_from_encoded_bank(front_ptr);
        const auto front_size = romfile::read_lz_decompressed(image_buffer, front_addr, 0x400);

        image_addr_log(front_addr, romfile::calc_lz_size(front_addr, 0x400));

        if (front_size == 0)
            bad_data_list.push_back({data::bad_data_reason::UNOWN_FRONT_IMAGE, i});

        data::unown_images[i].front = (front_size == 0)
                                          ? std::vector<u8>(IMG_55_SIZE, 0)
                                          : std::vector<u8>(image_buffer.begin(), image_buffer.begin() + front_size);

        const auto back_ptr = romfile::get_bytes(0x7c000 + i * 6 + 3, 3);
        const auto back_addr = addr::calc_from_encoded_bank(back_ptr);
        const auto back_size = romfile::read_lz_decompressed(image_buffer, back_addr, 0x400);

        image_addr_log(back_addr, romfile::calc_lz_size(back_addr, 0x400));

        if (back_size == 0)
            bad_data_list.push_back({data::bad_data_reason::UNOWN_BACK_IMAGE, i});

        data::unown_images[i].back = (back_size == 0)
                                         ? std::vector<u8>(IMG_66_SIZE, 0)
                                         : std::vector<u8>(image_buffer.begin(), image_buffer.begin() + back_size);
    }

    debug_log("pokegold::open", "trainers");
    size_t trainer_name_addr = addr::calc(romfile::get_bytes(0x35d5, 3));
    for (size_t i = 0; i < 67; i++)
    {
        data::trainer_groups[i].has_image = i != 66;

        const auto bytes = romfile::get_bytes_until(trainer_name_addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
        data::trainer_groups[i].name = bytes;
        trainer_name_addr += bytes.size();

        if (data::trainer_groups[i].name.has_bad_code())
        {
            data::trainer_groups[i].name = "[50]";
            bad_data_list.push_back({data::bad_data_reason::TRAINER_GROUP_NAME, i});
        }

        if (data::trainer_groups[i].has_image)
        {
            const auto img_addr = addr::calc_from_encoded_bank(romfile::get_bytes(0x80000 + (i * 3), 3));
            const auto img_size = romfile::read_lz_decompressed(image_buffer, img_addr, 0x400);

            image_addr_log(img_addr, romfile::calc_lz_size(img_addr, 0x400));

            if (img_size == 0)
                bad_data_list.push_back({data::bad_data_reason::TRAINER_IMAGE, i});

            data::trainer_groups[i].image = (img_size == 0)
                                                ? std::vector<u8>(IMG_77_SIZE, 0)
                                                : std::vector<u8>(image_buffer.begin(), image_buffer.begin() + img_size);

            data::trainer_groups[i].colors[0] = color(romfile::get_bytes(0xb511 + (i * 4) + 0, 2));
            data::trainer_groups[i].colors[1] = color(romfile::get_bytes(0xb511 + (i * 4) + 2, 2));
        }

        // debug_log("pokegold::open", "  - idx={}, name = \"{}\"", i, trainer_groups[i].name.string());
    }

    debug_log("pokegold::open", "types");
    for (size_t i = 0; i < 28; i++)
    {
        data::types[i].matchups.clear();
        data::types[i].weather_modifiers.clear();

        const size_t name_addr = addr::calc(0x14, romfile::get_bytes(0x50a57 + i * 2, 2));
        data::types[i].name = romfile::get_bytes_until(name_addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);

        if (data::types[i].name.has_bad_code())
        {
            data::types[i].name = "[50]";
            bad_data_list.push_back({data::bad_data_reason::TYPE_NAME, i});
        }

        // debug_log("pokegold::open", "  - idx={}, name = \"{}\"", i, types[i].name.editor_str());
    }

    const bool hacked_type_matchups = utils::match_bytes(romfile::data, 0x1fc7d4, {0xfe, 0xff});
    size_t type_matchups_addr = hacked_type_matchups ? addr::calc(romfile::get_bytes(0x348a7, 3)) : 0x34d01;
    size_t weather_type_modifiers_addr = hacked_type_matchups ? addr::calc(romfile::get_bytes(0x348aa, 3)) : 0xfbe68;
    size_t weather_move_modifiers_addr = hacked_type_matchups ? addr::calc(romfile::get_bytes(0x348ad, 3)) : 0xfbe75;

    debug_log("pokegold::open", "type matchups");
    bool foresight = false;
    while (true)
    {
        const u8 attacker = romfile::get_byte(type_matchups_addr++);
        if (attacker == 0xff)
            break;

        if (attacker == 0xfe)
        {
            foresight = true;
            continue;
        }

        const u8 defender = romfile::get_byte(type_matchups_addr++);
        const u8 effectiveness = romfile::get_byte(type_matchups_addr++);

        // 손상 데이터 체크 및 기본값 사용
        if (attacker >= data::types.size() || !(effectiveness % 5 == 0 && effectiveness <= 20))
        {
            type_matchups_addr = 0x34d01;
            romfile::set_bytes(0x34d01, embed::pokegold_default_type_matchups_bin);
            bad_data_list.push_back({data::bad_data_reason::TYPE_MATCHUPS, nullptr});
            continue;
        }

        data::type_matchup new_matchup;
        new_matchup.attacker_type_id = attacker;
        new_matchup.defender_type_id = defender;
        new_matchup.effectiveness = data::type_effectiveness(effectiveness);
        new_matchup.foresight = foresight;
        data::types[attacker].matchups.push_back(new_matchup);
    }

    debug_log("pokegold::open", "weather type modifiers");
    while (true)
    {
        const u8 weather = romfile::get_byte(weather_type_modifiers_addr++);
        if (weather == 0xff)
            break;

        const u8 type_id = romfile::get_byte(weather_type_modifiers_addr++);
        const u8 effectiveness = romfile::get_byte(weather_type_modifiers_addr++);

        // 손상 데이터 체크 및 기본값 사용
        if (type_id >= data::types.size() || weather > 3 || !(effectiveness % 5 == 0 && effectiveness <= 20))
        {
            weather_type_modifiers_addr = 0xfbe68;
            romfile::set_bytes(0xfbe68, embed::pokegold_default_weather_type_modifiers_bin);
            bad_data_list.push_back({data::bad_data_reason::WEATHER_TYPE_MODIFIERS, nullptr});
            continue;
        }

        data::weather_modifier new_weather_modifier;
        new_weather_modifier.weather = data::battle_weather(weather);
        new_weather_modifier.type_id = type_id;
        new_weather_modifier.effectiveness = data::type_effectiveness(effectiveness);
        data::types[type_id].weather_modifiers.push_back(new_weather_modifier);
    }

    debug_log("pokegold::open", "weather move modifiers");
    while (true)
    {
        const u8 weather = romfile::get_byte(weather_move_modifiers_addr++);
        if (weather == 0xff)
            break;

        const u8 move_id = romfile::get_byte(weather_move_modifiers_addr++);
        const u8 effectiveness = romfile::get_byte(weather_move_modifiers_addr++);

        // 손상 데이터 체크 및 기본값 사용
        if (move_id >= data::moves.size() || weather > 3 || !(effectiveness % 5 == 0 && effectiveness <= 20))
        {
            weather_move_modifiers_addr = 0xfbe75;
            romfile::set_bytes(0xfbe75, embed::pokegold_default_weather_move_modifiers_bin);
            bad_data_list.push_back({data::bad_data_reason::WEATHER_MOVE_MODIFIERS, nullptr});
            continue;
        }

        data::weather_modifier_move new_weather_modifier;
        new_weather_modifier.weather = data::battle_weather(weather);
        new_weather_modifier.move_id = move_id;
        new_weather_modifier.effectiveness = data::type_effectiveness(effectiveness);
        data::moves[move_id].weather_modifiers.push_back(new_weather_modifier);
    }

    debug_log("pokegold::open", "done");
    event::item_names_changed(-1);
    event::pokemon_names_changed(-1);
    event::move_names_changed(-1);
    event::hmtms_changed(-1);
    event::type_names_changed(-1);

    // MEMO: 손상 데이터를 내부적으로 처리하기 때문에 변경된 상태를 알림
    pokegold::romfile::is_changed = !bad_data_list.empty();

    event::rom_data_changed();
    event::rom_changed();

    return bad_data_list;
}
