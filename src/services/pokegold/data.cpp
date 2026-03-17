#include "data.h"

#include "base/files/file_util.h"

pokegold::Data::Data(std::filesystem::path romFilePath)
{
    if (romFilePath != base::NullPath)
        m_romBytes = base::ReadBytesFromFile(romFilePath);
}

pokegold::Data &pokegold::Data::operator=(const Data &newData)
{
    m_romBytes = newData.m_romBytes;

    Items = newData.Items;
    Moves = newData.Moves;
    MoveEffects = newData.MoveEffects;
    Pokemons = newData.Pokemons;
    UnownImages = newData.UnownImages;
    TrainerGroups = newData.TrainerGroups;
    Types = newData.Types;
    TMHMs = newData.TMHMs;

    Maps = newData.Maps;

    BadDataList = newData.BadDataList;

    UnownImageEnabled = newData.UnownImageEnabled;
    UnownPokemonId = newData.UnownPokemonId;

    // 변동 사항 전체 통지
    {
        PokemonNameUpdated(-1);
        ItemNameUpdated(-1);
        MoveNameUpdated(-1);
        TypeNameUpdated(-1);
        TMHMsUpdated();
        TrainerGroupUpdated(-1);
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
