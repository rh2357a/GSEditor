#pragma once

#include "base/files/paths.h"
#include "base/functional/event.h"
#include "base/types/types.h"
#include "services/pokegold/data/game_data.h"

#include <filesystem>
#include <span>
#include <array>
#include <vector>

namespace pokegold
{
    class Data
    {
    private:
        std::vector<u8> m_romBytes;

        std::array<Item, 256> m_items;
        std::array<Move, 251> m_moves;
        std::array<Pokemon, 256> m_pokemons;
        std::array<UnownImage, 26> m_unownImages;
        std::array<TrainerGroup, 67> m_trainerGroups;
        std::array<Type, 28> m_types;
        std::array<TMHM, 57> m_tmhms;

        std::vector<BadData> m_badDataList;

        base::Event<int> m_pokemonNameUpdated;
        base::Event<int> m_itemNameUpdated;
        base::Event<int> m_moveNameUpdated;
        base::Event<int> m_typeNameUpdated;

    public:
        Data(std::filesystem::path romFilePath = base::GetNullPath());

    public:
        bool MatchBytes(size_t offset, const std::vector<u8> &findBytes);

        u8 GetByte(size_t offset);
        std::span<const u8> GetBytes(size_t offset, size_t length);
        std::span<const u8> GetBytesUntil(size_t offset, std::function<bool(size_t, u8)> predicate, bool includeEnd);

        void SetByte(size_t offset, u8 byte);
        void SetBytes(size_t offset, const std::vector<u8> &bytes);
        void FillBytes(u8 byte, size_t offset, size_t length);

        auto &PokemonNameUpdated() { return m_pokemonNameUpdated; }
        auto &ItemNameUpdated() { return m_itemNameUpdated; }
        auto &MoveNameUpdated() { return m_moveNameUpdated; }
        auto &TypeNameUpdated() { return m_typeNameUpdated; }

        auto &Items() { return m_items; }
        auto &Moves() { return m_moves; }
        auto &Pokemons() { return m_pokemons; }
        auto &UnownImages() { return m_unownImages; }
        auto &TrainerGroups() { return m_trainerGroups; }
        auto &Types() { return m_types; }
        auto &TMHMs() { return m_tmhms; }

        auto &BadDataList() { return m_badDataList; }

        void AssignFrom(const Data &newData);
    };
}
