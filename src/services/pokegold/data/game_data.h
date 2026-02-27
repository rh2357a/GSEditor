#pragma once

#include "base/types/types.h"
#include "services/pokegold/data/color.h"
#include "services/pokegold/data/string.h"

#include <wx/gdicmn.h>

#include <any>
#include <array>
#include <vector>

namespace pokegold
{
    enum class TypeEffectiveness : u8
    {
        SuperEffective = 20,
        MoreEffective = 15,
        Effective = 10,
        NotVeryEffective = 5,
        NoEffect = 0,
    };

    enum class BattleWeather : u8
    {
        None = 0,
        Rain,
        Sun,
        Sandstorm,
    };

    enum class PokemonType
    {
        Pokemon,
        Unown,
        Egg,
        Dummy,
    };

    enum class GrowthRate : u8
    {
        MediumFast = 0,
        SlightlyFast,
        SlightlySlow,
        MediumSlow,
        Fast,
        Slow,
    };

    enum class GenderRate : u8
    {
        Gender_0 = 0x00,
        Gender_12_5 = 0x1f,
        Gender_25 = 0x3f,
        Gender_37_5 = 0x5f,
        Gender_50 = 0x7f,
        Gender_62_5 = 0x9f,
        Gender_75 = 0xbf,
        Gender_87_5 = 0xdf,
        Gender_100 = 0xfe,
        Unknown = 0xff,
    };

    enum class ImageDimensions : u8
    {
        Size_40x40 = 0x55,
        Size_48x48 = 0x66,
        Size_56x56 = 0x77,
    };

    inline ImageDimensions ToImageDimensions(wxSize size)
    {
        if (size.x == 40 && size.y == 40)
            return ImageDimensions::Size_40x40;
        else if (size.x == 48 && size.y == 48)
            return ImageDimensions::Size_48x48;
        else
            return ImageDimensions::Size_56x56;
    }

    enum class EggGroup : u8
    {
        Unknown = 0,
        Monster,
        Water1,
        Bug,
        Flying,
        Field,
        Fairy,
        Plant,
        HumanLike,
        Water3,
        Mineral,
        Indeterminate,
        Water2,
        Ditto,
        Dragon,
        None,
    };

    enum class EvolutionMethodType : u8
    {
        LevelUp = 1,
        UseItem = 2,
        Trade = 3,
        LevelUpWithHappiness = 4,
        LevelUpWithStats = 5,
    };

    enum class BadDataReason
    {
        EvolutionAndMoves,

        PokemonImage,
        UnownImage,
        TrainerGroupImage,
        EggImage,

        Pokedex,

        PokemonName,
        TrainerGroupName,
        TypeName,

        TypeMatchups,
        WeatherTypeModifiers,
        WeatherMoveModifiers,
    };
}

namespace pokegold
{
    class TypeMatchup
    {
    public:
        u8 AttackerTypeId;
        u8 DefenderTypeId;
        TypeEffectiveness TypeEffectiveness;
        bool IsForesight;
    };

    class WeatherTypeModifier
    {
    public:
        u8 TypeId;
        BattleWeather Weather;
        TypeEffectiveness TypeEffectiveness;
    };

    class WeatherMoveModifier
    {
    public:
        u8 MoveId;
        BattleWeather Weather;
        TypeEffectiveness TypeEffectiveness;
    };

    struct Item
    {
        u16 Price;
        u8 Effect;
        u8 Parameter;
        u8 Property;
        u8 Pocket;
        u8 FieldMenu;
        u8 BattleMenu;

        String Name;
        String Description;
    };

    struct Move
    {
        u8 Id;
        u8 Effect;
        u8 Power;
        u8 Type;
        u8 Accuracy;
        u8 PP;
        u8 EffectChance;

        std::vector<WeatherMoveModifier> WeatherModifiers;

        String Name;
        String Description;
    };

    struct TMHM
    {
        u8 MoveId;
    };

    class EvolutionMethod
    {
    public:
        EvolutionMethodType EvolutionMethodType;
        u8 PokemonId;
        u8 Level;
        u8 Stats;
        u8 ItemId;
        u8 Happiness;

    public:
        bool operator==(const EvolutionMethod &rhs) const;
        bool operator!=(const EvolutionMethod &rhs) const { return !(*this == rhs); }
    };

    class PokemonMove
    {
    public:
        u8 Level;
        u8 MoveId;

    public:
        bool operator==(const PokemonMove &rhs) const { return Level == rhs.Level && MoveId == rhs.MoveId; };
        bool operator!=(const PokemonMove &rhs) const { return !(*this == rhs); }
    };

    struct Pokemon
    {
        PokemonType Type;

        u8 Id;
        u8 CatchRate;
        u8 BaseExp;
        u8 Hp, Attack, Defence, Speed, SpAttack, SpDefence;
        u8 EggHatchLevel; // 걸음수: n * 256
        std::array<u8, 2> TypeIds;
        std::array<u8, 2> ItemIds;
        std::array<EggGroup, 2> EggGroups;
        std::array<bool, 64> TMHMs;
        ImageDimensions ImageDimensions;
        GenderRate GenderRate;
        GrowthRate GrowthRate;

        std::vector<EvolutionMethod> EvolutionMethods;
        std::vector<PokemonMove> Moves;

        String Name;
        String DexCategoryName;
        String Description;
        u8 Height;
        u16 Weight;

        std::vector<u8> FrontImage;
        std::vector<u8> BackImage;
        std::array<Color, 2> Colors;
        std::array<Color, 2> ShinyColors;
    };

    struct UnownImage
    {
        std::vector<u8> FrontImage;
        std::vector<u8> BackImage;

        // Pokemons()[200].Colors
        // Pokemons()[200].ShinyColors
    };

    struct TrainerGroup
    {
        String Name;

        std::vector<u8> Image;
        std::array<Color, 2> Colors;
    };

    class Type
    {
    public:
        String Name;

    public:
        std::vector<TypeMatchup> TypeMatchups;
        std::vector<WeatherTypeModifier> WeatherModifiers;
    };

    class BadData
    {
    private:
        BadDataReason m_reason;
        std::any m_data;

    public:
        BadData(BadDataReason reason, std::any data) : m_reason(reason), m_data(data) {}

    public:
        const auto &Reason() const { return m_reason; }
        const auto &Data() const { return m_data; }
    };
}
