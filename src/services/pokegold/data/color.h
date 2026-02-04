#pragma once

#include "base/types/types.h"
#include <span>

namespace pokegold
{
    class Color
    {
    private:
        u8 m_hiByte, m_loByte;

#ifdef DEBUG
        u16 m_debugR, m_debugG, m_debugB;
#endif

    public:
        Color() = default;
        ~Color() = default;

        Color(std::span<const u8> b);
        Color(u8 r, u8 g, u8 b);

#ifdef DEBUG
    private:
        void UpdateDebugInfo()
        {
            m_debugR = static_cast<u16>(R());
            m_debugG = static_cast<u16>(G());
            m_debugB = static_cast<u16>(B());
        }
#endif

    public:
        u16 Value() const { return (u16(m_hiByte) << 8) | m_loByte; }

        u8 GetHiByte() const { return m_hiByte; }
        u8 GetLoByte() const { return m_loByte; }

        u8 R() const;
        void R(u8 val);

        u8 G() const;
        void G(u8 val);

        u8 B() const;
        void B(u8 val);
    };
}
