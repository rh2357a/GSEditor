#ifndef _POKEGOLD_COLOR_H_
#define _POKEGOLD_COLOR_H_

#include "pokegold/bytes.h"

namespace pokegold {

class color
{
public:
    static const color BLACK, WHITE;

private:
    u8 m_hi_byte, m_lo_byte;

#ifdef DEBUG
    u16 m_cached_r, m_cached_g, m_cached_b;
#endif

public:
    color() = default;
    ~color() = default;

    color(bytes b) : m_hi_byte(b[1]), m_lo_byte(b[0])
    {
#ifdef DEBUG
        debug_cache();
#endif
    };

    color(u8 r, u8 g, u8 b)
    {
        u16 r16 = static_cast<u16>(r / 8);
        u16 g16 = static_cast<u16>(g / 8 << 5);
        u16 b16 = static_cast<u16>(b / 8 << 10);
        u16 value = r16 | g16 | b16;
        m_hi_byte = static_cast<u8>((value & 0xff00) >> 8);
        m_lo_byte = static_cast<u8>(value & 0x00ff);

#ifdef DEBUG
        debug_cache();
#endif
    }

#ifdef DEBUG
private:
    void debug_cache()
    {
        m_cached_r = static_cast<u16>(r());
        m_cached_g = static_cast<u16>(g());
        m_cached_b = static_cast<u16>(b());
    }
#endif

public:
    u16 value() const { return (u16(m_hi_byte) << 8) | m_lo_byte; }

    u8 r() const { return static_cast<u8>((value() & 0x1f) << 3); }
    void r(u8 val)
    {
        u16 v = value();
        v &= ~u16(0x1f);
        v |= (u16(val >> 3) & 0x1f);
        m_hi_byte = v >> 8;
        m_lo_byte = v & 0xff;

#ifdef DEBUG
        debug_cache();
#endif
    }

    u8 g() const { return static_cast<u8>(((value() >> 5) & 0x1f) << 3); }
    void g(u8 val)
    {
        u16 v = value();
        v &= ~u16(0x1f << 5);
        v |= (u16(val >> 3) & 0x1f) << 5;
        m_hi_byte = v >> 8;
        m_lo_byte = v & 0xff;

#ifdef DEBUG
        debug_cache();
#endif
    }

    u8 b() const { return static_cast<u8>(((value() >> 10) & 0x1f) << 3); }
    void b(u8 val)
    {
        u16 v = value();
        v &= ~u16(0x1f << 10);
        v |= (u16(val >> 3) & 0x1f) << 10;
        m_hi_byte = v >> 8;
        m_lo_byte = v & 0xff;

#ifdef DEBUG
        debug_cache();
#endif
    }

    bytes to_bytes() { return {m_lo_byte, m_hi_byte}; }
};

inline const color color::BLACK = color(0, 0, 0);
inline const color color::WHITE = color(255, 255, 255);

} // namespace pokegold

#endif
