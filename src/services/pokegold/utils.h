#pragma once

#include "base/types/types.h"
#include "utils/free_space.h"

#include <lzcomp/lzcomp.h>

#include <filesystem>
#include <format>
#include <fstream>
#include <span>
#include <sstream>
#include <string>
#include <vector>

namespace pokegold
{
    size_t Calc(u8 bank, u16 addr);
    size_t Calc(std::span<const u8> addrBytes);
    size_t Calc(u8 bank, std::span<const u8> addrBytes);

    size_t CalcFromEncodedBank(std::span<const u8> addrBytes);

    u8 CalcBank(size_t addr);
    u16 CalcPointer(size_t addr);
}

namespace pokegold
{
    template <typename... _Args>
    inline std::string GetAsmSection(size_t offset, std::format_string<_Args...> fmt, _Args &&...args)
    {
        u8 bank = offset / 0x4000;
        u16 ptr = offset % 0x4000 + (offset >= 0x4000 ? 0x4000 : 0);
        std::string name = std::format(fmt, std::forward<_Args>(args)...);
        return bank == 0
                   ? std::format("SECTION \"{}\", ROM0[{}]\n", name, ptr)
                   : std::format("SECTION \"{}\", ROMX[{}], BANK[{}]\n", name, ptr, bank);
    }

    template <typename... _Args>
    inline std::string GetAsmLine(std::format_string<_Args...> fmt, _Args &&...args)
    {
        return std::format(fmt, std::forward<_Args>(args)...) + '\n';
    }

    inline std::string GetAsmInclude(const std::string &path)
    {
        return std::format("INCLUDE \"{}\"\n", path);
    }

    inline std::string GetAsmBytes(std::span<const u8> bytes)
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

    inline std::string GetAsmBytes(std::initializer_list<u8> il)
    {
        return GetAsmBytes(std::span<const u8>(il.begin(), il.end()));
    }
}

namespace pokegold::internal
{
    class RomBuildData
    {
    private:
        std::ofstream m_source;
        std::ofstream m_namesSource;
        std::ofstream m_imagesSource;
        std::ofstream m_typeNamesSource;

        std::vector<u8> m_lzcompBuffer = std::vector<u8>(0x400);

        FreeSpaceDataResolver m_imageDataBlocks;
        FreeSpaceDataResolver m_typeNameDataBlocks;

        size_t m_playerBackImageSize = 0;

    public:
        RomBuildData(const std::filesystem::path &workdir)
            : m_source(workdir / "GSEditor.asm"),
              m_namesSource(workdir / "GSEditor.Names.asm"),
              m_imagesSource(workdir / "GSEditor.Images.asm"),
              m_typeNamesSource(workdir / "GSEditor.TypeNames.asm") {}

    public:
        auto &GetSourceStream() { return m_source; }
        auto &GetNamesSourceStream() { return m_namesSource; }
        auto &GetImagesSourceStream() { return m_imagesSource; }
        auto &GetTypeNameSourceStream() { return m_typeNamesSource; }

        auto &GetImageDataBlocks() { return m_imageDataBlocks; }
        auto &GetTypeNameDataBlocks() { return m_typeNameDataBlocks; }

        void PushImageDataBlock(std::string label, std::span<const u8> data)
        {
            size_t lzSize = lzcomp::Compress(m_lzcompBuffer, data);
            m_imageDataBlocks.Push(label, {m_lzcompBuffer.begin(), m_lzcompBuffer.begin() + lzSize});
        }

        void PushPlayerBackImageDataBlock(std::string label, std::span<const u8> playerData, std::span<const u8> dudeData)
        {
            size_t lzSize = lzcomp::Compress(m_lzcompBuffer, playerData);
            std::vector<u8> tempPlayerData(m_lzcompBuffer.begin(), m_lzcompBuffer.begin() + lzSize);
            m_playerBackImageSize = lzSize;

            lzSize = lzcomp::Compress(m_lzcompBuffer, dudeData);
            std::vector<u8> tempDudeData(m_lzcompBuffer.begin(), m_lzcompBuffer.begin() + lzSize);
            tempPlayerData.insert(tempPlayerData.end(), tempDudeData.begin(), tempDudeData.end());

            m_imageDataBlocks.Push(label, tempPlayerData);
        }

        size_t GetPlayerBackImageSize() const
        {
            return m_playerBackImageSize;
        }
    };
}
