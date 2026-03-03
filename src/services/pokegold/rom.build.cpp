#include "rom.h"

#include "base/files/file_util.h"
#include "base/log.h"
#include "base/resources.h"
#include "base/resources_embed.h"
#include "base/sidecar/rgbds.h"
#include "services/pokegold/data/game_data.h"
#include "services/pokegold/utils.h"
#include "utils/free_space.h"

#include <array>
#include <cstddef>
#include <filesystem>
#include <format>
#include <string>
#include <unordered_map>

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

    const std::vector<pokegold::FreeSpaceRange> k_typeNameFreeSpaces = {
        {0x050a8f, 0x050ae9},
        {0x053b57, 0x053be8},
    };

    const std::vector<pokegold::FreeSpaceRange> k_imageFreeSpaces = {
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
}

std::optional<std::filesystem::path> pokegold::Rom::Build()
{
    base::Log(TAG, "start build.");
    m_buildProgressState.Reset();

    std::vector<std::function<bool(internal::RomBuildData &)>> funcs = {
        [this](auto &data) { return Build_Startup(data); },
        [this](auto &data) { return Build_ItemSources(data); },
        [this](auto &data) { return Build_MoveSources(data); },
        [this](auto &data) { return Build_PokemonSources(data); },
        [this](auto &data) { return Build_TrainerGroupSources(data); },
        [this](auto &data) { return Build_TypeSources(data); },
        [this](auto &data) { return Build_Assemble(data); },
    };

    auto workDir = *m_workspacePathState;
    std::filesystem::remove_all(workDir);
    std::filesystem::create_directories(workDir);

    internal::RomBuildData data(workDir);
    for (const auto &func : funcs)
    {
        if (!func(data))
            return std::nullopt;
    }

    base::Log(TAG, "finish build.");

    return workDir / (s_targetName + ".bin");
}

bool pokegold::Rom::Build_Startup(internal::RomBuildData &data)
{
    base::Log(TAG, "build: copy baserom");
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        m_buildProgressState.UpdateMessage("베이스롬 복사");
        m_buildProgressState.Increase();

        std::filesystem::copy_file(*m_romFilePathState, *m_workspacePathState / (s_baseName + ".bin"));
    }

    base::Log(TAG, "build: copy save file");
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        m_buildProgressState.UpdateMessage("세이브 파일 복사");
        m_buildProgressState.Increase();

        auto savePath = (*m_romFilePathState).parent_path() / ((*m_romFilePathState).stem().string() + ".sav");
        auto targetSavePath = *m_workspacePathState / (s_targetName + ".sav");
        if (std::filesystem::exists(savePath))
            std::filesystem::copy_file(savePath, targetSavePath);
    }

    base::Log(TAG, "build: write macro");
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        m_buildProgressState.UpdateMessage("매크로 소스 작성");
        m_buildProgressState.Increase();

        constexpr auto filename = "GSEditor.Macros.asm";
        data.GetSourceStream() << GetAsmInclude(filename);

        base::WriteBytesToFile(*m_workspacePathState / filename, embed::GetPokegoldMacrosSource());
    }

    base::Log(TAG, "build: write cleanup");
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        if (m_appConfigs.GetBuildCleanup())
        {
            m_buildProgressState.UpdateMessage("롬 정리 소스 작성");
            m_buildProgressState.Increase();

            constexpr auto filename = "GSEditor.Cleanup.asm";
            data.GetSourceStream() << GetAsmInclude(filename);

            std::ofstream srcStream(*m_workspacePathState / filename);
            srcStream << GetAsmSection(0x1a0000, "GSEditor_Cleanup_Pokedex_0")
                      << GetAsmLine("ds $4000")
                      << GetAsmSection(0x1a4000, "GSEditor_Cleanup_Pokedex_1")
                      << GetAsmLine("ds $4000")

                      << GetAsmSection(0x1b0000, "GSEditor_Cleanup_Strings_0")
                      << GetAsmLine("ds $4000")
                      << GetAsmSection(0x1b4000, "GSEditor_Cleanup_Strings_1")
                      << GetAsmLine("ds $4000")
                      << GetAsmSection(0x1b8000, "GSEditor_Cleanup_Strings_2")
                      << GetAsmLine("ds $4000")

                      << GetAsmSection(0x34d01, "GSEditor_Cleanup_TypeMatchups_0")
                      << GetAsmLine("ds 332")
                      << GetAsmSection(0x1fc7d4, "GSEditor_Cleanup_TypeMatchups_1")
                      << GetAsmLine("ds $382c");

            for (size_t current = 0, max = k_typeNameFreeSpaces.size(); current < max; current++)
            {
                const auto &freeSpace = k_typeNameFreeSpaces[current];

                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("롬 정리 소스 작성 (타입 이름: {}/{})", current + 1, max));
                m_buildProgressState.Increase();

                srcStream << GetAsmSection(freeSpace.From, "GSEditor_Cleanup_TypeNameFreeSpace_0x{:x}", freeSpace.From)
                          << GetAsmLine("ds {}", freeSpace.To - freeSpace.From + 1);
            }

            for (size_t current = 0, max = k_imageFreeSpaces.size(); current < max; current++)
            {
                const auto &freeSpace = k_imageFreeSpaces[current];

                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("롬 정리 소스 작성 (이미지: {}/{})", current + 1, max));
                m_buildProgressState.Increase();

                srcStream << GetAsmSection(freeSpace.From, "GSEditor_Cleanup_ImageFreeSpace_0x{:x}", freeSpace.From)
                          << GetAsmLine("ds {}", freeSpace.To - freeSpace.From + 1);
            }
        }
        else
        {
            m_buildProgressState.UpdateMessage("롬 정리 소스 작성 (생략)");
            m_buildProgressState.Increase();
        }
    }

    // names section 기록
    data.GetNamesSourceStream() << GetAsmSection(0x1b0000, "GSEditor_Names");

    return !m_buildProgressState.HandlePausedOrCanceled();
}

bool pokegold::Rom::Build_ItemSources(internal::RomBuildData &data)
{
    constexpr auto filename = "GSEditor.Items.asm";
    std::ofstream srcStream(*m_workspacePathState / filename);
    data.GetSourceStream() << GetAsmInclude(filename);

    base::Log(TAG, "write item (primary)");
    {
        srcStream << GetAsmSection(0x697b, "GSEditor_Item_Properties")
                  << GetAsmLine("GSEditor_Item_Properties::");

        for (size_t i = 0; i < 256; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("아이템 (기본 정보: {}/256)", i + 1));
            m_buildProgressState.Increase();

            const auto &e = m_data.Items()[i];
            srcStream << GetAsmBytes({
                u8(e.Price & 0xff),
                u8((e.Price >> 8) & 0xff),
                e.Effect,
                e.Parameter,
                e.Property,
                e.Pocket,
                u8(((e.FieldMenu & 0x0f) << 4) | (e.BattleMenu & 0x0f)),
            });
        }
    }

    base::Log(TAG, "write item (name)");
    {
        // data
        data.GetNamesSourceStream() << GetAsmLine("GSEditor_Item_Names::");
        for (size_t i = 0; i < 256; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("아이템 (이름: {}/256)", i + 1));
            m_buildProgressState.Increase();

            const auto &e = m_data.Items()[i];
            data.GetNamesSourceStream() << GetAsmBytes(e.Name.GetData());
        }

        // ptr
        srcStream << GetAsmSection(0x35cc, "GSEditor_Item_Names_Pointer_0")
                  << GetAsmLine("db BANK(GSEditor_Item_Names)")
                  << GetAsmLine("dw GSEditor_Item_Names")

                  << GetAsmSection(0x515cd, "GSEditor_Item_Names_Pointer_1")
                  << GetAsmLine("dw GSEditor_Item_Names")

                  << GetAsmSection(0x515d7, "GSEditor_Item_Names_Pointer_2")
                  << GetAsmLine("dw GSEditor_Item_Names");
    }

    base::Log(TAG, "write item (description)");
    {
        std::array<std::string, 256> labels;

        // data
        {
            std::unordered_map<std::string, std::string> labelCacheMap;

            srcStream << GetAsmSection(0x1b8200, "GSEditor_Item_Descriptions")
                      << GetAsmLine("GSEditor_Item_Descriptions::");
            for (size_t i = 0; i < 256; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("아이템 (설명: {}/256)", i + 1));
                m_buildProgressState.Increase();

                const auto label = std::format("GSEditor_Item_Description_{}", i);
                auto &e = m_data.Items()[i].Description;
                auto str = e.ToEditorString();

                if (labelCacheMap.contains(str))
                {
                    labels[i] = labelCacheMap[str];
                }
                else
                {
                    srcStream << GetAsmLine("{}:", label)
                              << GetAsmBytes(e.GetData());

                    labelCacheMap[str] = label;
                    labels[i] = label;
                }
            }
        }

        // ptr
        {
            srcStream << GetAsmSection(0x1b8000, "GSEditor_Item_Description_Pointers")
                      << GetAsmLine("GSEditor_Item_Description_Pointers::");
            for (size_t i = 0; i < 256; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("아이템 (설명 포인터: {}/256)", i + 1));
                m_buildProgressState.Increase();

                srcStream << GetAsmLine("dw {}", labels[i]);
            }
        }
    }

    return !m_buildProgressState.HandlePausedOrCanceled();
}

bool pokegold::Rom::Build_MoveSources(internal::RomBuildData &data)
{
    constexpr auto filename = "GSEditor.Moves.asm";
    std::ofstream srcStream(*m_workspacePathState / filename);
    data.GetSourceStream() << GetAsmInclude(filename);

    base::Log(TAG, "write move (primary)");
    {
        srcStream << GetAsmSection(0x4172e, "GSEditor_Move_Properties")
                  << GetAsmLine("GSEditor_Move_Properties::");

        for (size_t i = 0; i < 251; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("기술 (기본 정보: {}/251)", i + 1));
            m_buildProgressState.Increase();

            const auto &e = m_data.Moves()[i];
            srcStream << GetAsmBytes({
                e.Id,
                e.Effect,
                e.Power,
                e.Type,
                e.Accuracy,
                e.PP,
                e.EffectChance,
            });
        }
    }

    base::Log(TAG, "write move (name)");
    {
        // ptr
        srcStream << GetAsmSection(0x35c6, "GSEditor_Move_Names_Pointer")
                  << GetAsmLine("db BANK(GSEditor_Move_Names)")
                  << GetAsmLine("dw GSEditor_Move_Names");

        // data
        data.GetNamesSourceStream() << GetAsmLine("GSEditor_Move_Names::");
        for (size_t i = 0; i < 251; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("기술 (이름: {}/251)", i + 1));
            m_buildProgressState.Increase();

            const auto &e = m_data.Moves()[i];
            data.GetNamesSourceStream() << GetAsmBytes(e.Name.GetData());
        }
    }

    base::Log(TAG, "write move (description)");
    {
        std::array<std::string, 251> labels;

        // data
        {
            std::unordered_map<std::string, std::string> labelCacheMap;

            srcStream << GetAsmSection(0x1b4200, "GSEditor_Move_Descriptions")
                      << GetAsmLine("GSEditor_Move_Descriptions::")

                      // MEMO: 더미 데이터 ("？[50]")
                      << GetAsmLine("GSEditor_Move_Description_0:")
                      << GetAsmBytes({230, 80});

            labelCacheMap["？"] = "GSEditor_Move_Description_0";

            for (size_t i = 0; i < 251; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("기술 (설명: {}/251)", i + 1));
                m_buildProgressState.Increase();

                const auto label = std::format("GSEditor_Move_Description_{}", i + 1);
                auto &e = m_data.Moves()[i].Description;
                auto str = e.ToEditorString();

                if (labelCacheMap.contains(str))
                {
                    labels[i] = labelCacheMap[str];
                }
                else
                {
                    srcStream << GetAsmLine("{}:", label)
                              << GetAsmBytes(e.GetData());

                    labelCacheMap[str] = label;
                    labels[i] = label;
                }
            }
        }

        // ptr
        {
            srcStream << GetAsmSection(0x1b4000, "GSEditor_Move_Description_Pointers")
                      << GetAsmLine("GSEditor_Move_Description_Pointers::");
            for (size_t i = 0; i < 251; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("기술 (설명 포인터: {}/251)", i + 1));
                m_buildProgressState.Increase();

                srcStream << GetAsmLine("dw {}", labels[i]);
            }

            for (size_t i = 0; i < 5; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("기술 (더미 데이터: {}/5)", i + 1));
                m_buildProgressState.Increase();

                srcStream << GetAsmLine("dw GSEditor_Move_Description_0");
            }
        }
    }

    base::Log(TAG, "write move (TM / HM)");
    {
        srcStream << GetAsmSection(0x119f5, "GSEditor_TMHMs")
                  << GetAsmLine("GSEditor_TMHMs::");

        for (size_t i = 0, max = m_data.TMHMs().size(); i < max; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("기술 (기술 & 비전 머신: {}/{})", i + 1, max));
            m_buildProgressState.Increase();

            srcStream << GetAsmBytes({m_data.TMHMs()[i].MoveId});
        }
    }

    return !m_buildProgressState.HandlePausedOrCanceled();
}

bool pokegold::Rom::Build_PokemonSources(internal::RomBuildData &data)
{
    constexpr auto filename = "GSEditor.Pokemons.asm";
    std::ofstream srcStream(*m_workspacePathState / filename);
    data.GetSourceStream() << GetAsmInclude(filename);

    base::Log(TAG, "write pokemon (primary)");
    {
        srcStream << GetAsmSection(0x51bdf, "GSEditor_Pokemon_Properties")
                  << GetAsmLine("GSEditor_Pokemon_Properties::");

        for (size_t i = 0; i < 256; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("포켓몬 (기본 정보: {}/256)", i + 1));
            m_buildProgressState.Increase();

            const auto &e = m_data.Pokemons()[i];

            std::array<u8, 8> tmhms{0};
            for (u8 j = 0; j < 8; j++)
            {
                for (u8 a = 0; a < 8; a++)
                {
                    u8 idx = (j * 8) + a;
                    if (e.TMHMs[idx])
                        tmhms[j] |= k_bits[a];
                }
            }

            srcStream << GetAsmBytes({
                e.Id,
                e.Hp,
                e.Attack,
                e.Defence,
                e.Speed,
                e.SpAttack,
                e.SpDefence,
                e.TypeIds[0],
                e.TypeIds[1],
                e.CatchRate,
                e.BaseExp,
                e.ItemIds[0],
                e.ItemIds[1],
                u8(e.GenderRate),
                100,
                e.EggHatchLevel,
                5,
                u8(e.ImageDimensions),
                0,
                0,
                0,
                0,
                u8(e.GrowthRate),
                u8(((u8(e.EggGroups[0]) & 0x0f) << 4) | (u8(e.EggGroups[1]) & 0x0f)),
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
    }

    base::Log(TAG, "write pokemon (evolves, moves)");
    {
        // data
        {
            srcStream << GetAsmSection(0x425e3, "GSEditor_Pokemon_EvoMoves")
                      << GetAsmLine("GSEditor_Pokemon_EvoMoves::");

            for (size_t i = 0; i < 251; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("포켓몬 (진화 & 자력기: {}/251)", i + 1));
                m_buildProgressState.Increase();

                std::vector<u8> bytes;
                {
                    const auto &e = m_data.Pokemons()[i];

                    for (const auto &method : e.EvolutionMethods)
                    {
                        switch (method.EvolutionMethodType)
                        {
                        case EvolutionMethodType::LevelUp:
                            bytes.push_back(u8(method.EvolutionMethodType));
                            bytes.push_back(method.Level);
                            bytes.push_back(method.PokemonId);
                            break;
                        case EvolutionMethodType::Trade:
                        case EvolutionMethodType::UseItem:
                            bytes.push_back(u8(method.EvolutionMethodType));
                            bytes.push_back(method.ItemId);
                            bytes.push_back(method.PokemonId);
                            break;
                        case EvolutionMethodType::LevelUpWithHappiness:
                            bytes.push_back(u8(method.EvolutionMethodType));
                            bytes.push_back(method.Happiness);
                            bytes.push_back(method.PokemonId);
                            break;
                        case EvolutionMethodType::LevelUpWithStats:
                            bytes.push_back(u8(method.EvolutionMethodType));
                            bytes.push_back(method.Level);
                            bytes.push_back(method.Stats);
                            bytes.push_back(method.PokemonId);
                            break;
                        }
                    }

                    bytes.push_back(0);

                    for (const auto &move : e.Moves)
                    {
                        bytes.push_back(move.Level);
                        bytes.push_back(move.MoveId);
                    }

                    bytes.push_back(0);
                }

                srcStream << GetAsmLine("GSEditor_Pokemon_EvoMove_{}:", i)
                          << GetAsmBytes(bytes);
            }
        }

        // ptr
        {
            srcStream << GetAsmSection(0x423ed, "GSEditor_Pokemon_EvoMove_Pointers")
                      << GetAsmLine("GSEditor_Pokemon_EvoMove_Pointers::");
            for (size_t i = 0; i < 251; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("포켓몬 (진화 & 자력기 포인터: {}/251)", i + 1));
                m_buildProgressState.Increase();

                srcStream << GetAsmLine("dw GSEditor_Pokemon_EvoMove_{}", i);
            }
        }
    }

    base::Log(TAG, "write pokemon (pokedex)");
    {
        // 1
        {
            srcStream << GetAsmSection(0x1a0000, "GSEditor_Pokedex_0");

            for (size_t i = 0; i < 128; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("포켓몬 (도감 1: {}/128)", i + 1));
                m_buildProgressState.Increase();

                std::vector<u8> bytes;
                {
                    const auto &e = m_data.Pokemons()[i];
                    bytes.insert(bytes.end(), e.DexCategoryName.GetData().begin(), e.DexCategoryName.GetData().end());
                    bytes.push_back(e.Height);
                    bytes.push_back(u8(e.Weight & 0x00ff));
                    bytes.push_back(u8((e.Weight & 0xff00) >> 8));
                    bytes.insert(bytes.end(), e.Description.GetData().begin(), e.Description.GetData().end());
                }

                srcStream << GetAsmLine("GSEditor_Pokedex_{}:", i)
                          << GetAsmBytes(bytes);
            }

            srcStream << GetAsmSection(0x442ff, "GSEditor_Pokedex_0_Pointers")
                      << GetAsmLine("GSEditor_Pokedex_0_Pointers::");
            for (size_t i = 0; i < 128; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("포켓몬 (도감 1 포인터: {}/128)", i + 1));
                m_buildProgressState.Increase();

                srcStream << GetAsmLine("dw GSEditor_Pokedex_{}", i);
            }
        }

        // 2
        {
            srcStream << GetAsmSection(0x1a4000, "GSEditor_Pokedex_1");

            for (size_t i = 0; i < 123; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("포켓몬 (도감 2: {}/123)", i + 1));
                m_buildProgressState.Increase();

                std::vector<u8> bytes;
                {
                    const auto &e = m_data.Pokemons()[i + 128];
                    bytes.insert(bytes.end(), e.DexCategoryName.GetData().begin(), e.DexCategoryName.GetData().end());
                    bytes.push_back(e.Height);
                    bytes.push_back(u8(e.Weight & 0x00ff));
                    bytes.push_back(u8((e.Weight & 0xff00) >> 8));
                    bytes.insert(bytes.end(), e.Description.GetData().begin(), e.Description.GetData().end());
                }

                srcStream << GetAsmLine("GSEditor_Pokedex_{}:", i + 128)
                          << GetAsmBytes(bytes);
            }

            srcStream << GetAsmSection(0x443ff, "GSEditor_Pokedex_1_Pointers")
                      << GetAsmLine("GSEditor_Pokedex_1_Pointers::");
            for (size_t i = 0; i < 123; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("포켓몬 (도감 2 포인터: {}/123)", i + 1));
                m_buildProgressState.Increase();

                srcStream << GetAsmLine("dw GSEditor_Pokedex_{}", i + 128);
            }
        }
    }

    base::Log(TAG, "write pokemon (name)");
    {
        srcStream << GetAsmSection(0x35c3, "GSEditor_Pokemon_Names_Pointer_0")
                  << GetAsmLine("db BANK(GSEditor_Pokemon_Names)")
                  << GetAsmLine("dw GSEditor_Pokemon_Names")

                  << GetAsmSection(0x3667, "GSEditor_Pokemon_Names_Pointer_1")
                  << GetAsmLine("dw GSEditor_Pokemon_Names")

                  << GetAsmSection(0x515bf, "GSEditor_Pokemon_Names_Pointer_2")
                  << GetAsmLine("dw GSEditor_Pokemon_Names");

        data.GetNamesSourceStream() << GetAsmLine("GSEditor_Pokemon_Names::");
        for (size_t i = 0; i < 256; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("포켓몬 (이름: {}/256)", i + 1));
            m_buildProgressState.Increase();

            const auto &e = m_data.Pokemons()[i];

            std::array<u8, 10> padded;
            std::fill(padded.begin(), padded.end(), 0x50);
            for (size_t j = 0; j < e.Name.GetData().size(); j++)
                padded[j] = e.Name.GetData()[j];

            data.GetNamesSourceStream() << GetAsmBytes(padded);
        }
    }

    base::Log(TAG, "write pokemon (image & color)");
    {
        // colors
        {
            srcStream << GetAsmSection(0xad15, "GSEditor_Pokemon_Colors")
                      << GetAsmLine("GSEditor_Pokemon_Colors::");

            for (size_t i = 0, max = m_data.Pokemons().size(); i < max; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("포켓몬 (색상: {}/{})", i + 1, max));
                m_buildProgressState.Increase();

                const auto &e = m_data.Pokemons()[i];
                srcStream << GetAsmBytes({
                    e.Colors[0].GetLoByte(),
                    e.Colors[0].GetHiByte(),
                    e.Colors[1].GetLoByte(),
                    e.Colors[1].GetHiByte(),
                    e.ShinyColors[0].GetLoByte(),
                    e.ShinyColors[0].GetHiByte(),
                    e.ShinyColors[1].GetLoByte(),
                    e.ShinyColors[1].GetHiByte(),
                });
            }
        }

        // images
        {
            // ptr
            {
                // egg
                {
                    srcStream << GetAsmSection(0x51897, "GSEditor_Egg_Image_Pointer")
                              << GetAsmLine("dw GSEditor_Egg_Image");
                    srcStream << GetAsmSection(0x5189a, "GSEditor_Egg_Image_Bank")
                              << GetAsmLine("db BANK(GSEditor_Egg_Image)");
                }

                // pokemon
                srcStream << GetAsmSection(0x48000, "GSEditor_Pokemon_Image_Pointers");
                for (size_t i = 0; i < 251; i++)
                {
                    if (m_buildProgressState.HandlePausedOrCanceled())
                        return false;

                    m_buildProgressState.UpdateMessage(std::format("포켓몬 (이미지 포인터: {}/{})", i + 1, 251));
                    m_buildProgressState.Increase();

                    const auto &e = m_data.Pokemons()[i];
                    if (e.Type == PokemonType::Pokemon)
                    {
                        srcStream << GetAsmLine("gse@pics Pokemon, {}", i);
                    }
                    else
                    {
                        srcStream << GetAsmLine("gse@dbw -1, -1")
                                  << GetAsmLine("gse@dbw -1, -1");
                    }
                }
            }

            // data
            for (size_t i = 0, max = m_data.Pokemons().size(); i < max; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("포켓몬 (이미지: {}/{})", i + 1, max));
                m_buildProgressState.Increase();

                const auto &e = m_data.Pokemons()[i];
                if (e.Type == PokemonType::Pokemon)
                {
                    data.PushImageDataBlock(std::format("GSEditor_Pokemon_FrontImage_{}", i), e.FrontImage);
                    data.PushImageDataBlock(std::format("GSEditor_Pokemon_BackImage_{}", i), e.BackImage);
                }
                else if (e.Type == PokemonType::Egg)
                {
                    data.PushImageDataBlock("GSEditor_Egg_Image", e.FrontImage);
                }

                // MEMO:
                //   * PokemonType::Unown: 다른 단계에서 처리
                //   * PokemonType::Dummy: 생략
            }
        }
    }

    base::Log(TAG, "write pokemon (unown image)");
    {
        // ptr
        {
            srcStream << GetAsmSection(0x7c000, "GSEditor_Unown_Image_Pointers");
            for (size_t i = 0; i < 26; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("포켓몬 (안농 이미지 포인터: {}/{})", i + 1, 26));
                m_buildProgressState.Increase();

                srcStream << GetAsmLine("gse@pics Unown, {}", i);
            }
        }

        // data
        for (size_t i = 0; i < 26; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("포켓몬 (안농 이미지: {}/{})", i + 1, 26));
            m_buildProgressState.Increase();

            data.PushImageDataBlock(std::format("GSEditor_Unown_FrontImage_{}", i), m_data.UnownImages()[i].FrontImage);
            data.PushImageDataBlock(std::format("GSEditor_Unown_BackImage_{}", i), m_data.UnownImages()[i].BackImage);
        }
    }

    return !m_buildProgressState.HandlePausedOrCanceled();
}

bool pokegold::Rom::Build_TrainerGroupSources(internal::RomBuildData &data)
{
    constexpr auto filename = "GSEditor.TrainerGroups.asm";
    std::ofstream srcStream(*m_workspacePathState / filename);
    data.GetSourceStream() << GetAsmInclude(filename);

    base::Log(TAG, "write trainer group (color)");
    {
        srcStream << GetAsmSection(0xb511, "GSEditor_TrainerGroup_Colors")
                  << GetAsmLine("GSEditor_TrainerGroup_Colors::");

        for (size_t i = 0, max = 66; i < max; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("트레이너 그룹 (이미지 색상: {}/{})", i + 1, max));
            m_buildProgressState.Increase();

            const auto &e = m_data.TrainerGroups()[i];
            srcStream << GetAsmBytes({
                e.Colors[0].GetLoByte(),
                e.Colors[0].GetHiByte(),
                e.Colors[1].GetLoByte(),
                e.Colors[1].GetHiByte(),
            });
        }
    }

    base::Log(TAG, "write trainer group (image)");
    {
        // ptr
        {
            srcStream << GetAsmSection(0x80000, "GSEditor_TrainerGroup_Image_Pointers");
            for (size_t i = 0, max = 66; i < max; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("트레이너 그룹 (이미지 포인터: {}/{})", i + 1, max));
                m_buildProgressState.Increase();

                srcStream << GetAsmLine("gse@pic TrainerGroup, {}", i);
            }
        }

        // data
        for (size_t i = 0, max = 66; i < max; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("트레이너 그룹 (이미지: {}/{})", i + 1, max));
            m_buildProgressState.Increase();

            data.PushImageDataBlock(std::format("GSEditor_TrainerGroup_Image_{}", i), m_data.TrainerGroups()[i].Image);
        }
    }

    base::Log(TAG, "write trainer group (name)");
    {
        srcStream << GetAsmSection(0x35d5, "GSEditor_TrainerGroup_Names_Pointer")
                  << GetAsmLine("db BANK(GSEditor_TrainerGroup_Names)")
                  << GetAsmLine("dw GSEditor_TrainerGroup_Names");

        data.GetNamesSourceStream() << GetAsmLine("GSEditor_TrainerGroup_Names::");
        for (size_t i = 0; i < 67; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("트레이너 그룹 (이름: {}/{})", i + 1, 67));
            m_buildProgressState.Increase();

            const auto &e = m_data.TrainerGroups()[i];
            data.GetNamesSourceStream() << GetAsmBytes(e.Name.GetData());
        }
    }

    return !m_buildProgressState.HandlePausedOrCanceled();
}

bool pokegold::Rom::Build_TypeSources(internal::RomBuildData &data)
{
    constexpr auto filename = "GSEditor.Types.asm";
    std::ofstream srcStream(*m_workspacePathState / filename);
    data.GetSourceStream() << GetAsmInclude(filename);

    base::Log(TAG, "write type (name)");
    {
        // push data
        for (size_t i = 0; i < 28; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("타입 (이름: {}/{})", i + 1, 28));
            m_buildProgressState.Increase();

            const auto &e = m_data.Types()[i];
            data.GetTypeNameDataBlocks()
                .Push(std::format("GSEditor_Type_Name_{}", i), e.Name.GetData());
        }

        // ptr
        {
            srcStream << GetAsmSection(0x50a57, "GSEditor_Type_Name_Pointers")
                      << GetAsmLine("GSEditor_Type_Name_Pointers::");

            for (size_t i = 0; i < 28; i++)
            {
                if (m_buildProgressState.HandlePausedOrCanceled())
                    return false;

                m_buildProgressState.UpdateMessage(std::format("타입 (이름 포인터: {}/{})", i + 1, 28));
                m_buildProgressState.Increase();

                srcStream << GetAsmLine("dw GSEditor_Type_Name_{}", i);
            }
        }
    }

    base::Log(TAG, "write type (matchups)");
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        m_buildProgressState.UpdateMessage("타입 (상성 데이터)");
        m_buildProgressState.Increase();

        // hack 코드
        {
            // data.GetSourceStream() << GetAsmInclude("GSEditor.Type.Matchups.asm");
            // base::WriteBytesToFile("GSEditor.Type.Matchups.asm", embed::GetPokegoldTypeMatchupsHackingSource());

            const auto &hackAsmFile = embed::GetPokegoldTypeMatchupsHackingSource();
            std::string_view hackAsmStr(reinterpret_cast<const char *>(hackAsmFile.data()), hackAsmFile.size());
            srcStream << hackAsmStr;
        }

        // matchups
        {
            std::vector<std::reference_wrapper<TypeMatchup>> matchups;
            std::vector<std::reference_wrapper<TypeMatchup>> foresights;

            for (size_t i = 0; i < 28; i++)
            {
                for (auto &e : m_data.Types()[i].TypeMatchups)
                {
                    if (e.IsForesight)
                        foresights.push_back(e);
                    else
                        matchups.push_back(e);
                }
            }

            srcStream << GetAsmLine("GSEditor_TypeMatchups:");
            for (const auto &e : matchups)
            {
                srcStream << GetAsmBytes({
                    e.get().AttackerTypeId,
                    e.get().DefenderTypeId,
                    u8(e.get().TypeEffectiveness),
                });
            }
            srcStream << GetAsmBytes({0xfe});

            for (const auto &e : foresights)
            {
                srcStream << GetAsmBytes({
                    e.get().AttackerTypeId,
                    e.get().DefenderTypeId,
                    u8(e.get().TypeEffectiveness),
                });
            }
            srcStream << GetAsmBytes({0xff});
        }

        // weather
        {
            srcStream << GetAsmLine("GSEditor_WeatherTypeModifiers:");
            for (const auto &e : m_data.Types())
            {
                for (const auto &modifier : e.WeatherModifiers)
                {
                    srcStream << GetAsmBytes({
                        u8(modifier.Weather),
                        modifier.TypeId,
                        u8(modifier.TypeEffectiveness),
                    });
                }
            }
            srcStream << GetAsmBytes({0xff});

            srcStream << GetAsmLine("GSEditor_WeatherMoveModifiers:");
            for (const auto &e : m_data.Moves())
            {
                for (const auto &modifier : e.WeatherModifiers)
                {
                    srcStream << GetAsmBytes({
                        u8(modifier.Weather),
                        modifier.MoveId,
                        u8(modifier.TypeEffectiveness),
                    });
                }
            }
            srcStream << GetAsmBytes({0xff});
        }
    }

    return !m_buildProgressState.HandlePausedOrCanceled();
}

bool pokegold::Rom::Build_Assemble(internal::RomBuildData &data)
{
    const auto workdir = *m_workspacePathState;

    // 추가 include
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        m_buildProgressState.UpdateMessage("Add includes...");
        m_buildProgressState.Increase();

        data.GetSourceStream() << GetAsmInclude("GSEditor.Names.asm");
        data.GetSourceStream() << GetAsmInclude("GSEditor.Images.asm");
        data.GetSourceStream() << GetAsmInclude("GSEditor.TypeNames.asm");
    }

    // 이미지 데이터 기록
    {
        auto dataBlocks = data.GetImageDataBlocks().Resolve(k_imageFreeSpaces);
        for (size_t i = 0, max = dataBlocks.size(); i < max; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("이미지 추가 ({}/{})", i + 1, max));
            m_buildProgressState.Increase();

            const auto &dataBlock = dataBlocks[i];
            if (dataBlock.DataBlocks.empty())
                continue;

            data.GetImagesSourceStream()
                << GetAsmSection(dataBlock.FreeSpaceRange.From, "GSEditor_Images_0x{:x}", dataBlock.FreeSpaceRange.From)
                << GetAsmLine("GSEditor_Images_0x{:x}::", dataBlock.FreeSpaceRange.From);

            for (const auto &e : dataBlock.DataBlocks)
            {
                data.GetImagesSourceStream()
                    << GetAsmLine("{}:", e.Label)
                    << GetAsmBytes(e.Data);
            }
        }
    }

    // 타입 이름 데이터 기록
    {
        auto dataBlocks = data.GetTypeNameDataBlocks().Resolve(k_typeNameFreeSpaces);
        for (size_t i = 0, max = dataBlocks.size(); i < max; i++)
        {
            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("타입 이름 추가 ({}/{})", i + 1, max));
            m_buildProgressState.Increase();

            const auto &dataBlock = dataBlocks[i];
            if (dataBlock.DataBlocks.empty())
                continue;

            data.GetTypeNameSourceStream()
                << GetAsmSection(dataBlock.FreeSpaceRange.From, "GSEditor_Type_Name_0x{:x}", dataBlock.FreeSpaceRange.From)
                << GetAsmLine("GSEditor_Type_Name_0x{:x}::", dataBlock.FreeSpaceRange.From);

            for (const auto &e : dataBlock.DataBlocks)
            {
                data.GetTypeNameSourceStream()
                    << GetAsmLine("{}:", e.Label)
                    << GetAsmBytes(e.Data);
            }
        }
    }

    // 파일 스트림 동기화
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        data.GetSourceStream().flush();
        data.GetNamesSourceStream().flush();
        data.GetImagesSourceStream().flush();
        data.GetTypeNameSourceStream().flush();
    }

    // rgbasm
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        m_buildProgressState.UpdateMessage("Assemble...");
        m_buildProgressState.Increase();

        auto args = std::format("-o {} {}", (workdir / "GSEditor.o").string(), (workdir / "GSEditor.asm").string());
        auto result = base::RunRgbasm(args, workdir.string());
        base::Log(TAG, "Build: rgbasm {}", args);
        base::Log(TAG, "Build: \n{}", result.GetOutput());
    }

    // rgblink
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        m_buildProgressState.UpdateMessage("Linking...");
        m_buildProgressState.Increase();

        auto debugLabelOption = m_appConfigs.GetShowDebugLabel()
                                    ? std::format("--map {} --sym {}",
                                                  (workdir / (s_targetName + ".map")).string(),
                                                  (workdir / (s_targetName + ".sym")).string())
                                    : "";

        auto args = std::format(
            "{} -o {} -O {} {}",
            debugLabelOption,
            (workdir / (s_targetName + ".bin")).string(),
            (workdir / (s_baseName + ".bin")).string(),
            (workdir / "GSEditor.o").string());
        auto result = base::RunRgblink(args, workdir.string());
        base::Log(TAG, "Build: rgblink {}", args);
        base::Log(TAG, "Build: \n{}", result.GetOutput());
    }

    // rgbfix
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        m_buildProgressState.UpdateMessage("Rom fixing...");
        m_buildProgressState.Increase();

        auto args = std::format("-v -Wno-overwrite {}", (workdir / (s_targetName + ".bin")).string());
        auto result = base::RunRgbfix(args, workdir.string());
        base::Log(TAG, "Build: rgbfix {}", args);
        base::Log(TAG, "Build: \n{}", result.GetOutput());
    }

    return !m_buildProgressState.HandlePausedOrCanceled();
}
