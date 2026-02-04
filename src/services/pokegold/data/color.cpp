#include "color.h"

pokegold::Color::Color(std::span<const u8> b) : m_hiByte(b[1]), m_loByte(b[0])
{
#ifdef DEBUG
    UpdateDebugInfo();
#endif
}

pokegold::Color::Color(u8 r, u8 g, u8 b)
{
    u16 r16 = static_cast<u16>(r / 8);
    u16 g16 = static_cast<u16>(g / 8 << 5);
    u16 b16 = static_cast<u16>(b / 8 << 10);
    u16 value = r16 | g16 | b16;
    m_hiByte = static_cast<u8>((value & 0xff00) >> 8);
    m_loByte = static_cast<u8>(value & 0x00ff);

#ifdef DEBUG
    UpdateDebugInfo();
#endif
}

u8 pokegold::Color::R() const
{
    return static_cast<u8>((Value() & 0x1f) << 3);
}

void pokegold::Color::R(u8 val)
{
    u16 v = Value();
    v &= ~u16(0x1f);
    v |= (u16(val >> 3) & 0x1f);
    m_hiByte = v >> 8;
    m_loByte = v & 0xff;

#ifdef DEBUG
    UpdateDebugInfo();
#endif
}

u8 pokegold::Color::G() const
{
    return static_cast<u8>(((Value() >> 5) & 0x1f) << 3);
}

void pokegold::Color::G(u8 val)
{
    u16 v = Value();
    v &= ~u16(0x1f << 5);
    v |= (u16(val >> 3) & 0x1f) << 5;
    m_hiByte = v >> 8;
    m_loByte = v & 0xff;

#ifdef DEBUG
    UpdateDebugInfo();
#endif
}

u8 pokegold::Color::B() const
{
    return static_cast<u8>(((Value() >> 10) & 0x1f) << 3);
}

void pokegold::Color::B(u8 val)
{
    u16 v = Value();
    v &= ~u16(0x1f << 10);
    v |= (u16(val >> 3) & 0x1f) << 10;
    m_hiByte = v >> 8;
    m_loByte = v & 0xff;

#ifdef DEBUG
    UpdateDebugInfo();
#endif
}
