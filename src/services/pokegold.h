#pragma once

#include "services/pokegold/data.h"
#include "services/pokegold/rom.h"

namespace services
{
    class Pokegold
    {
    private:
        pokegold::Data m_data;
        pokegold::Rom m_rom = pokegold::Rom(m_data);

    public:
        static Pokegold &Default()
        {
            static Pokegold instance;
            return instance;
        }

        auto &Data() { return m_data; }
        auto &Rom() { return m_rom; }
    };
}
