#include "utils.h"

size_t pokegold::Calc(u8 bank, u16 addr)
{
    return (bank * 0x4000) | (addr - 0x4000);
}

size_t pokegold::Calc(std::span<const u8> addrBytes)
{
    return (addrBytes[0] * 0x4000) | ((addrBytes[1] | addrBytes[2] << 8) - 0x4000);
}

size_t pokegold::Calc(u8 bank, std::span<const u8> addrBytes)
{
    return (bank * 0x4000) | ((addrBytes[0] | addrBytes[1] << 8) - 0x4000);
}

size_t pokegold::CalcFromEncodedBank(std::span<const u8> addrBytes)
{
    u8 bank;
    switch (addrBytes[0])
    {
    case 0x13:
        bank = 0x1f;
        break;
    case 0x14:
        bank = 0x20;
        break;
    case 0x1f:
        bank = 0x2e;
        break;
    default:
        bank = addrBytes[0];
        break;
    }

    return Calc(bank, u16(addrBytes[1] | addrBytes[2] << 8));
}

u8 pokegold::CalcBank(size_t addr)
{
    return u8(addr / 0x4000);
}

u16 pokegold::CalcPointer(size_t addr)
{
    return u16(addr % 0x4000 + (addr >= 0x4000 ? 0x4000 : 0));
}
