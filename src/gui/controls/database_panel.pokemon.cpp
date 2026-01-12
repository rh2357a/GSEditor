#include "database_panel.h"

#include "pokegold.h"
#include "gui.h"
#include "utils.h"

#include <array>
#include <unordered_map>

std::unordered_map<pokegold::data::growth_rate, int> growthRateIndexes{
    {pokegold::data::growth_rate::MEDIUM_FAST, 0},
    {pokegold::data::growth_rate::SLIGHTLY_FAST, 1},
    {pokegold::data::growth_rate::SLIGHTLY_SLOW, 2},
    {pokegold::data::growth_rate::MEDIUM_SLOW, 3},
    {pokegold::data::growth_rate::FAST, 4},
    {pokegold::data::growth_rate::SLOW, 5},
};

std::array<pokegold::data::growth_rate, 6> growthRateReverseIndexes{
    pokegold::data::growth_rate::MEDIUM_FAST,
    pokegold::data::growth_rate::SLIGHTLY_FAST,
    pokegold::data::growth_rate::SLIGHTLY_SLOW,
    pokegold::data::growth_rate::MEDIUM_SLOW,
    pokegold::data::growth_rate::FAST,
    pokegold::data::growth_rate::SLOW,
};

std::unordered_map<pokegold::data::gender_rate, int> genderRateIndexes{
    {pokegold::data::gender_rate::GENDER_0, 0},
    {pokegold::data::gender_rate::GENDER_12_5, 1},
    {pokegold::data::gender_rate::GENDER_25, 2},
    {pokegold::data::gender_rate::GENDER_37_5, 3},
    {pokegold::data::gender_rate::GENDER_50, 4},
    {pokegold::data::gender_rate::GENDER_62_5, 5},
    {pokegold::data::gender_rate::GENDER_75, 6},
    {pokegold::data::gender_rate::GENDER_87_5, 7},
    {pokegold::data::gender_rate::GENDER_100, 8},
    {pokegold::data::gender_rate::UNKNOWN, 9},
};

std::array<pokegold::data::gender_rate, 10> genderRateReverseIndexes{
    pokegold::data::gender_rate::GENDER_0,
    pokegold::data::gender_rate::GENDER_12_5,
    pokegold::data::gender_rate::GENDER_25,
    pokegold::data::gender_rate::GENDER_37_5,
    pokegold::data::gender_rate::GENDER_50,
    pokegold::data::gender_rate::GENDER_62_5,
    pokegold::data::gender_rate::GENDER_75,
    pokegold::data::gender_rate::GENDER_87_5,
    pokegold::data::gender_rate::GENDER_100,
    pokegold::data::gender_rate::UNKNOWN,
};

std::unordered_map<pokegold::data::egg_group, int> eggGroupIndexes{
    {pokegold::data::egg_group::MONSTER, 0},
    {pokegold::data::egg_group::WATER_1, 1},
    {pokegold::data::egg_group::BUG, 2},
    {pokegold::data::egg_group::FLYING, 3},
    {pokegold::data::egg_group::FIELD, 4},
    {pokegold::data::egg_group::FAIRY, 5},
    {pokegold::data::egg_group::PLANT, 6},
    {pokegold::data::egg_group::HUMAN_LIKE, 7},
    {pokegold::data::egg_group::WATER_3, 8},
    {pokegold::data::egg_group::MINERAL, 9},
    {pokegold::data::egg_group::INDETERMINATE, 10},
    {pokegold::data::egg_group::WATER_2, 11},
    {pokegold::data::egg_group::DITTO, 12},
    {pokegold::data::egg_group::DRAGON, 13},
    {pokegold::data::egg_group::NONE, 14},
};

std::array<pokegold::data::egg_group, 15> eggGroupReverseIndexes{
    pokegold::data::egg_group::MONSTER,
    pokegold::data::egg_group::WATER_1,
    pokegold::data::egg_group::BUG,
    pokegold::data::egg_group::FLYING,
    pokegold::data::egg_group::FIELD,
    pokegold::data::egg_group::FAIRY,
    pokegold::data::egg_group::PLANT,
    pokegold::data::egg_group::HUMAN_LIKE,
    pokegold::data::egg_group::WATER_3,
    pokegold::data::egg_group::MINERAL,
    pokegold::data::egg_group::INDETERMINATE,
    pokegold::data::egg_group::WATER_2,
    pokegold::data::egg_group::DITTO,
    pokegold::data::egg_group::DRAGON,
    pokegold::data::egg_group::NONE,
};

void gui::controls::DatabasePanel::InitPokemonTab()
{
    gui::controls::NestedScrolling({
        m_pokemonGenderRateComboBox,
        m_pokemonGrowthRateComboBox,
        m_pokemonType1ComboBox,
        m_pokemonType2ComboBox,
        m_pokemonItem1ComboBox,
        m_pokemonItem2ComboBox,
        m_pokemonEggGroup1ComboBox,
        m_pokemonEggGroup2ComboBox,

        m_pokemonStatsHpValue,
        m_pokemonStatsAtkValue,
        m_pokemonStatsDefValue,
        m_pokemonStatsSpAtkValue,
        m_pokemonStatsSpDefValue,
        m_pokemonStatsSpdValue,
        m_pokemonStatsExpValue,
        m_pokemonStatsCatchRateValue,

        m_pokemonDexHeightValue,
        m_pokemonDexWeightValue,
        m_pokemonDexDescriptionText,

        m_pokemonEvolutionsList,
        m_pokemonLearnMovesList,
    });

    m_subscriptions.subscribe(pokegold::event::rom_changed, [&] {
        m_eventGuard([&] { gui::controls::Select(m_pokemonList, -1); });
    });

    m_subscriptions.subscribe(pokegold::event::pokemon_names_changed, [this](int idx) {
        if (m_pokemonList->GetCount() == 0)
        {
            m_pokemonList->Clear();

            for (size_t i = 0; i < 256; i++)
                m_pokemonList->Append(wxT(""));
        }

        if (idx == -1)
        {
            for (size_t i = 0; i < 256; i++)
            {
                auto &e = pokegold::data::pokemons[i];
                m_pokemonList->SetString(i, e.name.editor_wxstr());
            }
        }
        else
        {
            auto &e = pokegold::data::pokemons[idx];
            m_pokemonList->SetString(idx, e.name.editor_wxstr());
        }
    });

    m_subscriptions.subscribe(pokegold::event::type_names_changed, [this](int idx) {
        if (m_pokemonType1ComboBox->GetCount() == 0)
        {
            m_pokemonType1ComboBox->Clear();
            m_pokemonType2ComboBox->Clear();

            for (size_t i = 0; i < 28; i++)
            {
                m_pokemonType1ComboBox->Append(wxT(""));
                m_pokemonType2ComboBox->Append(wxT(""));
            }
        }

        if (idx == -1)
        {
            for (size_t i = 0; i < 28; i++)
            {
                auto &e = pokegold::data::types[i];
                auto name = e.name.editor_wxstr();
                m_pokemonType1ComboBox->SetString(i, name);
                m_pokemonType2ComboBox->SetString(i, name);
            }
        }
        else
        {
            auto &e = pokegold::data::types[idx];
            auto name = e.name.editor_wxstr();
            m_pokemonType1ComboBox->SetString(idx, name);
            m_pokemonType2ComboBox->SetString(idx, name);
        }
    });

    m_subscriptions.subscribe(pokegold::event::item_names_changed, [this](int idx) {
        if (m_pokemonItem1ComboBox->GetCount() == 0)
        {
            m_pokemonItem1ComboBox->Clear();
            m_pokemonItem2ComboBox->Clear();

            for (size_t i = 0; i < 256 + 1; i++)
            {
                m_pokemonItem1ComboBox->Append(wxT(""));
                m_pokemonItem2ComboBox->Append(wxT(""));
            }
        }

        if (idx == -1)
        {
            m_pokemonItem1ComboBox->SetString(0, wxT("없음"));
            m_pokemonItem2ComboBox->SetString(0, wxT("없음"));

            for (size_t i = 0; i < 256; i++)
            {
                auto &e = pokegold::data::items[i];
                auto name = e.name.editor_wxstr();
                m_pokemonItem1ComboBox->SetString(i + 1, name);
                m_pokemonItem2ComboBox->SetString(i + 1, name);
            }
        }
        else
        {
            auto &e = pokegold::data::items[idx];
            auto name = e.name.editor_wxstr();
            m_pokemonItem1ComboBox->SetString(idx + 1, name);
            m_pokemonItem2ComboBox->SetString(idx + 1, name);
        }
    });

    m_pokemonNameText->Bind(wxEVT_TEXT, [&](const auto &ev) {
        if (m_eventGuard.is_guarded())
            return;

        auto str = m_pokemonNameText->GetValue().utf8_string();
        if (pokegold::string::is_charmap_string(str))
        {
            const auto pokemon = m_pokemonList->GetSelection();
            pokegold::data::pokemons[pokemon].name = str;
            pokegold::event::pokemon_names_changed.emit(pokemon);

            pokegold::romfile::is_changed = true;
            pokegold::event::rom_data_changed.emit();

            debug_log("database", "pokemon name changed (idx={}, name={})", pokemon, str);
        }
    });

    const auto &infoBindFunc = [&](const auto &ev) {
        if (m_eventGuard.is_guarded())
            return;

        auto bindInfo = [&](auto &field, const auto &value) {
            if (value != field)
            {
                field = value;
                return true;
            }
            return false;
        };

        auto &pokemon = pokegold::data::pokemons[m_pokemonList->GetSelection()];
        bool hasChanged = false;
        hasChanged |= bindInfo(pokemon.gender_rate, genderRateReverseIndexes[m_pokemonGenderRateComboBox->GetSelection()]);
        hasChanged |= bindInfo(pokemon.growth_rate, growthRateReverseIndexes[m_pokemonGrowthRateComboBox->GetSelection()]);
        hasChanged |= bindInfo(pokemon.type_1_id, u8(m_pokemonType1ComboBox->GetSelection()));
        hasChanged |= bindInfo(pokemon.type_2_id, u8(m_pokemonType2ComboBox->GetSelection()));
        hasChanged |= bindInfo(pokemon.item_1_id, u8(m_pokemonItem1ComboBox->GetSelection()));
        hasChanged |= bindInfo(pokemon.item_2_id, u8(m_pokemonItem2ComboBox->GetSelection()));
        hasChanged |= bindInfo(pokemon.egg_group_1, eggGroupReverseIndexes[m_pokemonEggGroup1ComboBox->GetSelection()]);
        hasChanged |= bindInfo(pokemon.egg_group_2, eggGroupReverseIndexes[m_pokemonEggGroup2ComboBox->GetSelection()]);

        if (hasChanged)
        {
            pokegold::romfile::is_changed = true;
            pokegold::event::rom_data_changed.emit();
        }
    };

    m_pokemonGenderRateComboBox->Bind(wxEVT_COMBOBOX, infoBindFunc);
    m_pokemonGrowthRateComboBox->Bind(wxEVT_COMBOBOX, infoBindFunc);
    m_pokemonType1ComboBox->Bind(wxEVT_COMBOBOX, infoBindFunc);
    m_pokemonType2ComboBox->Bind(wxEVT_COMBOBOX, infoBindFunc);
    m_pokemonItem1ComboBox->Bind(wxEVT_COMBOBOX, infoBindFunc);
    m_pokemonItem2ComboBox->Bind(wxEVT_COMBOBOX, infoBindFunc);
    m_pokemonEggGroup1ComboBox->Bind(wxEVT_COMBOBOX, infoBindFunc);
    m_pokemonEggGroup2ComboBox->Bind(wxEVT_COMBOBOX, infoBindFunc);

    const auto &statsBindFunc = [&](const auto &ev) {
        const auto catchRatePercentage = wxString::Format("(%.2lf%%)", m_pokemonStatsCatchRateValue->GetValue() / 255.0 * 100.0);
        m_pokemonCatchRatePercentage->SetLabelText(catchRatePercentage);

        if (m_eventGuard.is_guarded())
            return;

        auto bindStats = [&](u8 &field, wxSpinCtrlDouble *ctrl) {
            const auto value = u8(ctrl->GetValue());
            if (field != value)
            {
                field = value;
                return true;
            }
            return false;
        };

        auto &pokemon = pokegold::data::pokemons[m_pokemonList->GetSelection()];
        bool hasChanged = false;
        hasChanged |= bindStats(pokemon.hp, m_pokemonStatsHpValue);
        hasChanged |= bindStats(pokemon.atk, m_pokemonStatsAtkValue);
        hasChanged |= bindStats(pokemon.def, m_pokemonStatsDefValue);
        hasChanged |= bindStats(pokemon.sp_atk, m_pokemonStatsSpAtkValue);
        hasChanged |= bindStats(pokemon.sp_def, m_pokemonStatsSpDefValue);
        hasChanged |= bindStats(pokemon.spd, m_pokemonStatsSpdValue);
        hasChanged |= bindStats(pokemon.base_exp, m_pokemonStatsExpValue);
        hasChanged |= bindStats(pokemon.catch_rate, m_pokemonStatsCatchRateValue);

        if (hasChanged)
        {
            pokegold::romfile::is_changed = true;
            pokegold::event::rom_data_changed.emit();
        }
    };

    m_pokemonStatsHpValue->Bind(wxEVT_SPINCTRLDOUBLE, statsBindFunc);
    m_pokemonStatsAtkValue->Bind(wxEVT_SPINCTRLDOUBLE, statsBindFunc);
    m_pokemonStatsDefValue->Bind(wxEVT_SPINCTRLDOUBLE, statsBindFunc);
    m_pokemonStatsSpAtkValue->Bind(wxEVT_SPINCTRLDOUBLE, statsBindFunc);
    m_pokemonStatsSpDefValue->Bind(wxEVT_SPINCTRLDOUBLE, statsBindFunc);
    m_pokemonStatsSpdValue->Bind(wxEVT_SPINCTRLDOUBLE, statsBindFunc);
    m_pokemonStatsExpValue->Bind(wxEVT_SPINCTRLDOUBLE, statsBindFunc);
    m_pokemonStatsCatchRateValue->Bind(wxEVT_SPINCTRLDOUBLE, statsBindFunc);
}

void gui::controls::DatabasePanel::OnPokemonSelected(wxCommandEvent &event)
{
    const auto selected = m_pokemonList->GetSelection();
    debug_log("database", "pokemon selected (index={})", selected);

    m_eventGuard([&] {
        m_pokemonContainer->Enable(selected != -1);

        if (selected == -1)
        {
            m_pokemonNoText->SetValue(wxT("-"));
            m_pokemonNameText->SetValue(wxT(""));
            gui::controls::Select(m_pokemonGenderRateComboBox, -1);
            gui::controls::Select(m_pokemonGrowthRateComboBox, -1);
            gui::controls::Select(m_pokemonType1ComboBox, -1);
            gui::controls::Select(m_pokemonType2ComboBox, -1);
            gui::controls::Select(m_pokemonItem1ComboBox, -1);
            gui::controls::Select(m_pokemonItem2ComboBox, -1);
            gui::controls::Select(m_pokemonEggGroup1ComboBox, -1);
            gui::controls::Select(m_pokemonEggGroup2ComboBox, -1);

            gui::controls::SetValue(m_pokemonStatsHpValue, 0);
            gui::controls::SetValue(m_pokemonStatsAtkValue, 0);
            gui::controls::SetValue(m_pokemonStatsDefValue, 0);
            gui::controls::SetValue(m_pokemonStatsSpAtkValue, 0);
            gui::controls::SetValue(m_pokemonStatsSpDefValue, 0);
            gui::controls::SetValue(m_pokemonStatsSpdValue, 0);
            gui::controls::SetValue(m_pokemonStatsExpValue, 0);
            gui::controls::SetValue(m_pokemonStatsCatchRateValue, 0);

            // TODO: ...
        }
        else
        {
            auto &e = pokegold::data::pokemons[selected];

            m_pokemonNoText->SetValue(wxString::Format("%d", e.id));
            m_pokemonNameText->SetValue(e.name.editor_wxstr());
            gui::controls::Select(m_pokemonGenderRateComboBox, genderRateIndexes[e.gender_rate]);
            gui::controls::Select(m_pokemonGrowthRateComboBox, growthRateIndexes[e.growth_rate]);
            gui::controls::Select(m_pokemonType1ComboBox, e.type_1_id);
            gui::controls::Select(m_pokemonType2ComboBox, e.type_2_id);
            gui::controls::Select(m_pokemonItem1ComboBox, e.item_1_id);
            gui::controls::Select(m_pokemonItem2ComboBox, e.item_2_id);
            gui::controls::Select(m_pokemonEggGroup1ComboBox, eggGroupIndexes[e.egg_group_1]);
            gui::controls::Select(m_pokemonEggGroup2ComboBox, eggGroupIndexes[e.egg_group_2]);

            gui::controls::SetValue(m_pokemonStatsHpValue, e.hp);
            gui::controls::SetValue(m_pokemonStatsAtkValue, e.atk);
            gui::controls::SetValue(m_pokemonStatsDefValue, e.def);
            gui::controls::SetValue(m_pokemonStatsSpAtkValue, e.sp_atk);
            gui::controls::SetValue(m_pokemonStatsSpDefValue, e.sp_def);
            gui::controls::SetValue(m_pokemonStatsSpdValue, e.spd);
            gui::controls::SetValue(m_pokemonStatsExpValue, e.base_exp);
            gui::controls::SetValue(m_pokemonStatsCatchRateValue, e.catch_rate);

            // TODO: ...
        }
    });
}
