#include "rom.h"

#include "base/log.h"
#include "base/resources.h"
#include "services/pokegold/utils.h"

#include <filesystem>
#include <format>
#include <string>

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

    const std::vector<std::array<size_t, 2>> k_typeNameFreeSpaces = {
        {0x050a8f, 0x050ae9},
        {0x053b57, 0x053be8},
    };

    const std::vector<std::array<size_t, 2>> k_imageFreeSpaces = {
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
        [this](auto &data) { return Build_CommonSources(data); },
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

    return data.GetTargetRomPath();
}

bool pokegold::Rom::Build_Startup(internal::RomBuildData &data)
{
    base::Log(TAG, "build: copy baserom");
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        m_buildProgressState.UpdateMessage("베이스롬 복사");
        m_buildProgressState.Increase();

        std::filesystem::copy_file(*m_romFilePathState, data.BaseromPath());
    }

    return !m_buildProgressState.HandlePausedOrCanceled();
}

bool pokegold::Rom::Build_CommonSources(internal::RomBuildData &data)
{
    base::Log(TAG, "build: write macro");
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        m_buildProgressState.UpdateMessage("매크로 소스 작성");
        m_buildProgressState.Increase();

        constexpr auto filename = "GSEditor.Macros.asm";
        data.SourceStream() << GetAsmInclude(filename);

        std::ofstream srcStream(data.WorkDir() / filename);
        srcStream.write(reinterpret_cast<const char *>(embed::GetPokegoldMacrosSource().data()), embed::GetPokegoldMacrosSource().size());
    }

    base::Log(TAG, "build: write cleanup");
    {
        if (m_buildProgressState.HandlePausedOrCanceled())
            return false;

        m_buildProgressState.UpdateMessage("롬 정리 소스 작성");
        m_buildProgressState.Increase();

        constexpr auto filename = "GSEditor.Clean.asm";
        data.SourceStream() << GetAsmInclude(filename);

        std::ofstream srcStream(data.WorkDir() / filename);
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

            srcStream << GetAsmSection(freeSpace[0], "GSEditor_Cleanup_TypeNameFreeSpace_0x{:x}", freeSpace[0])
                      << GetAsmLine("ds {}", freeSpace[1] - freeSpace[0] + 1);
        }

        for (size_t current = 0, max = k_imageFreeSpaces.size(); current < max; current++)
        {
            const auto &freeSpace = k_imageFreeSpaces[current];

            if (m_buildProgressState.HandlePausedOrCanceled())
                return false;

            m_buildProgressState.UpdateMessage(std::format("롬 정리 소스 작성 (이미지: {}/{})", current + 1, max));
            m_buildProgressState.Increase();

            srcStream << GetAsmSection(freeSpace[0], "GSEditor_Cleanup_ImageFreeSpace_0x{:x}", freeSpace[0])
                      << GetAsmLine("ds {}", freeSpace[1] - freeSpace[0] + 1);
        }
    }

    return !m_buildProgressState.HandlePausedOrCanceled();
}

bool pokegold::Rom::Build_ItemSources(internal::RomBuildData &data)
{
    constexpr auto filename = "GSEditor.Pokegold.Items.asm";
    std::ofstream srcStream(data.WorkDir() / filename);
    data.SourceStream() << GetAsmInclude(filename);

    return !m_buildProgressState.HandlePausedOrCanceled();
}

bool pokegold::Rom::Build_MoveSources(internal::RomBuildData &data)
{
    constexpr auto filename = "GSEditor.Pokegold.Moves.asm";
    std::ofstream srcStream(data.WorkDir() / filename);
    data.SourceStream() << GetAsmInclude(filename);

    return !m_buildProgressState.HandlePausedOrCanceled();
}

bool pokegold::Rom::Build_PokemonSources(internal::RomBuildData &data)
{
    constexpr auto filename = "GSEditor.Pokegold.Pokemons.asm";
    std::ofstream srcStream(data.WorkDir() / filename);
    data.SourceStream() << GetAsmInclude(filename);

    return !m_buildProgressState.HandlePausedOrCanceled();
}

bool pokegold::Rom::Build_TrainerGroupSources(internal::RomBuildData &data)
{
    constexpr auto filename = "GSEditor.Pokegold.TrainerGroups.asm";
    std::ofstream srcStream(data.WorkDir() / filename);
    data.SourceStream() << GetAsmInclude(filename);

    return !m_buildProgressState.HandlePausedOrCanceled();
}

bool pokegold::Rom::Build_TypeSources(internal::RomBuildData &data)
{
    constexpr auto filename = "GSEditor.Pokegold.Types.asm";
    std::ofstream srcStream(data.WorkDir() / filename);
    data.SourceStream() << GetAsmInclude(filename);

    return !m_buildProgressState.HandlePausedOrCanceled();
}
