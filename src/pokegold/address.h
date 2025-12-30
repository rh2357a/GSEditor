#ifndef _POKEGOLD_ADDRESS_H_
#define _POKEGOLD_ADDRESS_H_

#include <span>

namespace pokegold::addr {

inline size_t calc(u8 bank, u16 addr) { return (bank * 0x4000) | (addr - 0x4000); }
inline size_t calc(std::span<const u8> addr_bytes) { return (addr_bytes[0] * 0x4000) | ((addr_bytes[1] | addr_bytes[2] << 8) - 0x4000); }
inline size_t calc(u8 bank, std::span<const u8> addr_bytes) { return (bank * 0x4000) | ((addr_bytes[0] | addr_bytes[1] << 8) - 0x4000); }

inline size_t calc_from_encoded_bank(std::span<const u8> addr_bytes)
{
    u8 bank;
    switch (addr_bytes[0])
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
        bank = addr_bytes[0];
        break;
    }

    return calc(bank, u16(addr_bytes[1] | addr_bytes[2] << 8));
}

inline u8 calc_bank(size_t addr) { return u8(addr / 0x4000); }
inline u16 calc_pointer(size_t addr) { return u16(addr % 0x4000 + (addr >= 0x4000 ? 0x4000 : 0)); }

} // namespace pokegold::addr

#endif
