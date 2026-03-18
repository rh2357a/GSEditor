#include "pokegold.h"

#include "base/files/paths.h"
#include "base/log.h"
#include "base/resources.h"
#include "base/resources_embed.h"
#include "base/strings/crypto.h"
#include "base/types/types.h"
#include "services/pokegold/data/color.h"
#include "services/pokegold/data/game_data.h"
#include "services/pokegold/utils.h"

#include <lzcomp/lzcomp.h>
#include <wx/wx.h>

#include <array>
#include <cstddef>
#include <format>
#include <functional>
#include <vector>

namespace
{
    const std::array<u8, 8> k_bits = {
        0b00000001,
        0b00000010,
        0b00000100,
        0b00001000,
        0b00010000,
        0b00100000,
        0b01000000,
        0b10000000,
    };

    constexpr size_t k_imageBufferSize_5x5 = 400;
    constexpr size_t k_imageBufferSize_6x6 = 576;
    constexpr size_t k_imageBufferSize_7x7 = 784;

    size_t GetBuferSize(pokegold::ImageDimensions dimens)
    {
        if (dimens == pokegold::ImageDimensions::Size_40x40)
            return k_imageBufferSize_5x5;
        if (dimens == pokegold::ImageDimensions::Size_48x48)
            return k_imageBufferSize_6x6;
        return k_imageBufferSize_7x7;
    }
}

bool services::Pokegold::Open(const std::filesystem::path &romFilePath)
{
    base::Log(TAG, "start open. (path=\"{}\")", romFilePath.string());
    m_openProgressState.Reset();

    std::vector<std::function<bool(pokegold::Data &)>> funcs = {
        [this](pokegold::Data &data) { return Open_ReadItems(data); },
        [this](pokegold::Data &data) { return Open_ReadMoves(data); },
        [this](pokegold::Data &data) { return Open_ReadPokemons(data); },
        [this](pokegold::Data &data) { return Open_ReadTrainerGroups(data); },
        [this](pokegold::Data &data) { return Open_ReadTypes(data); },
        [this](pokegold::Data &data) { return Open_ReadMaps(data); },
    };

    pokegold::Data data(romFilePath);

    for (const auto &func : funcs)
    {
        if (!func(data))
            return false;
    }

    Data = data;

    base::Log(TAG, "finish open.");
    m_romFilePathState.Update(romFilePath);
    m_isOpenedState.Update(true);

    std::filesystem::path workSpacePath = base::GetAppDataPath() / "workspaces" / base::Hash(romFilePath.string());
    std::filesystem::create_directories(workSpacePath);
    m_workspacePathState.Update(workSpacePath);

    // 손상된 데이터 유무에 따라 변동 사항을 통지
    m_isDataChangedState.Update(!data.BadDataList.empty());

    return true;
}

bool services::Pokegold::Open_ReadItems(pokegold::Data &data)
{
    base::Log(TAG, "read items (primary)");
    for (size_t i = 0; i < 256; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("아이템 (기본 정보: {}/256)", i + 1));
        m_openProgressState.Increase();

        auto bytes = data.GetBytes(0x697b + (i * 7), 7);
        auto &item = data.Items[i];
        item.Price = bytes[0] | (u16(bytes[1]) << 8);
        item.Effect = bytes[2];
        item.Parameter = bytes[3];
        item.Property = bytes[4];
        item.Pocket = bytes[5];
        item.FieldMenu = (bytes[6] & 0xf0) >> 4;
        item.BattleMenu = bytes[6] & 0x0f;
    }

    base::Log(TAG, "read items (name)");
    size_t itemNameOffset = pokegold::Calc(data.GetBytes(0x35cc, 3));
    bool hasBadItemName = false;
    for (size_t i = 0; i < 256; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("아이템 (이름: {}/256)", i + 1));
        m_openProgressState.Increase();

        const auto bytes = data.GetBytesUntil(itemNameOffset, [&](size_t idx, u8 b) { return b == 0x50; }, true);
        itemNameOffset += bytes.size();

        auto &item = data.Items[i];
        pokegold::String str = bytes;
        if (hasBadItemName || str.HasBadData() || str.GetData().size() > 24)
        {
            item.Name = "?";

            if (!hasBadItemName)
            {
                hasBadItemName = true;
                data.BadDataList.emplace_back(pokegold::BadDataReason::ItemName, i);
                base::Log(TAG, "bad data (item name, idx={})", i);
            }
        }
        else
        {
            item.Name = str;
        }
    }

    base::Log(TAG, "read items (description)");
    size_t itemDescriptionBank = pokegold::CalcBank(0x1b8000);
    for (size_t i = 0; i < 256; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("아이템 (설명: {}/256)", i + 1));
        m_openProgressState.Increase();

        size_t offset = pokegold::Calc(itemDescriptionBank, data.GetBytes(0x1b8000 + (i * 2), 2));
        auto &item = data.Items[i];
        pokegold::String str = data.GetBytesUntil(offset, [&](size_t idx, u8 b) { return b == 0x50; }, true);
        if (str.HasBadData() || str.GetData().size() > 110)
        {
            item.Description = "?";
            data.BadDataList.emplace_back(pokegold::BadDataReason::ItemDescription, i);
            base::Log(TAG, "bad data (item description, idx={})", i);
        }
        else
        {
            item.Description = str;
        }
    }

    return !m_openProgressState.HandlePausedOrCanceled();
}

bool services::Pokegold::Open_ReadMoves(pokegold::Data &data)
{
    base::Log(TAG, "read moves (primary)");
    for (size_t i = 0; i < 251; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("기술 (기본 정보: {}/251)", i + 1));
        m_openProgressState.Increase();

        auto &move = data.Moves[i];
        auto bytes = data.GetBytes(0x4172e + (i * 7), 7);
        move.Id = bytes[0];
        move.Effect = bytes[1];
        move.Power = bytes[2];
        move.Type = bytes[3];
        move.Accuracy = bytes[4];
        move.PP = bytes[5];
        move.EffectChance = bytes[6];
    }

    base::Log(TAG, "read moves (name)");
    size_t nameOffset = pokegold::Calc(data.GetBytes(0x35c6, 3));
    bool hasBadMoveName = false;
    for (size_t i = 0; i < 251; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("기술 (이름: {}/251)", i + 1));
        m_openProgressState.Increase();

        const auto bytes = data.GetBytesUntil(nameOffset, [&](size_t idx, u8 b) { return b == 0x50; }, true);
        nameOffset += bytes.size();

        pokegold::String str = bytes;
        if (hasBadMoveName || str.HasBadData() || str.GetData().size() > 24)
        {
            data.Moves[i].Name = "?";

            if (!hasBadMoveName)
            {
                hasBadMoveName = true;
                data.BadDataList.emplace_back(pokegold::BadDataReason::MoveName, i);
                base::Log(TAG, "bad data (move name, idx={})", i);
            }
        }
        else
        {
            data.Moves[i].Name = str;
        }

        data.Moves[i].Name = bytes;
    }

    base::Log(TAG, "read moves (description)");
    size_t descriptionBank = pokegold::CalcBank(0x1b4000);
    for (size_t i = 0; i < 251; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("기술 (설명: {}/251)", i + 1));
        m_openProgressState.Increase();

        size_t offset = pokegold::Calc(descriptionBank, data.GetBytes(0x1b4000 + (i * 2), 2));
        pokegold::String str = data.GetBytesUntil(offset, [&](size_t idx, u8 b) { return b == 0x50; }, true);
        if (str.HasBadData() || str.GetData().size() > 110)
        {
            data.Moves[i].Description = "?";
            data.BadDataList.emplace_back(pokegold::BadDataReason::MoveDescription, i);
            base::Log(TAG, "bad data (move description, idx={})", i);
        }
        else
        {
            data.Moves[i].Description = str;
        }
    }

    base::Log(TAG, "read moves (TM & HM)");
    for (size_t i = 0; i < 57; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("기술 (기술 머신: {}/57)", i + 1));
        m_openProgressState.Increase();

        const u8 moveId = data.GetByte(0x119f5 + i);
        data.TMHMs[i].MoveId = moveId;
    }

    return !m_openProgressState.HandlePausedOrCanceled();
}

bool services::Pokegold::Open_ReadPokemons(pokegold::Data &data)
{
    std::vector<u8> imageBuffer(0x400, 0);

    const bool isHackedUnownIds = data.MatchBytes(0x1fc7d6, {0xfd, 0xff});
    if (isHackedUnownIds)
    {
        data.TrainerCardImageEnabled = data.GetByte(0x1fc7d8) == 1;
        data.UnownPokemonId = data.GetByte(0x1fc7d9);
    }
    else
    {
        data.TrainerCardImageEnabled = false;
        data.UnownPokemonId = 0xc9;
    }

    base::Log(TAG, "read pokemon (primary)");
    const size_t eggMovesPtrOffset = pokegold::Calc(data.GetByte(0x17414), data.GetBytes(0x1740f, 2));
    const size_t eggMovesPtrBank = pokegold::CalcBank(eggMovesPtrOffset);
    for (size_t i = 0; i < 256; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("포켓몬 (기본 정보: {}/256)", i + 1));
        m_openProgressState.Increase();

        auto &pokemon = data.Pokemons[i];

        // type setting
        {
            if (i == 252)
                pokemon.Type = pokegold::PokemonType::Egg;
            else if (i < 251)
                pokemon.Type = pokegold::PokemonType::Pokemon;
            else
                pokemon.Type = pokegold::PokemonType::Dummy;
        }

        // 0~250
        if (pokemon.Type == pokegold::PokemonType::Pokemon)
        {
            const auto bytes = data.GetBytes(0x51bdf + (i * 32), 32);

            // stats
            {
                pokemon.Id = bytes[0];
                pokemon.Hp = bytes[1];
                pokemon.Attack = bytes[2];
                pokemon.Defence = bytes[3];
                pokemon.Speed = bytes[4];
                pokemon.SpAttack = bytes[5];
                pokemon.SpDefence = bytes[6];
                pokemon.TypeIds[0] = bytes[7];
                pokemon.TypeIds[1] = bytes[8];
                pokemon.CatchRate = bytes[9];
                pokemon.BaseExp = bytes[10];
                pokemon.ItemIds[0] = bytes[11];
                pokemon.ItemIds[1] = bytes[12];
                pokemon.GenderRate = pokegold::GenderRate(bytes[13]);
                pokemon.EggHatchLevel = bytes[15];
                pokemon.ImageDimensions = pokegold::ImageDimensions(bytes[17]);
                pokemon.GrowthRate = pokegold::GrowthRate(bytes[22]);
                pokemon.EggGroups[0] = pokegold::EggGroup((bytes[23] & 0xf0) >> 4);
                pokemon.EggGroups[1] = pokegold::EggGroup(bytes[23] & 0x0f);
            }

            // TMHMs
            for (u8 j = 0; j < 8; j++)
            {
                for (u8 a = 0; a < 8; a++)
                {
                    u8 idx = (j * 8) + a;
                    pokemon.TMHMs[idx] = (bytes[24 + j] & k_bits[a]) != 0;
                }
            }

            // egg moves
            {
                size_t offset = pokegold::Calc(eggMovesPtrBank, data.GetBytes(eggMovesPtrOffset + (i * 2), 2));
                for (;;)
                {
                    u8 byte = data.GetByte(offset);
                    if (byte == 0xff)
                        break;

                    pokemon.EggMoveIds.push_back(byte);
                    offset++;
                }
            }
        }
    }

    base::Log(TAG, "read pokemon (evolves & moves)");
    size_t evolveBank = pokegold::CalcBank(0x423ed);
    for (size_t i = 0; i < 256; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("포켓몬 (진화 & 자력기: {}/256)", i + 1));
        m_openProgressState.Increase();

        auto &pokemon = data.Pokemons[i];
        if (pokemon.Type == pokegold::PokemonType::Pokemon)
        {
            const auto offset = pokegold::Calc(evolveBank, data.GetBytes(0x423ed + (i * 2), 2));
            const auto bytes = data.GetBytesUntil(offset, [&](size_t idx, u8 b) { return b == 0; }, true);

            bool hasBadData = false;
            for (size_t j = 0; j < bytes.size();)
            {
                if (hasBadData)
                    break;

                pokegold::EvolutionMethod newEvolve;

                u8 b = bytes[j++];

                if (b == 0)
                    break;

                if (!(b >= 1 && b <= 5))
                {
                    hasBadData = true;
                    pokemon.EvolutionMethods.clear();
                    pokemon.Moves.clear();
                    data.BadDataList.emplace_back(pokegold::BadDataReason::EvolutionAndMoves, i);
                    base::Log(TAG, "bad data (pokemon evolve & moves, idx={})", i);
                    break;
                }

                newEvolve.EvolutionMethodType = pokegold::EvolutionMethodType(b);
                switch (newEvolve.EvolutionMethodType)
                {
                case pokegold::EvolutionMethodType::LevelUp:
                    newEvolve.Level = bytes[j++];
                    newEvolve.PokemonId = bytes[j++];
                    pokemon.EvolutionMethods.push_back(newEvolve);
                    break;

                case pokegold::EvolutionMethodType::UseItem:
                case pokegold::EvolutionMethodType::Trade:
                    newEvolve.ItemId = bytes[j++];
                    newEvolve.PokemonId = bytes[j++];
                    pokemon.EvolutionMethods.push_back(newEvolve);
                    break;

                case pokegold::EvolutionMethodType::LevelUpWithHappiness:
                    newEvolve.Happiness = bytes[j++];
                    newEvolve.PokemonId = bytes[j++];
                    pokemon.EvolutionMethods.push_back(newEvolve);
                    break;

                case pokegold::EvolutionMethodType::LevelUpWithStats:
                    newEvolve.Level = bytes[j++];
                    newEvolve.Stats = bytes[j++];
                    newEvolve.PokemonId = bytes[j++];
                    pokemon.EvolutionMethods.push_back(newEvolve);
                    break;
                }
            }

            if (!hasBadData)
            {
                const auto movesBytes = data.GetBytesUntil(offset + bytes.size(), [&](size_t idx, u8 b) { return b == 0; }, true);
                for (size_t j = 0; j < movesBytes.size();)
                {
                    const u8 b = movesBytes[j++];
                    if (b == 0 || j >= movesBytes.size())
                        break;

                    pokegold::PokemonMove newMove;
                    newMove.Level = b;
                    newMove.MoveId = movesBytes[j++];
                    pokemon.Moves.push_back(newMove);
                }
            }
        }
    }

    base::Log(TAG, "read pokemon (pokedex & name)");
    for (size_t i = 0; i < 256; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("포켓몬 (도감 & 이름: {}/256)", i + 1));
        m_openProgressState.Increase();

        auto &pokemon = data.Pokemons[i];
        if (pokemon.Type == pokegold::PokemonType::Pokemon)
        {
            size_t offset;
            if (i < 128)
                offset = pokegold::Calc(0x68, data.GetBytes(0x442ff + (i * 2), 2));
            else
                offset = pokegold::Calc(0x69, data.GetBytes(0x443ff + ((i - 128) * 2), 2));

            pokemon.DexCategoryName = data.GetBytesUntil(offset, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            offset += pokemon.DexCategoryName.GetData().size();

            if (pokemon.DexCategoryName.HasBadData() || pokemon.DexCategoryName.GetData().size() > 16)
            {
                pokemon.DexCategoryName = "[50]";
                pokemon.Height = 0;
                pokemon.Weight = 0;
                pokemon.Description = "[50]";
                data.BadDataList.emplace_back(pokegold::BadDataReason::Pokedex, i);
                base::Log(TAG, "bad data (pokedex1, idx={})", i);
            }
            else
            {
                pokemon.Height = data.GetByte(offset);
                offset += 1;

                pokemon.Weight = data.GetByte(offset) | (data.GetByte(offset + 1) << 8);
                offset += 2;

                pokemon.Description = data.GetBytesUntil(offset, [&](size_t idx, u8 b) { return b == 0x50; }, true);

                if (pokemon.Description.HasBadData() || pokemon.Description.GetData().size() > 110)
                {
                    pokemon.DexCategoryName = "[50]";
                    pokemon.Height = 0;
                    pokemon.Weight = 0;
                    pokemon.Description = "[50]";
                    data.BadDataList.emplace_back(pokegold::BadDataReason::Pokedex, i);
                    base::Log(TAG, "bad data (pokedex2, idx={})", i);
                }
            }
        }

        size_t offset = pokegold::Calc(data.GetBytes(0x35c3, 3)) + (i * 10);
        pokemon.Name = data.GetBytesUntil(offset, [&](size_t idx, u8 b) { return idx == 9 || b == 0x50; }, true);
        if (pokemon.Name.HasBadData() || pokemon.Name.GetData().size() > 11)
        {
            pokemon.Name = "[50]";
            data.BadDataList.emplace_back(pokegold::BadDataReason::PokemonName, i);
            base::Log(TAG, "bad data (pokemon name, idx={})", i);
        }
    }

    for (size_t i = 0, max = 38; i < max; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("포켓몬 (구버전 오버월드 이미지: {}/{})", i + 1, max));
        m_openProgressState.Increase();

        auto newData = data.GetBytes(0x8eab6 + (i * 0x80), 0x40);
        data.Maps.LegacyPokemonSmallPictures[i][0] = std::vector<u8>(newData.begin(), newData.end());

        newData = data.GetBytes(0x8eab6 + (i * 0x80) + 0x40, 0x40);
        data.Maps.LegacyPokemonSmallPictures[i][1] = std::vector<u8>(newData.begin(), newData.end());
    }

    const bool isHackedExtendedSmallPics = data.MatchBytes(0x14348, {0xc3, 0xc2, 0x7a}) || data.MatchBytes(0x14334, {0xc3});
    if (!isHackedExtendedSmallPics)
    {
        // 기본 스프라이트 주입 시키기
        for (size_t i = 0; i < 256; i++)
        {
            auto &pokemon = data.Pokemons[i];

            if (pokemon.Type == pokegold::PokemonType::Pokemon)
            {
                u8 picId = data.GetByte(0x8e96d + i) - 1;
                data.SetBytes(0x1f0000 + (i * 0x80), data.Maps.LegacyPokemonSmallPictures[picId][0]);
                data.SetBytes(0x1f0000 + (i * 0x80) + 0x40, data.Maps.LegacyPokemonSmallPictures[picId][1]);
            }
            else if (pokemon.Type == pokegold::PokemonType::Egg)
            {
                u8 picId = data.GetByte(0x8e96b) - 1;
                data.SetBytes(0x1f0000 + (i * 0x80), data.Maps.LegacyPokemonSmallPictures[picId][0]);
                data.SetBytes(0x1f0000 + (i * 0x80) + 0x40, data.Maps.LegacyPokemonSmallPictures[picId][1]);
            }
        }

        const auto &picsPalData = embed::GetPokegoldDefaultSmallPicturesPaletteData();
        data.SetBytes(0x017ace, picsPalData);

        const auto &picsAttr = embed::GetPokegoldDefaultSmallPicturesAttributes();
        data.SetBytes(0x08e96d, picsAttr);
    }

    base::Log(TAG, "read pokemon (image & color)");
    for (size_t i = 0; i < 256; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("포켓몬 (이미지: {}/256)", i + 1));
        m_openProgressState.Increase();

        auto &pokemon = data.Pokemons[i];

        // color
        {
            const auto offset = 0xad15 + (i * 8);
            pokemon.Colors[0] = pokegold::Color(data.GetBytes(offset, 2));
            pokemon.Colors[1] = pokegold::Color(data.GetBytes(offset + 2, 2));
            pokemon.ShinyColors[0] = pokegold::Color(data.GetBytes(offset + 4, 2));
            pokemon.ShinyColors[1] = pokegold::Color(data.GetBytes(offset + 6, 2));
        }

        // small pics
        {
            const auto offset = 0x1f0000 + (i * 0x80);

            auto bytes = data.GetBytes(offset + 0, 0x80);
            pokemon.SmallImages = std::vector<u8>(bytes.begin(), bytes.end());

            pokemon.SmallImagePaletteId = data.GetByte(0x17ace + i);
        }

        // footprint
        {
            const auto offset = 0xf92bd + ((i / 8) * 0x100) + ((i % 8) * 0x10);

            auto bytes = data.GetBytes(offset + 0, 0x10);
            pokemon.FootprintImage = std::vector<u8>(bytes.begin(), bytes.end());
            bytes = data.GetBytes(offset + 0x80, 0x10);
            pokemon.FootprintImage.insert(pokemon.FootprintImage.end(), bytes.begin(), bytes.end());
        }

        if (pokemon.Type == pokegold::PokemonType::Egg)
        {
            size_t offset;
            if (isHackedUnownIds)
                offset = pokegold::Calc(data.GetByte(0x1fc7da), data.GetBytes(0x1fc7db, 2));
            else
                offset = pokegold::Calc(data.GetByte(0x5189a), data.GetBytes(0x51897, 2));

            auto bytes = data.GetBytes(offset, 0x400);
            auto size = lzcomp::Uncompress(imageBuffer, bytes);

            if (size == 0 || size < k_imageBufferSize_5x5)
            {
                data.BadDataList.emplace_back(pokegold::BadDataReason::EggImage, nullptr);
                base::Log(TAG, "bad data (pokemon image (egg), idx={})", i);
            }

            pokemon.FrontImage = (size == 0)
                                     ? std::vector<u8>(k_imageBufferSize_5x5, 0)
                                     : std::vector<u8>(imageBuffer.begin(), imageBuffer.begin() + size);
        }
        else if (pokemon.Type == pokegold::PokemonType::Pokemon)
        {
            if (data.MatchBytes(0x48000 + (i * 6), {0xff, 0xff, 0xff}))
            {
                // 새로운 이미지 속성 복사
                for (auto &e : data.UnownImages)
                    e.ImageDimensions = pokemon.ImageDimensions;

                // 안농 이미지 해킹하기 전까지는 기본 이미지가 NULL인 상태이므로 예외처리
                pokemon.ImageDimensions = pokegold::ImageDimensions::Size_40x40;
                pokemon.FrontImage = std::vector<u8>(k_imageBufferSize_5x5, 0);
                pokemon.BackImage = std::vector<u8>(k_imageBufferSize_6x6, 0);
            }
            else
            {
                size_t offset = pokegold::CalcFromEncodedBank(data.GetBytes(0x48000 + (i * 6), 3));
                auto bytes = data.GetBytes(offset, 0x400);
                auto size = lzcomp::Uncompress(imageBuffer, bytes);

                if (size == 0 || size < GetBuferSize(pokemon.ImageDimensions))
                {
                    pokemon.ImageDimensions = pokegold::ImageDimensions::Size_40x40;
                    pokemon.FrontImage = std::vector<u8>(k_imageBufferSize_5x5, 0);
                    pokemon.BackImage = std::vector<u8>(k_imageBufferSize_6x6, 0);
                    data.BadDataList.emplace_back(pokegold::BadDataReason::PokemonImage, i);
                    base::Log(TAG, "bad data (pokemon image front, idx={})", i);
                }
                else
                {
                    pokemon.FrontImage = std::vector<u8>(imageBuffer.begin(), imageBuffer.begin() + size);

                    offset = pokegold::CalcFromEncodedBank(data.GetBytes(0x48000 + (i * 6) + 3, 3));
                    bytes = data.GetBytes(offset, 0x400);
                    size = lzcomp::Uncompress(imageBuffer, bytes);

                    if (size == 0 || size < k_imageBufferSize_6x6)
                    {
                        pokemon.ImageDimensions = pokegold::ImageDimensions::Size_40x40;
                        pokemon.FrontImage = std::vector<u8>(k_imageBufferSize_5x5, 0);
                        pokemon.BackImage = std::vector<u8>(k_imageBufferSize_6x6, 0);
                        data.BadDataList.emplace_back(pokegold::BadDataReason::PokemonImage, i);
                        base::Log(TAG, "bad data (pokemon image back, idx={})", i);
                    }
                    else
                    {
                        pokemon.BackImage = std::vector<u8>(imageBuffer.begin(), imageBuffer.begin() + size);
                    }
                }
            }
        }
    }

    base::Log(TAG, "read pokemon (unown image)");
    for (size_t i = 0; i < 26; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("포켓몬 (안농 이미지: {}/26)", i + 1));
        m_openProgressState.Increase();

        auto &unownImage = data.UnownImages[i];

        if (isHackedUnownIds)
        {
            size_t offset = pokegold::Calc(data.GetByte(0x1fc7dd), data.GetBytes(0x1fc7de, 2)) + i;
            unownImage.ImageDimensions = pokegold::ImageDimensions(data.GetByte(offset));
        }
        else
        {
            // NOTE: 포켓몬 항목에서 이미 처리됨.
        }

        size_t offset = pokegold::CalcFromEncodedBank(data.GetBytes(0x7c000 + (i * 6), 3));
        auto bytes = data.GetBytes(offset, 0x400);
        auto size = lzcomp::Uncompress(imageBuffer, bytes);

        if (size == 0 || size < GetBuferSize(unownImage.ImageDimensions))
        {
            unownImage.FrontImage = std::vector<u8>(k_imageBufferSize_5x5, 0);
            unownImage.BackImage = std::vector<u8>(k_imageBufferSize_6x6, 0);
            data.BadDataList.emplace_back(pokegold::BadDataReason::UnownImage, i);
            base::Log(TAG, "bad data (pokemon (unown front image), idx={})", i);
        }
        else
        {
            unownImage.FrontImage = std::vector<u8>(imageBuffer.begin(), imageBuffer.begin() + size);

            offset = pokegold::CalcFromEncodedBank(data.GetBytes(0x7c000 + (i * 6) + 3, 3));
            bytes = data.GetBytes(offset, 0x400);
            size = lzcomp::Uncompress(imageBuffer, bytes);

            if (size == 0 || size < k_imageBufferSize_6x6)
            {
                unownImage.FrontImage = std::vector<u8>(k_imageBufferSize_5x5, 0);
                unownImage.BackImage = std::vector<u8>(k_imageBufferSize_6x6, 0);
                data.BadDataList.emplace_back(pokegold::BadDataReason::UnownImage, i);
                base::Log(TAG, "bad data (pokemon (unown back image), idx={})", i);
            }
            else
            {
                unownImage.BackImage = std::vector<u8>(imageBuffer.begin(), imageBuffer.begin() + size);
            }
        }
    }

    return !m_openProgressState.HandlePausedOrCanceled();
}

bool services::Pokegold::Open_ReadTrainerGroups(pokegold::Data &data)
{
    base::Log(TAG, "read trainer groups (name)");
    size_t nameOffset = pokegold::Calc(data.GetBytes(0x35d5, 3));
    for (size_t i = 0; i < 68; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("트레이너 그룹 (이름: {}/68)", i + 1));
        m_openProgressState.Increase();

        auto &trainerGroup = data.TrainerGroups[i];

        if (i < 67)
        {
            const auto bytes = data.GetBytesUntil(nameOffset, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            trainerGroup.Name = bytes;
            nameOffset += bytes.size();
        }
        else
        {
            const u8 bank = pokegold::CalcBank(0x23995);
            size_t offset = pokegold::Calc(bank, data.GetBytes(0x23995, 2));

            const auto bytes = data.GetBytesUntil(offset, [&](size_t idx, u8 b) { return b == 0x50; }, true);
            trainerGroup.Name = bytes;
            nameOffset += bytes.size();
        }

        if (trainerGroup.Name.HasBadData() || trainerGroup.Name.GetData().size() > 26)
        {
            trainerGroup.Name = "[50]";
            data.BadDataList.emplace_back(pokegold::BadDataReason::TrainerGroupName, i);
        }
    }

    base::Log(TAG, "read trainer groups (image)");
    std::vector<u8> imageBuffer(0x400, 0);
    for (size_t i = 0; i < 66; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("트레이너 그룹 (이미지: {}/66)", i + 1));
        m_openProgressState.Increase();

        auto &trainerGroup = data.TrainerGroups[i];

        // color
        {
            trainerGroup.Colors[0] = pokegold::Color(data.GetBytes(0xb511 + (i * 4) + 0, 2));
            trainerGroup.Colors[1] = pokegold::Color(data.GetBytes(0xb511 + (i * 4) + 2, 2));
        }

        // image
        {
            auto offset = pokegold::CalcFromEncodedBank(data.GetBytes(0x80000 + (i * 3), 3));
            auto bytes = data.GetBytes(offset, 0x400);
            auto size = lzcomp::Uncompress(imageBuffer, bytes);

            if (size == 0 || size < k_imageBufferSize_7x7)
            {
                trainerGroup.Image = std::vector<u8>(k_imageBufferSize_7x7, 0);
                data.BadDataList.emplace_back(pokegold::BadDataReason::TrainerGroupImage, i);
            }
            else
            {
                trainerGroup.Image = std::vector<u8>(imageBuffer.begin(), imageBuffer.begin() + size);
            }
        }

        // 플레이어, 튜토리얼 이미지
        if (i == 11)
        {
            // color
            {
                trainerGroup.BackColors[0] = pokegold::Color(data.GetBytes(0xb50d + 0, 2));
                trainerGroup.BackColors[1] = pokegold::Color(data.GetBytes(0xb50d + 2, 2));
            }

            // image
            {
                u8 bank = data.GetByte(0x3f9c7);
                auto offset = pokegold::Calc(bank, data.GetBytes(0x3f9b7, 2));
                auto bytes = data.GetBytes(offset, 0x400);
                auto size = lzcomp::Uncompress(imageBuffer, bytes);

                if (size == 0 || size < k_imageBufferSize_6x6)
                {
                    trainerGroup.BackImage = std::vector<u8>(k_imageBufferSize_6x6, 0);
                    trainerGroup.DudeBackImage = std::vector<u8>(k_imageBufferSize_6x6, 0);
                    data.BadDataList.emplace_back(pokegold::BadDataReason::TrainerGroupPlayerBackImage, i);
                }
                else
                {
                    trainerGroup.BackImage = std::vector<u8>(imageBuffer.begin(), imageBuffer.begin() + size);

                    auto offset = pokegold::Calc(bank, data.GetBytes(0x3f9c1, 2));
                    auto bytes = data.GetBytes(offset, 0x400);
                    auto size = lzcomp::Uncompress(imageBuffer, bytes);

                    if (size == 0 || size < k_imageBufferSize_6x6)
                    {
                        trainerGroup.DudeBackImage = std::vector<u8>(k_imageBufferSize_6x6, 0);
                        data.BadDataList.emplace_back(pokegold::BadDataReason::TrainerGroupPlayerBackImage, i);
                    }
                    else
                    {
                        trainerGroup.DudeBackImage = std::vector<u8>(imageBuffer.begin(), imageBuffer.begin() + size);
                    }
                }
            }
        }
    }

    return !m_openProgressState.HandlePausedOrCanceled();
}

bool services::Pokegold::Open_ReadTypes(pokegold::Data &data)
{
    base::Log(TAG, "read type (names)");
    for (size_t i = 0; i < 28; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("타입 (이름: {}/28)", i + 1));
        m_openProgressState.Increase();

        auto &type = data.Types[i];

        size_t offset = pokegold::Calc(0x14, data.GetBytes(0x50a57 + (i * 2), 2));
        type.Name = data.GetBytesUntil(offset, [&](size_t idx, u8 b) { return b == 0x50; }, true);

        if (type.Name.HasBadData() || type.Name.GetData().size() > 9)
        {
            type.Name = "[50]";
            data.BadDataList.emplace_back(pokegold::BadDataReason::TypeName, i);
        }
    }

    const bool isHackedTypeMatchups = data.MatchBytes(0x1fc7d4, {0xfe, 0xff});
    size_t typeMatchupsOffset = isHackedTypeMatchups ? pokegold::Calc(data.GetBytes(0x348a7, 3)) : 0x34d01;
    size_t weatherTypeModifiersOffset = isHackedTypeMatchups ? pokegold::Calc(data.GetBytes(0x348aa, 3)) : 0xfbe68;
    size_t weatherMoveModifiersOffset = isHackedTypeMatchups ? pokegold::Calc(data.GetBytes(0x348ad, 3)) : 0xfbe75;

    base::Log(TAG, "read type (type matchups)");
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage("타입 (상성 정보)");
        m_openProgressState.Increase();

        bool foresight = false;
        while (true)
        {
            const u8 attacker = data.GetByte(typeMatchupsOffset++);
            if (attacker == 0xff)
                break;

            if (attacker == 0xfe)
            {
                foresight = true;
                continue;
            }

            const u8 defender = data.GetByte(typeMatchupsOffset++);
            const u8 effectiveness = data.GetByte(typeMatchupsOffset++);

            // 손상 데이터 체크 및 기본값 사용
            if (attacker >= data.Types.size() || !(effectiveness % 5 == 0 && effectiveness <= 20))
            {
                for (auto &e : data.Types)
                    e.TypeMatchups.clear();

                typeMatchupsOffset = 0x34d01;
                data.SetBytes(0x34d01, embed::GetPokegoldDefaultTypeMatchupsData());
                data.BadDataList.emplace_back(pokegold::BadDataReason::TypeMatchups, nullptr);
                continue;
            }

            pokegold::TypeMatchup newMatchup;
            newMatchup.AttackerTypeId = attacker;
            newMatchup.DefenderTypeId = defender;
            newMatchup.TypeEffectiveness = pokegold::TypeEffectiveness(effectiveness);
            newMatchup.IsForesight = foresight;
            data.Types[attacker].TypeMatchups.push_back(newMatchup);
        }
    }

    base::Log(TAG, "read type (type weather modifiers)");
    {

        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage("타입 (날씨 보정 데이터 - 타입)");
        m_openProgressState.Increase();

        while (true)
        {
            const u8 weather = data.GetByte(weatherTypeModifiersOffset++);
            if (weather == 0xff)
                break;

            const u8 typeId = data.GetByte(weatherTypeModifiersOffset++);
            const u8 effectiveness = data.GetByte(weatherTypeModifiersOffset++);

            // 손상 데이터 체크 및 기본값 사용
            if (typeId >= data.Types.size() || weather > 3 || !(effectiveness % 5 == 0 && effectiveness <= 20))
            {
                for (auto &e : data.Types)
                    e.WeatherModifiers.clear();

                weatherTypeModifiersOffset = 0xfbe68;
                data.SetBytes(0xfbe68, embed::GetPokegoldDefaultTypeWeatherModifiersData());
                data.BadDataList.emplace_back(pokegold::BadDataReason::TypeWeatherModifiers, nullptr);
                continue;
            }

            pokegold::WeatherModifier newModifier;
            newModifier.Weather = pokegold::BattleWeather(weather);
            newModifier.TypeEffectiveness = pokegold::TypeEffectiveness(effectiveness);
            data.Types[typeId].WeatherModifiers.push_back(newModifier);
        }
    }

    base::Log(TAG, "read type (move effect weather modifiers)");
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage("타입 (날씨 보정 데이터 - 기술 효과)");
        m_openProgressState.Increase();

        while (true)
        {
            const u8 weather = data.GetByte(weatherMoveModifiersOffset++);
            if (weather == 0xff)
                break;

            const u8 moveEffectId = data.GetByte(weatherMoveModifiersOffset++);
            const u8 effectiveness = data.GetByte(weatherMoveModifiersOffset++);

            // 손상 데이터 체크 및 기본값 사용
            if (size_t(moveEffectId) >= data.MoveEffects.size() || weather > 3 || !(effectiveness % 5 == 0 && effectiveness <= 20))
            {
                for (auto &e : data.MoveEffects)
                    e.WeatherModifiers.clear();

                weatherMoveModifiersOffset = 0xfbe75;
                data.SetBytes(0xfbe75, embed::GetPokegoldDefaultMoveEffectWeatherModifiersData());
                data.BadDataList.emplace_back(pokegold::BadDataReason::MoveEffectWeatherModifiers, nullptr);
                continue;
            }

            pokegold::WeatherModifier newModifier;
            newModifier.Weather = pokegold::BattleWeather(weather);
            newModifier.TypeEffectiveness = pokegold::TypeEffectiveness(effectiveness);
            data.MoveEffects[moveEffectId].WeatherModifiers.push_back(newModifier);
        }
    }

    return !m_openProgressState.HandlePausedOrCanceled();
}

bool services::Pokegold::Open_ReadMaps(pokegold::Data &data)
{
    base::Log(TAG, "read npc colors");
    for (size_t i = 0, max = 4; i < max; i++)
    {
        if (m_openProgressState.HandlePausedOrCanceled())
            return false;

        m_openProgressState.UpdateMessage(std::format("맵 (오브젝트 색상: {}/{})", i + 1, max));
        m_openProgressState.Increase();

        size_t offset = 0xb87e + (i * 64);
        for (auto &npcColor : data.Maps.NpcColors[i])
        {
            for (size_t j = 0; j < 4; j++)
            {
                npcColor[j] = data.GetBytes(offset, 2);
                offset += 2;
            }
        }
    }

    base::Log(TAG, "read maps");
    {
        // Map vars
        {
            const u8 bank = data.GetByte(0x1ff7);
            const size_t mapVarOffset = pokegold::Calc(bank, data.GetBytes(0x1ffa, 2));

            for (auto &mapVar : data.Maps.MapVariables)
            {
                mapVar.Group = 0xff;
                mapVar.Number = 0xff;
                mapVar.IsDummy = true;
            }

            for (size_t i = 0;;)
            {
                auto bytes = data.GetBytes(mapVarOffset + i, 4);
                if (bytes[0] == 0xff)
                    break;

                u16 index = (bytes[2] | (bytes[3] << 8)) - 0xd74a;
                data.Maps.MapVariables[index].Group = bytes[0] - 1;
                data.Maps.MapVariables[index].Number = bytes[1] - 1;
                data.Maps.MapVariables[index].IsDummy = false;

                i += 4;
            }
        }

        // Map data
        {
            const u8 bank = data.GetByte(0x2d46);
            const size_t ptrBaseOffset = pokegold::Calc(bank, data.GetBytes(0x2d29, 2));

            std::array<size_t, data.Maps.MapGroups.size()> groupCnts;
            {
                for (size_t i = 0, max = data.Maps.MapGroups.size(); i < max; i++)
                {
                    const size_t mapGroupOffset = pokegold::Calc(bank, data.GetBytes(ptrBaseOffset + (i * 2), 2));
                    const size_t nextMapGroupOffset = pokegold::Calc(bank, data.GetBytes(ptrBaseOffset + ((i + 1) * 2), 2));

                    if (i == max - 1)
                    {
                        groupCnts[i] = 0;

                        for (size_t j = 0; groupCnts[i] < 255;)
                        {
                            const u8 attrBank = data.GetByte(mapGroupOffset + j);
                            const u16 attrPtr = data.GetByte(mapGroupOffset + j + 3) | (data.GetByte(mapGroupOffset + j + 4) << 8);
                            if (/* attrBank != bank || */ !(attrPtr >= 0x4000 && attrPtr <= 0x7fff))
                            {
                                // MEMO: 맵 속성의 뱅크는 툴에서 재배치가 일어나기 때문에 뱅크 일치여부는 제외함
                                break;
                            }

                            const size_t attrOffset = pokegold::Calc(attrBank, data.GetBytes(mapGroupOffset + j + 3, 2));
                            const u8 locationId = data.GetByte(attrOffset);
                            const u8 width = data.GetByte(attrOffset + 4);
                            const u8 height = data.GetByte(attrOffset + 3);
                            if (locationId >= 95 || width * height == 0)
                                break;

                            groupCnts[i]++;
                            j += 9;
                        }
                    }
                    else
                    {
                        groupCnts[i] = (nextMapGroupOffset - mapGroupOffset) / 9;
                    }
                }
            }

            for (size_t i = 0, max = data.Maps.MapGroups.size(); i < max; i++)
            {
                if (m_openProgressState.HandlePausedOrCanceled())
                    return false;

                m_openProgressState.UpdateMessage(std::format("맵 (기본 정보: {}/{})", i + 1, max));
                m_openProgressState.Increase();

                const size_t mapGroupOffset = pokegold::Calc(bank, data.GetBytes(ptrBaseOffset + (i * 2), 2));
                for (size_t j = 0; j < groupCnts[i]; j++)
                {
                    const size_t curretMapGroupOffset = mapGroupOffset + (j * 9);
                    const size_t currentMapAttributeOffset = pokegold::Calc(data.GetByte(curretMapGroupOffset + 0), data.GetBytes(curretMapGroupOffset + 3, 2));

                    pokegold::Map newMap;

                    // header
                    {
                        newMap.TilesetId = data.GetByte(curretMapGroupOffset + 1);
                        newMap.Environment = pokegold::MapEnvironment(data.GetByte(curretMapGroupOffset + 2));
                        newMap.LocationId = data.GetByte(curretMapGroupOffset + 5);
                        newMap.MusicId = data.GetByte(curretMapGroupOffset + 6);
                        newMap.PhoneMuted = ((data.GetByte(curretMapGroupOffset + 7) & 0xf0) >> 4) == 1;
                        newMap.Color = pokegold::MapColor(data.GetByte(curretMapGroupOffset + 7) & 0x0f);
                        newMap.FishingGroupId = data.GetByte(curretMapGroupOffset + 8);
                    }

                    // attributes
                    {
                        newMap.BorderTileId = data.GetByte(currentMapAttributeOffset + 0);
                        newMap.Width = data.GetByte(currentMapAttributeOffset + 2);
                        newMap.Height = data.GetByte(currentMapAttributeOffset + 1);
                    }

                    data.Maps.MapGroups[i].push_back(newMap);
                }
            }

            for (size_t i = 0, max = data.Maps.MapGroups.size(); i < max; i++)
            {
                if (m_openProgressState.HandlePausedOrCanceled())
                    return false;

                m_openProgressState.UpdateMessage(std::format("맵 (추가 정보: {}/{})", i + 1, max));
                m_openProgressState.Increase();

                const size_t mapGroupOffset = pokegold::Calc(bank, data.GetBytes(ptrBaseOffset + (i * 2), 2));
                for (size_t j = 0; j < groupCnts[i]; j++)
                {
                    const size_t curretMapGroupOffset = mapGroupOffset + (j * 9);
                    const size_t currentMapAttributeOffset = pokegold::Calc(data.GetByte(curretMapGroupOffset + 0), data.GetBytes(curretMapGroupOffset + 3, 2));

                    const size_t tilesOffset = pokegold::Calc(data.GetByte(currentMapAttributeOffset + 3), data.GetBytes(currentMapAttributeOffset + 4, 2));
                    const size_t scriptsOffset = pokegold::Calc(data.GetByte(currentMapAttributeOffset + 6), data.GetBytes(currentMapAttributeOffset + 7, 2));
                    const size_t eventsOffset = pokegold::Calc(data.GetByte(currentMapAttributeOffset + 6), data.GetBytes(currentMapAttributeOffset + 9, 2));

                    // tiles
                    {
                        const u8 width = data.Maps.MapGroups[i][j].Width;
                        const u8 height = data.Maps.MapGroups[i][j].Height;

                        const u8 tileBank = data.GetByte(currentMapAttributeOffset + 3);
                        const size_t tileOffset = pokegold::Calc(tileBank, data.GetBytes(currentMapAttributeOffset + 4, 2));

                        for (size_t a = 0; a < width * height; a++)
                            data.Maps.MapGroups[i][j].Tiles.push_back(data.GetByte(tileOffset + a));
                    }

                    // TODO: 테스트... 작업 필요
                    data.Maps.MapGroups[i][j].ScriptsBank = data.GetByte(currentMapAttributeOffset + 6);
                    data.Maps.MapGroups[i][j].ScriptsPtr = data.GetByte(currentMapAttributeOffset + 7) | (data.GetByte(currentMapAttributeOffset + 8) << 8);
                    data.Maps.MapGroups[i][j].EventsPtr = data.GetByte(currentMapAttributeOffset + 9) | (data.GetByte(currentMapAttributeOffset + 10) << 8);

                    u8 connectionByte = data.GetByte(currentMapAttributeOffset + 11);
                    if (connectionByte != 0)
                    {
                        size_t connectionOffset = currentMapAttributeOffset + 12;

                        for (int c = 4; c >= 1; c--)
                        {
                            auto &bits = k_bits[c - 1];

                            if ((connectionByte & bits) != 0)
                            {
                                u8 targetMapGroup = data.GetByte(connectionOffset + 0) - 1;
                                u8 targetMapNo = data.GetByte(connectionOffset + 1) - 1;

                                auto &targetMap = data.Maps.MapGroups[targetMapGroup][targetMapNo];

                                i8 x = (i8)data.GetByte(connectionOffset + 9);
                                i8 y = (i8)data.GetByte(connectionOffset + 8);

                                // base::Log(TAG, "{}, {} ({}, {}, {} ,{})", i, j, targetMapGroupIdx, targetMapIdx, x, y);

                                connectionOffset += 12;

                                if (bits == 0b1000)
                                    data.Maps.MapGroups[i][j].NorthConnection = {targetMapGroup, targetMapNo, i8(x / -2)};
                                else if (bits == 0b0100)
                                    data.Maps.MapGroups[i][j].SouthConnection = {targetMapGroup, targetMapNo, i8(x / -2)};
                                else if (bits == 0b0010)
                                    data.Maps.MapGroups[i][j].WestConnection = {targetMapGroup, targetMapNo, i8(y / -2)};
                                else if (bits == 0b0001)
                                    data.Maps.MapGroups[i][j].EastConnection = {targetMapGroup, targetMapNo, i8(y / -2)};
                            }
                        }
                    }
                }
            }
        }
    }

    return !m_openProgressState.HandlePausedOrCanceled();
}
