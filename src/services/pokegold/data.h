#pragma once

#include "base/files/paths.h"
#include "base/functional/event.h"
#include "base/types/types.h"
#include "services/pokegold/data/game_data.h"

#include <array>
#include <filesystem>
#include <span>
#include <vector>

namespace pokegold
{
    class Data
    {
    private:
        std::vector<u8> m_romBytes;

    public:
        std::array<Item, 256> Items;
        std::array<Move, 251> Moves;
        std::array<MoveEffect, 256> MoveEffects;
        std::array<Pokemon, 256> Pokemons;
        std::array<UnownImage, 26> UnownImages;
        std::array<TrainerGroup, 68> TrainerGroups;
        std::array<Type, 28> Types;
        std::array<TMHM, 57> TMHMs;

        Maps Maps;

        bool TrainerCardImageEnabled = true;
        u8 UnownPokemonId = 0xc9;

        std::vector<BadData> BadDataList;

        base::Event<int> PokemonNameUpdated;
        base::Event<int> ItemNameUpdated;
        base::Event<int> MoveNameUpdated;
        base::Event<int> TypeNameUpdated;
        base::Event<> TMHMsUpdated;
        base::Event<int> TrainerGroupUpdated;

    public:
        Data(std::filesystem::path romFilePath = base::NullPath);
        Data &operator=(const Data &newData);

    public:
        bool MatchBytes(size_t offset, const std::vector<u8> &findBytes);

        std::span<const u8> GetRomBytes() { return m_romBytes; }

        u8 GetByte(size_t offset);
        std::span<const u8> GetBytes(size_t offset, size_t length);
        std::span<const u8> GetBytesUntil(size_t offset, std::function<bool(size_t, u8)> predicate, bool includeEnd);

        void SetByte(size_t offset, u8 byte);
        void SetBytes(size_t offset, const std::vector<u8> &bytes);
        void FillBytes(u8 byte, size_t offset, size_t length);
    };
}
