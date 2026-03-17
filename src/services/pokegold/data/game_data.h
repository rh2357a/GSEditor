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
        Egg,
        Dummy,

        // NOTE: index 값과 설정값으로 처리
        // Unown,
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
        Size_16x16 = 0x22,
        Size_32x16 = 0x42,
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
        else if (size.x == 16 && size.y == 16)
            return ImageDimensions::Size_16x16;
        else if (size.x == 32 && size.y == 16)
            return ImageDimensions::Size_32x16;
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

    enum class NpcColorIndex : u8
    {
        Red = 0,
        Blue,
        Green,
        Brown,
        Pink,
        Gray,
        Tree,
        Rock,
    };

    enum class BadDataReason
    {
        EvolutionAndMoves,

        PokemonImage,
        UnownImage,
        TrainerGroupImage,
        TrainerGroupPlayerBackImage,
        EggImage,

        Pokedex,

        ItemName,
        ItemDescription,

        MoveName,
        MoveDescription,

        PokemonName,
        TrainerGroupName,
        TypeName,

        TypeMatchups,
        TypeWeatherModifiers,
        MoveEffectWeatherModifiers,
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

    public:
        bool operator!=(const TypeMatchup &rhs) const { return !(*this == rhs); }
        bool operator==(const TypeMatchup &rhs) const
        {
            return AttackerTypeId == rhs.AttackerTypeId
                   && DefenderTypeId == rhs.DefenderTypeId
                   && TypeEffectiveness == rhs.TypeEffectiveness
                   && IsForesight == rhs.IsForesight;
        }
    };

    class WeatherModifier
    {
    public:
        BattleWeather Weather;
        TypeEffectiveness TypeEffectiveness;

    public:
        bool operator!=(const WeatherModifier &rhs) const
        {
            return !(*this == rhs);
        }

        bool operator==(const WeatherModifier &rhs) const
        {
            return Weather == rhs.Weather && TypeEffectiveness == rhs.TypeEffectiveness;
        }
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

        String Name;
        String Description;
    };

    struct MoveEffect
    {
        std::vector<WeatherModifier> WeatherModifiers;
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
        bool operator==(const PokemonMove &rhs) const { return Level == rhs.Level && MoveId == rhs.MoveId; }
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
        std::vector<u8> EggMoveIds;

        String Name;
        String DexCategoryName;
        String Description;
        u8 Height;
        u16 Weight;

        std::vector<u8> FrontImage;
        std::vector<u8> BackImage;
        std::array<Color, 2> Colors;
        std::array<Color, 2> ShinyColors;

        u8 SmallImagePaletteId;
        std::vector<u8> SmallImages;
        std::vector<u8> FootprintImage;
    };

    struct UnownImage
    {
        ImageDimensions ImageDimensions;

        std::vector<u8> FrontImage;
        std::vector<u8> BackImage;
    };

    struct TrainerGroup
    {
        String Name;

        std::vector<u8> Image;
        std::array<Color, 2> Colors;

        // 플레이어, 튜토리얼 전용
        std::vector<u8> BackImage, DudeBackImage;
        std::array<Color, 2> BackColors; // obsoluted
    };

    struct Type
    {
        String Name;

        std::vector<TypeMatchup> TypeMatchups;
        std::vector<WeatherModifier> WeatherModifiers;
    };

    class NpcColor
    {
    private:
        std::array<std::array<Color, 4>, 8> m_colors;

    public:
        std::array<Color, 4> &operator[](size_t idx)
        {
            return m_colors[idx];
        }

        std::array<Color, 4> &operator[](const NpcColorIndex &idx)
        {
            u8 index = u8(idx);
            return m_colors[index];
        }

        auto begin() { return m_colors.begin(); }
        auto end() { return m_colors.end(); }
    };

    class NpcColors
    {
    private:
        std::array<NpcColor, 4> m_colors;

    public:
        NpcColor &Morning = m_colors[0];
        NpcColor &Day = m_colors[1];
        NpcColor &Night = m_colors[2];
        NpcColor &Dark = m_colors[3];

    public:
        NpcColors &operator=(const NpcColors &npcColor)
        {
            m_colors = npcColor.m_colors;
            return *this;
        }

    public:
        NpcColor &operator[](size_t idx) { return m_colors[idx]; }
        auto begin() { return m_colors.begin(); }
        auto end() { return m_colors.end(); }
    };

    // TODO: 작업 중...
    // struct Map
    // {};

    struct Maps
    {
        // TODO: 작업 중...
        // std::array<Map, 26> MapGroups;

        NpcColors NpcColors;
        std::array<std::array<std::vector<u8>, 2>, 38> LegacyPokemonSmallPictures; // 롬 빌드에 포함하지 않음 (읽기 전용)
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
