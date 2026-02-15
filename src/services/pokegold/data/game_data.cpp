#include "game_data.h"

bool pokegold::EvolutionMethod::operator==(const EvolutionMethod &rhs) const
{
    if (EvolutionMethodType == EvolutionMethodType::LevelUp)
    {
        return EvolutionMethodType == rhs.EvolutionMethodType
               && PokemonId == rhs.PokemonId
               && Level == rhs.Level;
    }
    else if (EvolutionMethodType == EvolutionMethodType::UseItem || EvolutionMethodType == EvolutionMethodType::Trade)
    {
        return EvolutionMethodType == rhs.EvolutionMethodType
               && PokemonId == rhs.PokemonId
               && ItemId == rhs.ItemId;
    }
    else if (EvolutionMethodType == EvolutionMethodType::LevelUpWithHappiness)
    {
        return EvolutionMethodType == rhs.EvolutionMethodType
               && PokemonId == rhs.PokemonId
               && Happiness == rhs.Happiness;
    }
    else if (EvolutionMethodType == EvolutionMethodType::LevelUpWithStats)
    {
        return EvolutionMethodType == rhs.EvolutionMethodType
               && PokemonId == rhs.PokemonId
               && Level == rhs.Level
               && Stats == rhs.Stats;
    }

    return false;
}
