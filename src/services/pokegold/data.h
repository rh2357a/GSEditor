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

        std::array<Item, 256> m_items;
        std::array<Move, 251> m_moves;
        std::array<MoveEffect, 256> m_moveEffects;
        std::array<Pokemon, 256> m_pokemons;
        std::array<UnownImage, 26> m_unownImages;
        std::array<TrainerGroup, 68> m_trainerGroups;
        std::array<Type, 28> m_types;
        std::array<TMHM, 57> m_tmhms;

        NpcColors m_npcColors;
        std::array<std::array<std::vector<u8>, 2>, 38> m_legacyPokemonSmallPictures; // 롬 빌드에 포함하지 않음 (읽기 전용)

        std::vector<BadData> m_badDataList;

        base::Event<int> m_pokemonNameUpdated;
        base::Event<int> m_itemNameUpdated;
        base::Event<int> m_moveNameUpdated;
        base::Event<int> m_typeNameUpdated;
        base::Event<> m_tmhmsUpdated;
        base::Event<int> m_trainerGroupUpdated;

    public:
        bool UnownImageEnabled = true;
        u8 UnownPokemonId = 0xc9;

    public:
        Data(std::filesystem::path romFilePath = base::GetNullPath());
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

        auto &PokemonNameUpdated() { return m_pokemonNameUpdated; }
        auto &ItemNameUpdated() { return m_itemNameUpdated; }
        auto &MoveNameUpdated() { return m_moveNameUpdated; }
        auto &TypeNameUpdated() { return m_typeNameUpdated; }
        auto &TMHMsUpdated() { return m_tmhmsUpdated; }
        auto &TrainerGroupUpdated() { return m_trainerGroupUpdated; }

        auto &Items() { return m_items; }
        auto &Moves() { return m_moves; }
        auto &MoveEffects() { return m_moveEffects; }
        auto &Pokemons() { return m_pokemons; }
        auto &UnownImages() { return m_unownImages; }
        auto &TrainerGroups() { return m_trainerGroups; }
        auto &Types() { return m_types; }
        auto &TMHMs() { return m_tmhms; }

        auto &NpcColors() { return m_npcColors; }
        auto &LegacyPokemonSmallPictures() { return m_legacyPokemonSmallPictures; }

        auto &BadDataList() { return m_badDataList; }
    };
}
