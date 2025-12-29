#include "pokegold.h"

#include "lib/lzcomp.h"
#include "embed.h"
#include "utils.h"

#include <functional>
#include <string>
#include <format>
#include <filesystem>
#include <fstream>
#include <array>
#include <unordered_map>

class data_block
{
public:
    std::string label;
    pokegold::bytes data;

public:
    data_block(const std::string &l, pokegold::bytes d) : label(l), data(d) {}
    ~data_block() = default;
};

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

const std::vector<std::array<size_t, 2>> TYPE_NAME_FREE_SPACES{
    {0x050a8f, 0x050ae9},
    {0x053b57, 0x053be8},
};

const std::vector<std::array<size_t, 2>> IMAGE_FREE_SPACES{
    {0x0485e2, 0x04bfff},
    {0x054000, 0x057fff},
    {0x058000, 0x05bfff},
    {0x05c000, 0x05ffff},
    {0x060000, 0x063fff},
    {0x064000, 0x067fff},
    {0x068000, 0x06bfff},
    {0x06c000, 0x06ffff},
    {0x070000, 0x073fff},
    {0x074000, 0x077fff},
    {0x078000, 0x07bfff},
    {0x07c09c, 0x07ffff},
    {0x0800c6, 0x083fff},
    {0x0b8000, 0x0ba2ff},

    // 추가 빈공간
    {0x088000, 0x08bfff},
    {0x09c000, 0x09ffff},
    {0x0a0000, 0x0a3fff},
    {0x0a4000, 0x0a7fff},
    {0x0b0000, 0x0b3fff},
    {0x0b4000, 0x0b7fff},
    {0x0bc000, 0x0bffff},
    {0x0d0000, 0x0d3fff},
    {0x0d4000, 0x0d7fff},
    {0x160000, 0x163fff},
    {0x18c000, 0x18ffff},
    {0x1a8000, 0x1abfff},
    {0x1ac000, 0x1affff},
    {0x1bc000, 0x1bffff},
    {0x1cc000, 0x1cffff},
    {0x1d0000, 0x1d3fff},
    {0x1d4000, 0x1d7fff},
    {0x1f0000, 0x1f3fff},
    {0x1f4000, 0x1f7fff},
    {0x1f8000, 0x1fbfff},
};

template <typename... _Args>
std::string asm_section(size_t address, std::format_string<_Args...> fmt, _Args &&...args)
{
    u8 bank = address / 0x4000;
    u16 ptr = address % 0x4000 + (address >= 0x4000 ? 0x4000 : 0);
    std::string name = std::format(fmt, std::forward<_Args>(args)...);
    return bank == 0
               ? std::format("SECTION \"{}\",ROM0[{}]\n", name, ptr)
               : std::format("SECTION \"{}\",ROMX[{}],BANK[{}]\n", name, ptr, bank);
}

template <typename... _Args>
std::string asm_line(std::format_string<_Args...> fmt, _Args &&...args)
{
    return std::format(fmt, std::forward<_Args>(args)...) + '\n';
}

std::string asm_include(const std::string &path)
{
    return std::format("INCLUDE \"{}\"\n", path);
}

std::string asm_bytes(std::span<const u8> bytes)
{
    std::ostringstream oss;

    oss << "db ";

    bool first = true;
    for (auto b : bytes)
    {
        if (!first)
            oss << ',';
        first = false;
        oss << +b;
    }

    oss << '\n';

    return oss.str();
}

std::string asm_bytes(std::initializer_list<u8> il)
{
    return asm_bytes(std::span<const u8>(il.begin(), il.end()));
}

/// @brief FFD 기준으로 데이터 블록을 정리
/// @param free_spaces 메모리 공간 모음
/// @param data_blocks 입력 데이터 블록
/// @return 배치된 데이터 블록
std::vector<std::vector<data_block>> first_fit_decreasing(const std::vector<std::array<size_t, 2>> &free_spaces,
                                                          std::vector<data_block> &data_blocks)
{
    std::vector<std::vector<data_block>> result(free_spaces.size());

    std::vector<size_t> cur_addrs;
    for (const auto &e : free_spaces)
        cur_addrs.push_back(e[0]);

    std::vector<std::reference_wrapper<data_block>> sorted_blocks;
    for (auto &label : data_blocks)
        sorted_blocks.push_back(label);

    std::sort(
        sorted_blocks.begin(),
        sorted_blocks.end(),
        [&](const data_block &a, const data_block &b) {
            return a.data.size() > b.data.size();
        });

    for (const auto &label : sorted_blocks)
    {
        size_t size = label.get().data.size();
        for (size_t j = 0; j < free_spaces.size(); j++)
        {
            if (cur_addrs[j] + size < free_spaces[j][1])
            {
                result[j].push_back(label.get());
                cur_addrs[j] += size;
                break;
            }
        }
    }

    return result;
}

void generate_macros_source(const std::filesystem::path &workdir, std::ofstream &top_src)
{
    constexpr auto src_name = "gs_editor_macros.asm";
    top_src << asm_include(src_name);

    std::ofstream src(workdir / src_name);
    src.write(reinterpret_cast<const char *>(embed::pokegold_macros_asm.data()), embed::pokegold_macros_asm.size());
    src.close();
}

void generate_cleanup_source(const std::filesystem::path &workdir, std::ofstream &top_src)
{
    constexpr auto src_name = "gs_editor_cleanup.asm";
    top_src << asm_include(src_name);

    std::ofstream src(workdir / src_name);

    src << asm_section(0x1a0000, "GSEditor_Cleanup_Pokedex_0")
        << asm_line("ds $4000")
        << asm_section(0x1a4000, "GSEditor_Cleanup_Pokedex_1")
        << asm_line("ds $4000")
        << asm_section(0x1b0000, "GSEditor_Cleanup_Strings_0")
        << asm_line("ds $4000")

        << asm_section(0x1b4000, "GSEditor_Cleanup_Strings_1")
        << asm_line("ds $4000")
        << asm_section(0x1b8000, "GSEditor_Cleanup_Strings_2")
        << asm_line("ds $4000")

        << asm_section(0x53b57, "GSEditor_Cleanup_EggImage")
        << asm_line("ds 146");

    for (auto free_space : TYPE_NAME_FREE_SPACES)
    {
        src << asm_section(free_space[0], "GSEditor_Cleanup_TypeNameFreeSpace_0x{:x}", free_space[0])
            << asm_line("ds {}", free_space[1] - free_space[0] + 1);
    }

    for (auto free_space : IMAGE_FREE_SPACES)
    {
        src << asm_section(free_space[0], "GSEditor_Cleanup_ImageFreeSpace_0x{:x}", free_space[0])
            << asm_line("ds {}", free_space[1] - free_space[0] + 1);
    }

    src.close();
}

void generate_pokegold_source(const std::filesystem::path &workdir, std::ofstream &top_src)
{
    constexpr auto src_name = "gs_editor_pokegold.asm";
    top_src << asm_include(src_name);

    std::ofstream src(workdir / src_name);

    debug_log("pokegold::build", "generate items");
    src << asm_section(0x697b, "GSEditor_Item_Properties")
        << asm_line("GSEditor_Item_Properties::");
    for (size_t i = 0; i < 256; i++)
    {
        const auto &e = pokegold::data::items[i];
        src << asm_bytes({
            u8(e.price & 0xff),
            u8((e.price >> 8) & 0xff),
            e.effect,
            e.parameter,
            e.property,
            e.pocket,
            u8(((e.field_menu & 0x0f) << 4) | (e.battle_menu & 0x0f)),
        });
    }

    debug_log("pokegold::build", "generate move");
    src << asm_section(0x4172e, "GSEditor_Move_Properties")
        << asm_line("GSEditor_Move_Properties::");
    for (size_t i = 0; i < 251; i++)
    {
        const auto &e = pokegold::data::moves[i];
        src << asm_bytes({
            e.id,
            e.effect,
            e.power,
            e.type,
            e.accuracy,
            e.pp,
            e.effect_chance,
        });
    }

    debug_log("pokegold::build", "generate tmhms");
    src << asm_section(0x119f5, "GSEditor_TMHMs")
        << asm_line("GSEditor_TMHMs::")
        << asm_bytes(pokegold::data::tmhms);

    debug_log("pokegold::build", "generate pokemon");
    {
        src << asm_section(0x51bdf, "GSEditor_Pokemon_Properties")
            << asm_line("GSEditor_Pokemon_Properties::");
        for (size_t i = 0; i < 251; i++)
        {
            const auto &e = pokegold::data::pokemons[i];

            std::array<u8, 8> tmhms{0};
            for (u8 j = 0; j < 8; j++)
            {
                for (u8 a = 0; a < 8; a++)
                {
                    u8 idx = (j * 8) + a;
                    if (e.tmhms[idx])
                        tmhms[j] |= BITS[a];
                }
            }

            src << asm_bytes({
                e.id,
                e.hp,
                e.atk,
                e.def,
                e.spd,
                e.sp_atk,
                e.sp_def,
                e.type_1_id,
                e.type_2_id,
                e.catch_rate,
                e.base_exp,
                e.item_1_id,
                e.item_2_id,
                u8(e.gender_rate),
                100,
                e.egg_hatch_lv,
                5,
                u8(e.image_dimens),
                0,
                0,
                0,
                0,
                u8(e.growth_rate),
                u8(((u8(e.egg_group_1) & 0x0f) << 4) | (u8(e.egg_group_2) & 0x0f)),
                tmhms[0],
                tmhms[1],
                tmhms[2],
                tmhms[3],
                tmhms[4],
                tmhms[5],
                tmhms[6],
                tmhms[7],
            });
        }

        src << asm_section(0x425e3, "GSEditor_Pokemon_EvoMoves")
            << asm_line("GSEditor_Pokemon_EvoMoves::");
        for (size_t i = 0; i < 251; i++)
        {
            src << asm_line("GSEditor_Pokemon_EvoMove_{}:", i);

            const auto &e = pokegold::data::pokemons[i];

            std::vector<u8> evomoves;

            for (const auto &evo : e.evolution_methods)
            {
                switch (evo.evolution_type)
                {
                case 1:
                    evomoves.push_back(evo.evolution_type);
                    evomoves.push_back(evo.level);
                    evomoves.push_back(evo.pokemon_id);
                    break;
                case 2:
                case 3:
                    evomoves.push_back(evo.evolution_type);
                    evomoves.push_back(evo.item_id);
                    evomoves.push_back(evo.pokemon_id);
                    break;
                case 4:
                    evomoves.push_back(evo.evolution_type);
                    evomoves.push_back(evo.happiness);
                    evomoves.push_back(evo.pokemon_id);
                    break;
                case 5:
                    evomoves.push_back(evo.evolution_type);
                    evomoves.push_back(evo.level);
                    evomoves.push_back(evo.stats);
                    evomoves.push_back(evo.pokemon_id);
                    break;
                }
            }

            evomoves.push_back(0);

            for (const auto &move : e.learn_moves)
            {
                evomoves.push_back(move.level);
                evomoves.push_back(move.move_id);
            }

            evomoves.push_back(0);

            src << asm_bytes(evomoves);
        }

        src << asm_section(0x423ed, "GSEditor_Pokemon_EvoMove_Pointers")
            << asm_line("GSEditor_Pokemon_EvoMove_Pointers::");
        for (size_t i = 0; i < 251; i++)
            src << asm_line("dw GSEditor_Pokemon_EvoMove_{}", i);
    }

    debug_log("pokegold::build", "generate pokedex");
    {
        src << asm_section(0x1a0000, "GSEditor_Pokedex_0");

        for (size_t i = 0; i < 128; i++)
        {
            src << asm_line("GSEditor_Pokedex_{}:", i);

            const auto &e = pokegold::data::pokemons[i];

            std::vector<u8> dex_bytes;
            dex_bytes.insert(dex_bytes.end(), e.species_name.begin(), e.species_name.end());
            dex_bytes.push_back(e.height);
            dex_bytes.push_back(u8(e.weight & 0x00ff));
            dex_bytes.push_back(u8((e.weight & 0xff00) >> 8));
            dex_bytes.insert(dex_bytes.end(), e.description.begin(), e.description.end());

            src << asm_bytes(dex_bytes);
        }

        src << asm_section(0x442ff, "GSEditor_Pokedex_0_Pointers")
            << asm_line("GSEditor_Pokedex_0_Pointers::");
        for (size_t i = 0; i < 128; i++)
            src << asm_line("dw GSEditor_Pokedex_{}", i);

        src << asm_section(0x1a4000, "GSEditor_Pokedex_1");
        for (size_t i = 0; i < 123; i++)
        {
            src << asm_line("GSEditor_Pokedex_{}:", i + 128);

            const auto &e = pokegold::data::pokemons[i + 128];

            std::vector<u8> dex_bytes;
            dex_bytes.insert(dex_bytes.end(), e.species_name.begin(), e.species_name.end());
            dex_bytes.push_back(e.height);
            dex_bytes.push_back(u8(e.weight & 0x00ff));
            dex_bytes.push_back(u8((e.weight & 0xff00) >> 8));
            dex_bytes.insert(dex_bytes.end(), e.description.begin(), e.description.end());

            src << asm_bytes(dex_bytes);
        }

        src << asm_section(0x443ff, "GSEditor_Pokedex_1_Pointers")
            << asm_line("GSEditor_Pokedex_1_Pointers::");
        for (size_t i = 0; i < 123; i++)
            src << asm_line("dw GSEditor_Pokedex_{}", i + 128);
    }

    debug_log("pokegold::build", "generate images");
    {
        src << asm_section(0xad15, "GSEditor_Pokemon_Colors")
            << asm_line("GSEditor_Pokemon_Colors::");
        for (const auto &e : pokegold::data::pokemons)
        {
            src << asm_bytes({
                e.colors[0].lo_byte(),
                e.colors[0].hi_byte(),
                e.colors[1].lo_byte(),
                e.colors[1].hi_byte(),
                e.shiny_colors[0].lo_byte(),
                e.shiny_colors[0].hi_byte(),
                e.shiny_colors[1].lo_byte(),
                e.shiny_colors[1].hi_byte(),
            });
        }

        src << asm_section(0xb511, "GSEditor_TrainerGroup_Colors")
            << asm_line("GSEditor_TrainerGroup_Colors::");
        for (const auto &e : pokegold::data::trainer_groups)
        {
            if (e.has_image)
            {
                src << asm_bytes({
                    e.colors[0].lo_byte(),
                    e.colors[0].hi_byte(),
                    e.colors[1].lo_byte(),
                    e.colors[1].hi_byte(),
                });
            }
        }

        std::vector<data_block> data_blocks;
        std::vector<u8> compressed_buffer(0x400);
        auto img_push = [&](const std::string &label, const pokegold::bytes &data) {
            const auto size = lzcomp::compress(compressed_buffer, data);
            data_blocks.push_back({
                label,
                std::vector<u8>(std::begin(compressed_buffer), std::begin(compressed_buffer) + size),
            });
        };

        for (size_t i = 0; i < 251; i++)
        {
            if (i == 200)
                continue;
            img_push(std::format("GSEditor_Pokemon_FrontImage_{}", i), pokegold::data::pokemons[i].front_image);
            img_push(std::format("GSEditor_Pokemon_BackImage_{}", i), pokegold::data::pokemons[i].back_image);
        }

        for (size_t i = 0; i < 26; i++)
        {
            img_push(std::format("GSEditor_Unown_FrontImage_{}", i), pokegold::data::unown_images[i].front);
            img_push(std::format("GSEditor_Unown_BackImage_{}", i), pokegold::data::unown_images[i].back);
        }

        for (size_t i = 0; i < 66; i++)
            img_push(std::format("GSEditor_TrainerGroup_Image_{}", i), pokegold::data::trainer_groups[i].image);

        img_push("GSEditor_Egg_Image", pokegold::data::pokemons[252].front_image);

        const auto ffd_data_blocks = first_fit_decreasing(IMAGE_FREE_SPACES, data_blocks);

        // 압축, 배치 사이즈 로깅
#ifdef DEBUG
        size_t cnt = 0;
        for (const auto &label : ffd_data_blocks)
        {
            if (!label.empty())
            {
                size_t size = 0;
                for (const auto &e : label)
                    size += e.data.size();

                debug_log("pokegold::build", "compiled image (index={}, label_size={}, data_size={})", cnt, label.size(), size);
                cnt++;
            }
        }
#endif

        // 데이터 기록
        for (size_t i = 0; i < IMAGE_FREE_SPACES.size(); i++)
        {
            if (ffd_data_blocks[i].empty())
                continue;

            src << asm_section(IMAGE_FREE_SPACES[i][0], "GSEditor_Images_0x{:x}", IMAGE_FREE_SPACES[i][0])
                << asm_line("GSEditor_Images_0x{:x}::", IMAGE_FREE_SPACES[i][0]);
            for (const auto &e : ffd_data_blocks[i])
            {
                src << asm_line("{}:", e.label)
                    << asm_bytes(e.data);
            }
        }

        // 포인터 기록
        {
            src << asm_section(0x51897, "GSEditor_Egg_Image_Pointer")
                << asm_line("dw GSEditor_Egg_Image");
            src << asm_section(0x5189a, "GSEditor_Egg_Image_Bank")
                << asm_line("db BANK(GSEditor_Egg_Image)");

            src << asm_section(0x48000, "GSEditor_Pokemon_Image_Pointers");
            for (size_t i = 0; i < 251; i++)
            {
                const auto &e = pokegold::data::pokemons[i];
                if (e.type == pokegold::data::pokemon_type::POKEMON)
                {
                    src << asm_line("gsepics Pokemon,{}", i);
                }
                else
                {
                    src << asm_line("dbw -1,-1");
                    src << asm_line("dbw -1,-1");
                }
            }

            src << asm_section(0x7c000, "GSEditor_Unown_Image_Pointers");
            for (size_t i = 0; i < 26; i++)
                src << asm_line("gsepics Unown,{}", i);

            src << asm_section(0x80000, "GSEditor_TrainerGroup_Image_Pointers");
            for (size_t i = 0; i < 66; i++)
                src << asm_line("gsepic TrainerGroup,{}", i);
        }
    }

    // names
    {
        pokegold::address names_addr(0x1b0000);

        debug_log("pokegold::build", "generate items name");
        {
            src << asm_section(0x35cc, "GSEditor_Item_Names_Pointer_0")
                << asm_line("db BANK(GSEditor_Item_Names)")
                << asm_section(0x515cd, "GSEditor_Item_Names_Pointer_1")
                << asm_line("dw GSEditor_Item_Names")
                << asm_section(0x515d7, "GSEditor_Item_Names_Pointer_2")
                << asm_line("dw GSEditor_Item_Names")

                << asm_section(names_addr.offset(), "GSEditor_Item_Names")
                << asm_line("GSEditor_Item_Names::");
            for (size_t i = 0; i < 256; i++)
            {
                const auto &e = pokegold::data::items[i];
                src << asm_bytes(e.name);
                names_addr += e.name.size();
            }
        }

        debug_log("pokegold::build", "generate trainer group name");
        {
            src << asm_section(0x35d5, "GSEditor_TrainerGroup_Names_Pointer")
                << asm_line("db BANK(GSEditor_TrainerGroup_Names)")
                << asm_line("dw GSEditor_TrainerGroup_Names")

                << asm_section(names_addr.offset(), "GSEditor_TrainerGroup_Names")
                << asm_line("GSEditor_TrainerGroup_Names::");
            for (size_t i = 0; i < 67; i++)
            {
                const auto &e = pokegold::data::trainer_groups[i];
                src << asm_bytes(e.name);
                names_addr += e.name.size();
            }
        }

        debug_log("pokegold::build", "generate pokemon name");
        {
            src << asm_section(0x35c3, "GSEditor_Pokemon_Names_Pointer_0")
                << asm_line("db BANK(GSEditor_Pokemon_Names)")
                << asm_section(0x3667, "GSEditor_Pokemon_Names_Pointer_1")
                << asm_line("dw GSEditor_Pokemon_Names")
                << asm_section(0x515bf, "GSEditor_Pokemon_Names_Pointer_2")
                << asm_line("dw GSEditor_Pokemon_Names")

                << asm_section(names_addr.offset(), "GSEditor_Pokemon_Names")
                << asm_line("GSEditor_Pokemon_Names::");
            for (size_t i = 0; i < 256; i++)
            {
                const auto &e = pokegold::data::pokemons[i];

                std::array<u8, 10> padded;
                std::fill(padded.begin(), padded.end(), 0x50);
                for (size_t j = 0; j < e.name.size(); j++)
                    padded[j] = e.name[j];

                src << asm_bytes(padded);
                names_addr += 10;
            }
        }

        debug_log("pokegold::build", "generate move name");
        {
            src << asm_section(0x35c6, "GSEditor_Move_Names_Pointer")
                << asm_line("db BANK(GSEditor_Move_Names)")
                << asm_line("dw GSEditor_Move_Names")

                << asm_section(names_addr.offset(), "GSEditor_Move_Names")
                << asm_line("GSEditor_Move_Names::");
            for (size_t i = 0; i < 251; i++)
            {
                const auto &e = pokegold::data::moves[i];
                src << asm_bytes(e.name);
                names_addr += e.name.size();
            }
        }
    }

    // item descriptions
    {
        debug_log("pokegold::build", "generate item description");
        std::unordered_map<std::string, std::string> item_label_map;
        std::array<std::string, 256> item_labels;
        pokegold::address item_ptr_addr(0x1b8000);
        pokegold::address item_addr(0x1b8200);

        src << asm_section(item_addr.offset(), "GSEditor_Item_Descriptions")
            << asm_line("GSEditor_Item_Descriptions::");
        for (size_t i = 0; i < 256; i++)
        {
            const auto label = std::format("GSEditor_Item_Description_{}", i);
            auto &e = pokegold::data::items[i].description;

            if (item_label_map.contains(e.string()))
            {
                item_labels[i] = item_label_map[e.string()];
            }
            else
            {
                src << asm_line("{}:", label)
                    << asm_bytes(e);
                item_addr += e.size();
                item_label_map[e.string()] = label;
                item_labels[i] = label;
            }
        }

        src << asm_section(item_ptr_addr.offset(), "GSEditor_Item_Description_Pointers")
            << asm_line("GSEditor_Item_Description_Pointers::");
        for (size_t i = 0; i < 256; i++)
            src << asm_line("dw {}", item_labels[i]);
    }

    // move descriptions
    {
        debug_log("pokegold::build", "generate move description");
        std::unordered_map<std::string, std::string> move_label_map;
        std::array<std::string, 256> move_labels;
        pokegold::address move_ptr_addr(0x1b4000);
        pokegold::address move_addr(0x1b4200);

        src << asm_section(move_addr.offset(), "GSEditor_Move_Descriptions")
            << asm_line("GSEditor_Move_Descriptions::")
            << asm_line("GSEditor_Move_Description_0:")
            << asm_bytes({230, 80});
        for (size_t i = 0; i < 251; i++)
        {
            const auto label = std::format("GSEditor_Move_Description_{}", i + 1);
            auto &e = pokegold::data::moves[i].description;

            if (move_label_map.contains(e.string()))
            {
                move_labels[i] = move_label_map[e.string()];
            }
            else
            {
                src << asm_line("{}:", label)
                    << asm_bytes(e);
                move_addr += e.size();
                move_label_map[e.string()] = label;
                move_labels[i] = label;
            }
        }

        src << asm_section(move_ptr_addr.offset(), "GSEditor_Move_Description_Pointers")
            << asm_line("GSEditor_Move_Description_Pointers::");
        for (size_t i = 0; i < 251; i++)
            src << asm_line("dw {}", move_labels[i]);
        for (size_t i = 0; i < 5; i++)
            src << asm_line("dw GSEditor_Move_Description_0");
    }

    // tpye names
    {
        std::vector<data_block> data_blocks;
        for (size_t i = 0; i < 28; i++)
        {
            const auto &e = pokegold::data::types[i];
            data_blocks.push_back({
                std::format("GSEditor_Type_Name_{}", i),
                std::vector<u8>(e.name.begin(), e.name.end()),
            });
        }

        const auto ffd_data_blocks = first_fit_decreasing(TYPE_NAME_FREE_SPACES, data_blocks);
        for (size_t i = 0; i < TYPE_NAME_FREE_SPACES.size(); i++)
        {
            if (ffd_data_blocks[i].empty())
                continue;

            pokegold::address addr(TYPE_NAME_FREE_SPACES[i][0]);
            src << asm_section(TYPE_NAME_FREE_SPACES[i][0], "GSEditor_Type_Name_0x{:x}", TYPE_NAME_FREE_SPACES[i][0])
                << asm_line("GSEditor_Type_Name_0x{:x}::", TYPE_NAME_FREE_SPACES[i][0]);
            for (const auto &e : ffd_data_blocks[i])
            {
                src << asm_line("{}:", e.label)
                    << asm_bytes(e.data);
            }
        }

        src << asm_section(0x50a57, "GSEditor_Type_Name_Pointers")
            << asm_line("GSEditor_Type_Name_Pointers::");
        for (size_t i = 0; i < 28; i++)
            src << asm_line("dw GSEditor_Type_Name_{}", i);
    }

    src.close();
}

std::vector<u8> pokegold::build()
{
    const auto workdir = workspace_path / "workspace";
    const auto base_path = workdir / "base.bin";
    const auto target_path = workdir / "target.bin";
    const auto target_map_path = workdir / "target.map";
    const auto target_sym_path = workdir / "target.sym";
    const auto src_path = workdir / "gs_editor.asm";
    const auto obj_path = workdir / "gs_editor.o";

    debug_log("pokegold::build", "cleanup (path=\"{}\")", workdir.string());
    std::filesystem::remove_all(workdir);
    std::filesystem::create_directories(workdir);

    debug_log("pokegold::build", "copy baserom");
    utils::files::write_bytes_to_file(base_path, rom.data());

    debug_log("pokegold::build", "generate sources");
    std::ofstream src(src_path);
    generate_macros_source(workdir, src);
    generate_cleanup_source(workdir, src);
    generate_pokegold_source(workdir, src);
    src.close();

    const auto rgbasm_args = std::format("-o {} {}", obj_path.string(), src_path.string());
    debug_log("pokegold::build", "rgbasm {}", rgbasm_args);
    const auto rgbasm_result = utils::rgbasm(rgbasm_args, workdir.string());
    debug_log("pokegold::build", "\n{}", rgbasm_result.output);

    const auto rgblink_args = std::format(
        "--map {} --sym {} -o {} -O {} {}",
        target_map_path.string(),
        target_sym_path.string(),
        target_path.string(),
        base_path.string(),
        obj_path.string());
    debug_log("pokegold::build", "rgblink {}", rgblink_args);
    const auto rgblink_result = utils::rgblink(rgblink_args, workdir.string());
    debug_log("pokegold::build", "\n{}", rgblink_result.output);

    const auto rgbfix_args = std::format("-v -Wno-overwrite {}", target_path.string());
    debug_log("pokegold::build", "rgbfix {}", rgbfix_args);
    const auto rgbfix_result = utils::rgbfix(rgbfix_args, workdir.string());
    debug_log("pokegold::build", "\n{}", rgbfix_result.output);

    const auto result = utils::files::read_bytes_from_file(target_path);
#ifdef RELEASE
    // debug_log("pokegold::build", "last cleanup (path=\"{}\")", workdir.string());
    std::filesystem::remove_all(workdir);
#endif
    return result;
}
