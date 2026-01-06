#ifndef _POKEGOLD_DATA_H_
#define _POKEGOLD_DATA_H_

#include "pokegold/string.h"
#include "pokegold/color.h"

#include <any>
#include <array>
#include <vector>

namespace pokegold::data {

enum class pokemon_type
{
    POKEMON,
    UNOWN,
    EGG,
    DUMMY,
};

enum class growth_rate : u8
{
    MEDIUM_FAST = 0,
    SLIGHTLY_FAST,
    SLIGHTLY_SLOW,
    MEDIUM_SLOW,
    FAST,
    SLOW,
};

enum class gender_rate : u8
{
    GENDER_0 = 0x00,
    GENDER_12_5 = 0x1f,
    GENDER_25 = 0x3f,
    GENDER_37_5 = 0x5f,
    GENDER_50 = 0x7f,
    GENDER_62_5 = 0x9f,
    GENDER_75 = 0xbf,
    GENDER_87_5 = 0xdf,
    GENDER_100 = 0xfe,
    UNKNOWN = 0xff,
};

enum class image_dimens : u8
{
    SIZE_40 = 0x55,
    SIZE_48 = 0x66,
    SIZE_56 = 0x77,
};

enum class egg_group : u8
{
    UNKNWON = 0, // 사용 금지
    MONSTER,
    WATER_1,
    BUG,
    FLYING,
    FIELD,
    FAIRY,
    PLANT,
    HUMAN_LIKE,
    WATER_3,
    MINERAL,
    INDETERMINATE,
    WATER_2,
    DITTO,
    DRAGON,
    NONE,
};

enum class type_effectiveness : u8
{
    SUPER_EFFECTIVE = 20,
    MORE_EFFECTIVE = 15,
    EFFECTIVE = 10,
    NOT_VERY_EFFECTIVE = 5,
    NO_EFFECT = 0,
};

enum class battle_weather : u8
{
    NONE = 0, // 사용 금지
    RAIN,
    SUN,
    SANDSTORM,
};

enum class bad_data_reason
{
    EVOLUTION_MOVES,

    POKEMON_FRONT_IMAGE,
    POKEMON_BACK_IMAGE,

    UNOWN_FRONT_IMAGE,
    UNOWN_BACK_IMAGE,

    TRAINER_IMAGE,

    EGG_IMAGE,
};

} // namespace pokegold::data

namespace pokegold::data {

class bad_data
{
public:
    bad_data_reason reason;
    std::any data;
};

class item
{
public:
    u16 price;
    u8 effect;
    u8 parameter;
    u8 property;
    u8 pocket;
    u8 field_menu;
    u8 battle_menu;

public:
    string name;
    string description;
};

class weather_modifier_move
{
public:
    u8 move_id;
    battle_weather weather;
    type_effectiveness effectiveness;
};

class move
{
public:
    u8 id;
    u8 effect;
    u8 power;
    u8 type;
    u8 accuracy;
    u8 pp;
    u8 effect_chance;

public:
    std::vector<weather_modifier_move> weather_modifiers;

public:
    string name;
    string description;
};

class evolution_method
{
public:
    u8 evolution_type;
    u8 pokemon_id;
    u8 level;
    u8 stats;
    u8 item_id;
    u8 happiness;
};

class learn_move
{
public:
    u8 level;
    u8 move_id;
};

class pokemon
{
public:
    pokemon_type type;

public:
    u8 id;
    u8 catch_rate;
    u8 base_exp;
    u8 hp, atk, def, spd, sp_atk, sp_def;
    u8 type_1_id, type_2_id;
    u8 item_1_id, item_2_id;
    u8 egg_hatch_lv; // 걸음수: n * 256
    egg_group egg_group_1, egg_group_2;
    image_dimens image_dimens;
    gender_rate gender_rate;
    growth_rate growth_rate;
    std::array<bool, 64> tmhms;

public:
    std::vector<evolution_method> evolution_methods;
    std::vector<learn_move> learn_moves;

public:
    string name;
    string species_name;
    string description;
    u8 height;
    u16 weight;

public:
    std::vector<u8> front_image;
    std::vector<u8> back_image;
    std::array<color, 2> colors;
    std::array<color, 2> shiny_colors;
};

class unown_image
{
public:
    std::vector<u8> front;
    std::vector<u8> back;

    // pokemons[200].colors
    // pokemons[200].shiny_colors
};

class trainer_group
{
public:
    bool has_image;
    string name;
    std::vector<u8> image;
    std::array<color, 2> colors;
};

class type_matchup
{
public:
    u8 attacker_type_id;
    u8 defender_type_id;
    type_effectiveness effectiveness;
    bool foresight;
};

class weather_modifier
{
public:
    u8 type_id;
    battle_weather weather;
    type_effectiveness effectiveness;
};

class type
{
public:
    string name;

public:
    std::vector<type_matchup> matchups;
    std::vector<weather_modifier> weather_modifiers;
};

} // namespace pokegold::data

namespace pokegold::data {

inline std::array<item, 256> items;
inline std::array<move, 251> moves;
inline std::array<pokemon, 256> pokemons;
inline std::array<unown_image, 26> unown_images;
inline std::array<trainer_group, 67> trainer_groups;
inline std::array<type, 28> types;
inline std::array<u8, 57> tmhms;

} // namespace pokegold::data

#endif
