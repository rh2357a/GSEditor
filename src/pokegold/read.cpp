#include "pokegold.h"
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
        debug_log("pokegold::read", s);
    }
}

std::vector<pokegold::data::bad_data> pokegold::read(const std::filesystem::path &filepath)
{
    using namespace pokegold::data;

    auto &data = pokegold::rom = filepath;

    workspace_path = utils::files::get_app_data_path() / "workspaces" / utils::crypto::hash(filepath.string());
    is_rom_opened = true;
    config::read();

    std::vector<bad_data> bad_data_list;
    std::vector<u8> image_buffer(0x400);

    debug_log("pokegold::read", "parse items");
    {
        debug_log("pokegold::read", "  - props");
        for (size_t i = 0; i < 256; i++)
        {
            // debug_log("pokegold::read", "    - {}", i);

            auto bytes = data.get_bytes(0x697b + i * 7, 7);

            auto &item = items[i];
            item.price = bytes[0] | (static_cast<u16>(bytes[1]) << 8);
            item.effect = bytes[2];
            item.parameter = bytes[3];
            item.property = bytes[4];
            item.pocket = bytes[5];
            item.field_menu = (bytes[6] & 0xf0) >> 4;
            item.battle_menu = bytes[6] & 0x0f;
        }

        debug_log("pokegold::read", "  - names");
        size_t name_addr = addr::calc(data.get_bytes(0x35cc, 3));
        for (size_t i = 0; i < 256; i++)
        {
            // debug_log("pokegold::read", "    - {}", i);

            const auto bytes = data.get_bytes_until(name_addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            name_addr += bytes.size();
            items[i].name = bytes;
        }

        debug_log("pokegold::read", "  - descriptions");
        u8 desc_bank = addr::calc_bank(0x1b8000);
        for (size_t i = 0; i < 256; i++)
        {
            // debug_log("pokegold::read", "    - {}", i);

            size_t addr = addr::calc(desc_bank, data.get_bytes(0x1b8000 + (i * 2), 2));
            const auto bytes = data.get_bytes_until(addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            items[i].description = bytes;
        }
    }

    debug_log("pokegold::read", "parse moves");
    {
        debug_log("pokegold::read", "  - props");
        for (size_t i = 0; i < 251; i++)
        {
            // debug_log("pokegold::read", "    - {}", i);

            auto bytes = data.get_bytes(0x4172e + i * 7, 7);

            auto &move = moves[i];
            move.id = bytes[0];
            move.effect = bytes[1];
            move.power = bytes[2];
            move.type = bytes[3];
            move.accuracy = bytes[4];
            move.pp = bytes[5];
            move.effect_chance = bytes[6];

            move.weather_modifiers.clear();
        }

        debug_log("pokegold::read", "  - names");
        size_t name_addr = addr::calc(data.get_bytes(0x35c6, 3));
        for (size_t i = 0; i < 251; i++)
        {
            // debug_log("pokegold::read", "    - {}", i);

            const auto bytes = data.get_bytes_until(name_addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            name_addr += bytes.size();
            moves[i].name = bytes;
        }

        debug_log("pokegold::read", "  - descriptions");
        u8 desc_bank = addr::calc_bank(0x1b4000);
        for (size_t i = 0; i < 251; i++)
        {
            // debug_log("pokegold::read", "    - {}", i);

            size_t addr = addr::calc(desc_bank, data.get_bytes(0x1b4000 + (i * 2), 2));
            const auto bytes = data.get_bytes_until(addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            moves[i].description = bytes;
        }
    }

    debug_log("pokegold::read", "parse TMHMs");
    for (size_t i = 0; i < 57; i++)
    {
        // debug_log("pokegold::read", "    - {}", i);
        tmhms[i] = data.get_byte(0x119f5 + i);
    }

    debug_log("pokegold::read", "parse pokemons");
    {
        const u8 evos_bank = addr::calc_bank(0x423ed);
        size_t evos_addr = 0x423ed;
        size_t mon_name_addr = addr::calc(data.get_bytes(0x35c3, 3));
        size_t props_addr = 0x51bdf;

        debug_log("pokegold::read", "  - props, name, pokedex");
        for (size_t i = 0; i < 256; i++)
        {
            // debug_log("pokegold::read", "    - {}", i);

            const auto bytes = data.get_bytes(props_addr, 32);
            props_addr += 32;

            auto &mon = pokemons[i];

            if (i == 200)
                mon.type = pokemon_type::UNOWN;
            else if (i == 252)
                mon.type = pokemon_type::EGG;
            else if (i < 251)
                mon.type = pokemon_type::POKEMON;
            else
                mon.type = pokemon_type::DUMMY;

            if (mon.type == pokemon_type::POKEMON || mon.type == pokemon_type::UNOWN)
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
                mon.gender_rate = gender_rate(bytes[13]);
                mon.egg_hatch_lv = bytes[15];
                mon.image_dimens = image_dimens(bytes[17]);
                mon.growth_rate = growth_rate(bytes[22]);
                mon.egg_group_1 = egg_group((bytes[23] & 0xf0) >> 4);
                mon.egg_group_2 = egg_group(bytes[23] & 0x0f);

                for (u8 j = 0; j < 8; j++)
                {
                    for (u8 a = 0; a < 8; a++)
                    {
                        u8 idx = (j * 8) + a;
                        mon.tmhms[idx] = (bytes[24 + j] & BITS[a]) != 0;
                    }
                }

                size_t evo_addr = addr::calc(evos_bank, data.get_bytes(evos_addr, 2));
                evos_addr += 2;

                mon.evolution_methods.clear();
                mon.learn_moves.clear();

                const auto evo_bytes = data.get_bytes_until(evo_addr, [&](size_t idx, u8 b) { return b == 0; }, true);
                bool bad_evolution_data = false;
                for (size_t j = 0; j < evo_bytes.size();)
                {
                    if (bad_evolution_data)
                        break;

                    evolution_method new_evolve;
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
                        // debug_log("pokegold::read", "bad evolution");
                        bad_evolution_data = true;
                        mon.evolution_methods.clear();
                        mon.learn_moves.clear();
                        bad_data_list.push_back({bad_data_reason::EVOLUTION_MOVES, i});
                        break;
                    }
                }

                if (!bad_evolution_data)
                {
                    const auto move_bytes = data.get_bytes_until(evo_addr + evo_bytes.size(), [&](size_t idx, u8 b) { return b == 0; }, true);
                    for (size_t j = 0; j < move_bytes.size();)
                    {
                        const u8 b = move_bytes[j++];
                        if (b == 0 || j >= move_bytes.size())
                            break;

                        learn_move new_item;
                        new_item.level = b;
                        new_item.move_id = move_bytes[j++];
                        mon.learn_moves.push_back(new_item);
                    }
                }

                size_t addr;
                if (i < 128)
                    addr = addr::calc(0x68, data.get_bytes(0x442ff + (i * 2), 2));
                else
                    addr = addr::calc(0x69, data.get_bytes(0x443ff + ((i - 128) * 2), 2));

                auto &mon = pokemons[i];

                mon.species_name = data.get_bytes_until(addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
                addr += mon.species_name.size();

                mon.height = data.get_byte(addr);
                addr += 1;

                mon.weight = data.get_byte(addr) | (data.get_byte(addr + 1) << 8);
                addr += 2;

                mon.description = data.get_bytes_until(addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            }

            mon.name = data.get_bytes_until(mon_name_addr, [&](size_t idx, u8 b) { return idx == 9 || b == 0x50; }, true);
            mon_name_addr += 10;
        }

        debug_log("pokegold::read", "  - image, color");
        for (size_t i = 0; i < 256; i++)
        {
            // debug_log("pokegold::read", "    - {}", i);

            const auto addr = 0xad15 + i * 8;
            pokemons[i].colors[0] = color(data.get_bytes(addr, 2));
            pokemons[i].colors[1] = color(data.get_bytes(addr + 2, 2));
            pokemons[i].shiny_colors[0] = color(data.get_bytes(addr + 4, 2));
            pokemons[i].shiny_colors[1] = color(data.get_bytes(addr + 6, 2));

            if (pokemons[i].type == pokemon_type::UNOWN || pokemons[i].type == pokemon_type::DUMMY)
                continue;

            if (pokemons[i].type == pokemon_type::EGG)
            {
                const size_t front_addr = addr::calc(data.get_byte(0x5189a), data.get_bytes(0x51897, 2));
                const auto front_size = data.read_lz_decompressed(image_buffer, front_addr, 0x400);

                if (front_size == 0)
                    bad_data_list.push_back({bad_data_reason::EGG_IMAGE, nullptr});

                pokemons[i].front_image = (front_size == 0)
                                              ? std::vector<u8>(IMG_55_SIZE, 0)
                                              : std::vector<u8>(image_buffer.begin(), image_buffer.begin() + front_size);
            }
            else
            {
                const auto front_ptr = data.get_bytes(0x48000 + i * 6, 3);
                const auto front_addr = addr::calc_from_encoded_bank(front_ptr);
                const auto front_size = data.read_lz_decompressed(image_buffer, front_addr, 0x400);

                image_addr_log(front_addr, data.calc_lz_size(front_addr, 0x400));

                if (front_size == 0)
                {
                    pokemons[i].image_dimens = image_dimens::SIZE_40;
                    bad_data_list.push_back({bad_data_reason::POKEMON_FRONT_IMAGE, i});
                }

                pokemons[i].front_image = (front_size == 0)
                                              ? std::vector<u8>(IMG_55_SIZE, 0)
                                              : std::vector<u8>(image_buffer.begin(), image_buffer.begin() + front_size);

                const auto back_ptr = data.get_bytes(0x48000 + i * 6 + 3, 3);
                const auto back_addr = addr::calc_from_encoded_bank(back_ptr);
                const auto back_size = data.read_lz_decompressed(image_buffer, back_addr, 0x400);

                image_addr_log(back_addr, data.calc_lz_size(back_addr, 0x400));

                if (back_size == 0)
                    bad_data_list.push_back({bad_data_reason::POKEMON_BACK_IMAGE, i});

                pokemons[i].back_image = (back_size == 0)
                                             ? std::vector<u8>(IMG_66_SIZE, 0)
                                             : std::vector<u8>(image_buffer.begin(), image_buffer.begin() + back_size);
            }
        }
    }

    debug_log("pokegold::read", "parse unown images");
    for (size_t i = 0; i < 26; i++)
    {
        // debug_log("pokegold::read", "  - {}", i);

        const auto front_ptr = data.get_bytes(0x7c000 + i * 6, 3);
        const auto front_addr = addr::calc_from_encoded_bank(front_ptr);
        const auto front_size = data.read_lz_decompressed(image_buffer, front_addr, 0x400);

        image_addr_log(front_addr, data.calc_lz_size(front_addr, 0x400));

        if (front_size == 0)
            bad_data_list.push_back({bad_data_reason::UNOWN_FRONT_IMAGE, i});

        unown_images[i].front = (front_size == 0)
                                    ? std::vector<u8>(IMG_55_SIZE, 0)
                                    : std::vector<u8>(image_buffer.begin(), image_buffer.begin() + front_size);

        const auto back_ptr = data.get_bytes(0x7c000 + i * 6 + 3, 3);
        const auto back_addr = addr::calc_from_encoded_bank(back_ptr);
        const auto back_size = data.read_lz_decompressed(image_buffer, back_addr, 0x400);

        image_addr_log(back_addr, data.calc_lz_size(back_addr, 0x400));

        if (back_size == 0)
            bad_data_list.push_back({bad_data_reason::UNOWN_BACK_IMAGE, i});

        unown_images[i].back = (back_size == 0)
                                   ? std::vector<u8>(IMG_66_SIZE, 0)
                                   : std::vector<u8>(image_buffer.begin(), image_buffer.begin() + back_size);
    }

    debug_log("pokegold::read", "trainers");
    size_t trainer_name_addr = addr::calc(data.get_bytes(0x35d5, 3));
    for (size_t i = 0; i < 67; i++)
    {
        trainer_groups[i].has_image = i != 66;

        const auto bytes = data.get_bytes_until(trainer_name_addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);
        trainer_groups[i].name = bytes;
        trainer_name_addr += bytes.size();

        if (trainer_groups[i].has_image)
        {
            const auto img_addr = addr::calc_from_encoded_bank(data.get_bytes(0x80000 + (i * 3), 3));
            const auto img_size = data.read_lz_decompressed(image_buffer, img_addr, 0x400);

            image_addr_log(img_addr, data.calc_lz_size(img_addr, 0x400));

            if (img_size == 0)
                bad_data_list.push_back({bad_data_reason::TRAINER_IMAGE, i});

            trainer_groups[i].image = (img_size == 0)
                                          ? std::vector<u8>(IMG_77_SIZE, 0)
                                          : std::vector<u8>(image_buffer.begin(), image_buffer.begin() + img_size);

            trainer_groups[i].colors[0] = color(data.get_bytes(0xb511 + (i * 4) + 0, 2));
            trainer_groups[i].colors[1] = color(data.get_bytes(0xb511 + (i * 4) + 2, 2));
        }

        // debug_log("pokegold::read", "  - idx={}, name = \"{}\"", i, trainer_groups[i].name.string());
    }

    debug_log("pokegold::read", "types");
    for (size_t i = 0; i < 28; i++)
    {
        types[i].matchups.clear();
        types[i].weather_modifiers.clear();

        const size_t name_addr = addr::calc(0x14, data.get_bytes(0x50a57 + i * 2, 2));
        types[i].name = data.get_bytes_until(name_addr, [&](size_t idx, u8 b) { return b == 0x50; }, true);

        // debug_log("pokegold::read", "  - idx={}, name = \"{}\"", i, types[i].name.u8string());
    }

    const bool hacked_type_matchups = utils::match_bytes(data.data(), 0x34890, {0x21, 0x01, 0x4d, 0x2a});
    size_t type_matchups_addr = hacked_type_matchups ? 0x34d01 : addr::calc(data.get_bytes(0x348a7, 3));
    size_t weather_type_modifiers_addr = hacked_type_matchups ? 0xfbe68 : addr::calc(data.get_bytes(0x348aa, 3));
    size_t weather_move_modifiers_addr = hacked_type_matchups ? 0xfbe75 : addr::calc(data.get_bytes(0x348ad, 3));

    debug_log("pokegold::read", "type matchups");
    bool foresight = false;
    while (true)
    {
        const u8 attacker = data.get_byte(type_matchups_addr++);
        if (attacker == 0xff)
            break;

        if (attacker == 0xfe)
        {
            foresight = true;
            continue;
        }

        const u8 defender = data.get_byte(type_matchups_addr++);
        const u8 effectiveness = data.get_byte(type_matchups_addr++);

        type_matchup new_matchup;
        new_matchup.attacker_type_id = attacker;
        new_matchup.defender_type_id = defender;
        new_matchup.effectiveness = type_effectiveness(effectiveness);
        new_matchup.foresight = foresight;
        types[attacker].matchups.push_back(new_matchup);
    }

    debug_log("pokegold::read", "weather type modifiers");
    while (true)
    {
        const u8 weather = data.get_byte(weather_type_modifiers_addr++);
        if (weather == 0xff)
            break;

        const u8 type_id = data.get_byte(weather_type_modifiers_addr++);
        const u8 effectiveness = data.get_byte(weather_type_modifiers_addr++);

        weather_modifier new_weather_modifier;
        new_weather_modifier.weather = battle_weather(weather);
        new_weather_modifier.type_id = type_id;
        new_weather_modifier.effectiveness = type_effectiveness(effectiveness);
        types[type_id].weather_modifiers.push_back(new_weather_modifier);
    }

    debug_log("pokegold::read", "weather move modifiers");
    while (true)
    {
        const u8 weather = data.get_byte(weather_move_modifiers_addr++);
        if (weather == 0xff)
            break;

        const u8 move_id = data.get_byte(weather_move_modifiers_addr++);
        const u8 effectiveness = data.get_byte(weather_move_modifiers_addr++);

        weather_modifier_move new_weather_modifier;
        new_weather_modifier.weather = battle_weather(weather);
        new_weather_modifier.move_id = move_id;
        new_weather_modifier.effectiveness = type_effectiveness(effectiveness);
        moves[move_id].weather_modifiers.push_back(new_weather_modifier);
    }

    debug_log("pokegold::read", "done");
    return bad_data_list;
}
