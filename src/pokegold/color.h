#ifndef _POKEGOLD_COLOR_H_
#define _POKEGOLD_COLOR_H_

#include "pokegold/bytes.h"
#include <cstdint>

namespace pokegold {

class color
{
public:
    static const color BLACK, WHITE;

private:
    uint8_t m_hi_byte, m_lo_byte;

#ifdef DEBUG
    uint16_t m_cached_r, m_cached_g, m_cached_b;
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

    color(uint8_t r, uint8_t g, uint8_t b)
    {
        uint16_t r16 = static_cast<uint16_t>(r / 8);
        uint16_t g16 = static_cast<uint16_t>(g / 8 << 5);
        uint16_t b16 = static_cast<uint16_t>(b / 8 << 10);
        uint16_t value = r16 | g16 | b16;
        m_hi_byte = static_cast<uint8_t>((value & 0xff00) >> 8);
        m_lo_byte = static_cast<uint8_t>(value & 0x00ff);

#ifdef DEBUG
        debug_cache();
#endif
    }

#ifdef DEBUG
private:
    void debug_cache()
    {
        m_cached_r = static_cast<uint16_t>(r());
        m_cached_g = static_cast<uint16_t>(g());
        m_cached_b = static_cast<uint16_t>(b());
    }
#endif

public:
    uint16_t value() const { return (uint16_t(m_hi_byte) << 8) | m_lo_byte; }

    uint8_t r() const { return static_cast<uint8_t>((value() & 0x1f) << 3); }
    void r(uint8_t val)
    {
        uint16_t v = value();
        v &= ~uint16_t(0x1f);
        v |= (uint16_t(val >> 3) & 0x1f);
        m_hi_byte = v >> 8;
        m_lo_byte = v & 0xff;

#ifdef DEBUG
        debug_cache();
#endif
    }

    uint8_t g() const { return static_cast<uint8_t>(((value() >> 5) & 0x1f) << 3); }
    void g(uint8_t val)
    {
        uint16_t v = value();
        v &= ~uint16_t(0x1f << 5);
        v |= (uint16_t(val >> 3) & 0x1f) << 5;
        m_hi_byte = v >> 8;
        m_lo_byte = v & 0xff;

#ifdef DEBUG
        debug_cache();
#endif
    }

    uint8_t b() const { return static_cast<uint8_t>(((value() >> 10) & 0x1f) << 3); }
    void b(uint8_t val)
    {
        uint16_t v = value();
        v &= ~uint16_t(0x1f << 10);
        v |= (uint16_t(val >> 3) & 0x1f) << 10;
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
