#include "evolution_editor_dialog.h"
#include <unordered_map>

gui::dialogs::EvolutionEditorDialog::EvolutionEditorDialog(wxWindow *parent, std::optional<pokegold::data::evolution_method> defaultValue) : EvolutionEditorDialogBase(parent)
{
    // 상태 연결
    {
        m_evolveType.bind(
            [&](core::state<int> &state) {
                m_levelUpRadio->Bind(wxEVT_RADIOBUTTON, [&](auto &ev) { state = 0; });
                m_useItemRadio->Bind(wxEVT_RADIOBUTTON, [&](auto &ev) { state = 1; });
                m_tradeRadio->Bind(wxEVT_RADIOBUTTON, [&](auto &ev) { state = 2; });
            },
            [&](const int type) {
                m_levelUpRadio->SetValue(type == 0);
                m_useItemRadio->SetValue(type == 1);
                m_tradeRadio->SetValue(type == 2);
            });

        m_levelUpType.bind(
            [&](core::state<int> &state) {
                m_levelUpCommonRadio->Bind(wxEVT_RADIOBUTTON, [&](auto &e) { state = 0; });
                m_happinessRadio->Bind(wxEVT_RADIOBUTTON, [&](auto &e) { state = 1; });
            },
            [&](const int type) {
                m_levelUpCommonRadio->SetValue(type == 0);
                m_happinessRadio->SetValue(type == 1);
            });

        m_tradeGaveItem.bind(
            [&](core::state<bool> &state) {
                m_tradeGaveItemCheckBox->Bind(wxEVT_CHECKBOX, [&](auto &e) { state = m_tradeGaveItemCheckBox->IsChecked(); });
            },
            [&](const bool gaveItem) {
                m_tradeGaveItemCheckBox->SetValue(gaveItem);
            });
    }

    // 값 변경 연결
    {
        m_evolveType.observe([&](const int type) {
            m_levelUpPanel->Enable(type == 0);
            m_useItemPanel->Enable(type == 1);
            m_tradePanel->Enable(type == 2);
        });

        m_levelUpType.observe(
            [&](const int type) {
                m_level->Enable(type == 0);
                m_levelTypeComboBox->Enable(type == 0);

                m_happinessTypeComboBox->Enable(type == 1);
            });
    }

    // 필요 데이터 로딩
    {
        m_pokemon->Freeze();
        m_useItems->Freeze();
        m_tradeItems->Freeze();

        for (auto &e : pokegold::data::pokemons)
        {
            const auto name = e.name.editor_wxstr();
            m_pokemon->Append(name);
        }

        for (auto &e : pokegold::data::items)
        {
            const auto name = e.name.editor_wxstr();
            m_useItems->Append(name);
            m_tradeItems->Append(name);
        }

        m_pokemon->Thaw();
        m_useItems->Thaw();
        m_tradeItems->Thaw();
    }

    // 값 설정
    {
        m_pokemon->Select(0);
        m_useItems->Select(0);
        m_tradeItems->Select(0);
        m_level->SetValue(5);

        if (defaultValue.has_value())
        {
            const auto &e = *defaultValue;
            m_pokemon->Select(e.pokemon_id - 1);

            switch (e.evolution_type)
            {
            case 1:
                m_evolveType = 0;
                m_levelUpType = 0;
                m_tradeGaveItem = false;
                m_level->SetValue(e.level);
                m_levelTypeComboBox->Select(0);
                break;

            case 2:
                m_evolveType = 1;
                m_levelUpType = 0;
                m_tradeGaveItem = false;
                m_useItems->Select(e.item_id - 1);
                break;

            case 3:
                m_evolveType = 2;
                m_levelUpType = 0;
                m_tradeGaveItem = e.item_id != 0xff;
                m_tradeItems->Select(e.item_id - 1);
                break;

            case 4:
                m_evolveType = 0;
                m_levelUpType = 1;
                m_tradeGaveItem = false;
                m_pokemon->Select(e.pokemon_id - 1);
                m_happinessTypeComboBox->Select(e.happiness - 1);
                break;

            case 5:
                m_evolveType = 0;
                m_levelUpType = 0;
                m_tradeGaveItem = false;
                m_level->SetValue(e.level);
                m_levelTypeComboBox->Select(e.stats);
                break;
            }
        }
        else
        {
            m_evolveType = 0;
            m_levelUpType = 0;
            m_tradeGaveItem = false;
        }
    }

    wxString title = defaultValue.has_value() ? wxT("진화 수정...") : wxT("진화 추가...");
    SetTitle(title);
}

void gui::dialogs::EvolutionEditorDialog::OnConfirmButtonClick(wxCommandEvent &event)
{
    // TODO: 추가...

    Close();
}

void gui::dialogs::EvolutionEditorDialog::OnCancelButtonClick(wxCommandEvent &event)
{
    m_result.reset();
    Close();
}

std::optional<pokegold::data::evolution_method> gui::dialogs::ShowEvolutionDialog(wxWindow *parent, std::optional<pokegold::data::evolution_method> defaultValue)
{
    EvolutionEditorDialog dialog(parent, defaultValue);
    dialog.ShowModal();
    return dialog.GetResult();
}
