#include "evolution_editor_dialog.h"

#include "services/pokegold/data/game_data.h"
#include "ui/bindings.h"
#include "ui/dialogs/evolution_editor_dialog.h"
#include "ui/utils.h"

#include <wx/string.h>

ui::internal::EvolutionEditorDialog::EvolutionEditorDialog(wxWindow *parent, std::optional<pokegold::EvolutionMethod> defaultValue)
    : EvolutionEditorDialogBase(parent)
{
    ApplyListSearch(this, {m_pokemon, m_tradeItems, m_useItems});

    // 진화 타입 바인딩
    {
        BindRadioButtonValue(this, m_levelUpRadio, m_evolveType, EvolveType::LevelUp);
        BindRadioButtonValue(this, m_useItemRadio, m_evolveType, EvolveType::UseItem);
        BindRadioButtonValue(this, m_tradeRadio, m_evolveType, EvolveType::Trade);

        m_evolveType.Subscribe(this, [this](const EvolveType &type) {
            m_levelUpPanel->Enable(type == EvolveType::LevelUp);
            m_useItemPanel->Enable(type == EvolveType::UseItem);
            m_tradePanel->Enable(type == EvolveType::Trade);
        });
    }

    // 레벨업 진화 타입 바인딩
    {
        BindRadioButtonValue(this, m_levelUpCommonRadio, m_levelUpType, LevelUpType::Common);
        BindRadioButtonValue(this, m_happinessRadio, m_levelUpType, LevelUpType::Happiness);

        m_levelUpType.Subscribe(this, [this](const LevelUpType &type) {
            m_level->Enable(type == LevelUpType::Common);
            m_levelTypeComboBox->Enable(type == LevelUpType::Common);

            m_happinessTypeComboBox->Enable(type == LevelUpType::Happiness);
        });
    }

    // 교환 아이템 바인딩
    {
        BindCheckBoxValue(this, m_tradeGaveItemCheckBox, m_tradeGaveItem);

        m_tradeGaveItem.Subscribe(this, [this](const bool &checked) {
            m_tradeItems->Enable(checked);
        });
    }

    // 필요 데이터 로딩
    {
        m_pokemon->Freeze();
        m_useItems->Freeze();
        m_tradeItems->Freeze();

        for (auto &e : m_pokegold.Data().Pokemons())
        {
            if (e.Type == pokegold::PokemonType::Pokemon)
            {
                const auto name = e.Name.ToEditorWxString();
                m_pokemon->Append(name);
            }
        }

        for (auto &e : m_pokegold.Data().Items())
        {
            const auto name = e.Name.ToEditorWxString();
            m_useItems->Append(name);
            m_tradeItems->Append(name);
        }

        m_pokemon->Thaw();
        m_useItems->Thaw();
        m_tradeItems->Thaw();
    }

    // 값 설정
    {
        m_evolveType.Update(EvolveType::LevelUp);
        m_levelUpType.Update(LevelUpType::Common);
        m_tradeGaveItem.Update(false);
        m_pokemon->Select(0);
        m_useItems->Select(0);
        m_tradeItems->Select(0);
        m_level->SetValue(5);

        if (defaultValue.has_value())
        {
            const auto &e = *defaultValue;
            m_pokemon->Select(e.PokemonId - 1);

            switch (e.EvolutionMethodType)
            {
            case pokegold::EvolutionMethodType::LevelUp:
                m_evolveType.Update(EvolveType::LevelUp);
                m_levelUpType.Update(LevelUpType::Common);
                m_tradeGaveItem.Update(false);
                m_level->SetValue(e.Level);
                m_levelTypeComboBox->Select(0);
                break;

            case pokegold::EvolutionMethodType::UseItem:
                m_evolveType.Update(EvolveType::UseItem);
                m_levelUpType.Update(LevelUpType::Common);
                m_tradeGaveItem.Update(false);
                m_useItems->Select(e.ItemId - 1);
                break;

            case pokegold::EvolutionMethodType::Trade:
                m_evolveType.Update(EvolveType::Trade);
                m_levelUpType.Update(LevelUpType::Common);
                m_tradeGaveItem.Update(e.ItemId != 0xff);
                m_tradeItems->Select(e.ItemId - 1);
                break;

            case pokegold::EvolutionMethodType::LevelUpWithHappiness:
                m_evolveType.Update(EvolveType::LevelUp);
                m_levelUpType.Update(LevelUpType::Happiness);
                m_tradeGaveItem.Update(false);
                m_happinessTypeComboBox->Select(e.Happiness - 1);
                break;

            case pokegold::EvolutionMethodType::LevelUpWithStats:
                m_evolveType.Update(EvolveType::LevelUp);
                m_levelUpType.Update(LevelUpType::Common);
                m_tradeGaveItem.Update(false);
                m_level->SetValue(e.Level);
                m_levelTypeComboBox->Select(e.Stats);
                break;
            }
        }
    }

    wxString title = defaultValue.has_value() ? wxT("진화 수정...") : wxT("진화 추가...");
    SetTitle(title);
}

void ui::internal::EvolutionEditorDialog::OnConfirmButtonClick(wxCommandEvent &event)
{
    pokegold::EvolutionMethod result;
    result.PokemonId = m_pokemon->GetSelection() + 1;

    const auto evolveType = *m_evolveType;
    if (evolveType == EvolveType::LevelUp)
    {
        const auto levelUpType = *m_levelUpType;
        if (levelUpType == LevelUpType::Common)
        {
            const auto stats = m_levelTypeComboBox->GetSelection();
            if (stats == 0)
            {
                result.EvolutionMethodType = pokegold::EvolutionMethodType::LevelUp;
                result.Level = m_level->GetValue();
            }
            else
            {
                result.EvolutionMethodType = pokegold::EvolutionMethodType::LevelUpWithStats;
                result.Level = m_level->GetValue();
                result.Stats = stats;
            }
        }
        else // if (levelUpType == LevelUpType::Happiness)
        {
            result.EvolutionMethodType = pokegold::EvolutionMethodType::LevelUpWithHappiness;
            result.Happiness = m_happinessTypeComboBox->GetSelection() + 1;
        }
    }
    else if (evolveType == EvolveType::UseItem)
    {
        result.EvolutionMethodType = pokegold::EvolutionMethodType::UseItem;
        result.Level = m_level->GetValue();
        result.ItemId = m_useItems->GetSelection() + 1;
    }
    else // if (evolveType == EvolveType::Trade)
    {
        result.EvolutionMethodType = pokegold::EvolutionMethodType::Trade;
        result.Level = m_level->GetValue();
        result.ItemId = *m_tradeGaveItem ? m_tradeItems->GetSelection() + 1 : 0xff;
    }

    m_result = result;
    EndModal(wxID_OK);
}

void ui::internal::EvolutionEditorDialog::OnCancelButtonClick(wxCommandEvent &event)
{
    m_result.reset();
    EndModal(wxID_CANCEL);
}

std::optional<pokegold::EvolutionMethod> ui::ShowEvolutionEditorDialog(wxWindow *parent, std::optional<pokegold::EvolutionMethod> defaultValue)
{
    internal::EvolutionEditorDialog dialog(parent, defaultValue);
    dialog.ShowModal();
    return dialog.GetResult();
}
