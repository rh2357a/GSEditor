#pragma once

#include "base/types/types.h"

#include <format>
#include <span>
#include <sstream>
#include <string>

namespace pokegold
{
    /// @brief 주소 계산
    /// @param bank 뱅크
    /// @param addr 포인터
    /// @return 주소
    size_t Calc(u8 bank, u16 addr);

    /// @brief 주소 계산
    /// @param addrBytes 뱅크, 포인터 3바이트 배열
    /// @return 주소
    size_t Calc(std::span<const u8> addrBytes);

    /// @brief 주소 계산
    /// @param bank 뱅크
    /// @param addrBytes 포인터 2바이트 배열
    /// @return 주소
    size_t Calc(u8 bank, std::span<const u8> addrBytes);

    /// @brief 주소 계산
    /// @param addrBytes 인코딩된 뱅크, 포인터 3바이트 배열
    /// @return
    size_t CalcFromEncodedBank(std::span<const u8> addrBytes);

    /// @brief 뱅크 계산
    /// @param addr 주소
    /// @return 뱅크
    u8 CalcBank(size_t addr);

    /// @brief 포인터 계산
    /// @param addr 주소
    /// @return 포인터
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
