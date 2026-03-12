#include "data.h"

#include "base/files/file_util.h"

pokegold::Data::Data(std::filesystem::path romFilePath)
{
    if (romFilePath != base::GetNullPath())
        m_romBytes = base::ReadBytesFromFile(romFilePath);
}

pokegold::Data &pokegold::Data::operator=(const Data &newData)
{
    m_romBytes = newData.m_romBytes;

    m_items = newData.m_items;
    m_moves = newData.m_moves;
    m_moveEffects = newData.m_moveEffects;
    m_pokemons = newData.m_pokemons;
    m_unownImages = newData.m_unownImages;
    m_trainerGroups = newData.m_trainerGroups;
    m_types = newData.m_types;
    m_tmhms = newData.m_tmhms;

    m_npcColors = newData.m_npcColors;
    m_legacyPokemonSmallPictures = newData.m_legacyPokemonSmallPictures;

    m_badDataList = newData.m_badDataList;

    UnownImageEnabled = newData.UnownImageEnabled;
    UnownPokemonId = newData.UnownPokemonId;

    // 변동 사항 전체 통지
    {
        m_pokemonNameUpdated(-1);
        m_itemNameUpdated(-1);
        m_moveNameUpdated(-1);
        m_typeNameUpdated(-1);
        m_tmhmsUpdated();
        m_trainerGroupUpdated(-1);
    }

    return *this;
};

bool pokegold::Data::MatchBytes(size_t offset, const std::vector<u8> &findBytes)
{
    if (offset + findBytes.size() > m_romBytes.size())
        return false;

    for (size_t j = 0; j < findBytes.size(); j++)
    {
        if (m_romBytes[offset + j] != findBytes[j])
            return false;
    }

    return true;
}

u8 pokegold::Data::GetByte(size_t offset)
{
    return m_romBytes[offset];
}

std::span<const u8> pokegold::Data::GetBytes(size_t offset, size_t length)
{
    if (length == 0 || offset >= m_romBytes.size() || length > m_romBytes.size() - offset)
        return {};
    return std::span<const u8>(m_romBytes.data() + offset, length);
}

std::span<const u8> pokegold::Data::GetBytesUntil(size_t offset, std::function<bool(size_t, u8)> predicate, bool includeEnd)
{
    if (offset >= m_romBytes.size())
        return {};

    size_t i = 0;
    while (offset + i < m_romBytes.size())
    {
        u8 b = m_romBytes[offset + i];
        if (predicate(i, b))
        {
            if (includeEnd)
                i++;
            break;
        }

        i++;
    }

    return std::span<const u8>(m_romBytes.data() + offset, i);
}

void pokegold::Data::SetByte(size_t offset, u8 byte)
{
    m_romBytes[offset] = byte;
}

void pokegold::Data::SetBytes(size_t offset, const std::vector<u8> &bytes)
{
    if (offset >= m_romBytes.size() || bytes.size() > m_romBytes.size() - offset)
        return;

    for (size_t i = 0; i < bytes.size(); i++)
        m_romBytes[offset + i] = bytes[i];
}

void pokegold::Data::FillBytes(u8 byte, size_t offset, size_t length)
{
    if (offset >= m_romBytes.size() || length > m_romBytes.size() - offset)
        return;

    for (size_t i = 0; i < length; i++)
        m_romBytes[offset + i] = byte;
}
