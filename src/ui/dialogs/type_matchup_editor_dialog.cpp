#include "type_matchup_editor_dialog.h"

#include "services/pokegold/data/game_data.h"

#include <wx/wx.h>

ui::internal::TypeMatchupEditorDialog::TypeMatchupEditorDialog(wxWindow *parent, std::optional<pokegold::TypeMatchup> defaultValue)
    : TypeMatchupEditorDialogBase(parent)
{
    // 필요 데이터 로딩
    {
        m_typeComboBox->Freeze();

        for (auto &e : m_pokegold.Data().Types())
        {
            const auto name = e.Name.ToEditorWxString();
            m_typeComboBox->Append(name);
        }

        m_typeComboBox->Thaw();
    }

    if (defaultValue.has_value())
    {
        m_typeComboBox->Select((*defaultValue).DefenderTypeId);

        if ((*defaultValue).TypeEffectiveness == pokegold::TypeEffectiveness::NoEffect)
            m_effectivenessComboBox->Select(2);
        else if ((*defaultValue).TypeEffectiveness == pokegold::TypeEffectiveness::NotVeryEffective)
            m_effectivenessComboBox->Select(0);
        else if ((*defaultValue).TypeEffectiveness == pokegold::TypeEffectiveness::SuperEffective)
            m_effectivenessComboBox->Select(1);

        m_foresightCheckBox->SetValue((*defaultValue).IsForesight);

        SetTitle(wxT("수정..."));
    }
    else
    {
        m_typeComboBox->Select(0);
        m_effectivenessComboBox->Select(0);
        m_foresightCheckBox->SetValue(false);

        SetTitle(wxT("추가..."));
    }
}

void ui::internal::TypeMatchupEditorDialog::OnConfirmButtonClick(wxCommandEvent &event)
{
    pokegold::TypeMatchup result;
    result.DefenderTypeId = m_typeComboBox->GetSelection();
    result.IsForesight = m_foresightCheckBox->IsChecked();

    if (m_effectivenessComboBox->GetSelection() == 0)
        result.TypeEffectiveness = pokegold::TypeEffectiveness::NotVeryEffective;
    else if (m_effectivenessComboBox->GetSelection() == 1)
        result.TypeEffectiveness = pokegold::TypeEffectiveness::SuperEffective;
    else if (m_effectivenessComboBox->GetSelection() == 2)
        result.TypeEffectiveness = pokegold::TypeEffectiveness::NoEffect;

    Result = result;

    EndModal(wxID_OK);
}

void ui::internal::TypeMatchupEditorDialog::OnCancelButtonClick(wxCommandEvent &event)
{
    Result.reset();

    EndModal(wxID_CANCEL);
}

std::optional<pokegold::TypeMatchup> ui::ShowTypeMatchupEditorDialog(wxWindow *parent, std::optional<pokegold::TypeMatchup> defaultValue)
{
    internal::TypeMatchupEditorDialog dialog(parent, defaultValue);
    dialog.ShowModal();
    return dialog.Result;
}
