#include "move_editor_dialog.h"

#include "ui/utils.h"

#include <wx/colour.h>

#include <optional>

ui::internal::MoveEditorDialog::MoveEditorDialog(wxWindow *parent, std::optional<pokegold::PokemonMove> defaultValue, bool hasLevel) : MoveEditorDialogBase(parent)
{
    ApplyListSearch(this, {m_movesComboBox});

    // 기술 목록 로딩
    {
        m_movesComboBox->Freeze();

        for (auto &e : m_pokegold.Data.Moves)
        {
            const auto name = e.Name.ToEditorWxString();
            m_movesComboBox->Append(name);
        }

        m_movesComboBox->Thaw();
    }

    if (defaultValue.has_value())
    {
        SetTitle(wxT("수정..."));

        m_levelSpinCtrl->SetValue(defaultValue->Level);
        m_movesComboBox->Select(defaultValue->MoveId - 1);
    }
    else
    {
        SetTitle(wxT("추가..."));

        m_levelSpinCtrl->SetValue(1);
        m_movesComboBox->Select(0);
    }

    if (!hasLevel)
    {
        m_contentGrid->Detach(m_levelLabel);
        m_contentGrid->Detach(m_levelSpinCtrl);

        m_levelLabel->Destroy();
        m_levelLabel = nullptr;

        m_levelSpinCtrl->Destroy();
        m_levelSpinCtrl = nullptr;

        auto size = GetSize();
        size.SetHeight(132);
        SetSize(size);
    }
}

void ui::internal::MoveEditorDialog::OnConfirmButtonClick(wxCommandEvent &event)
{
    pokegold::PokemonMove result;

    if (m_levelSpinCtrl != nullptr)
        result.Level = m_levelSpinCtrl->GetValue();

    result.MoveId = m_movesComboBox->GetSelection() + 1;

    m_result = result;

    EndModal(wxID_OK);
}

void ui::internal::MoveEditorDialog::OnCancelButtonClick(wxCommandEvent &event)
{
    m_result.reset();
    EndModal(wxID_CANCEL);
}

std::optional<pokegold::PokemonMove> ui::ShowMoveEditorDialog(wxWindow *parent, std::optional<pokegold::PokemonMove> defaultValue)
{
    internal::MoveEditorDialog dialog(parent, defaultValue, true);
    dialog.ShowModal();
    return dialog.GetResult();
}

std::optional<u8> ui::ShowNoLevelMoveEditorDialog(wxWindow *parent, std::optional<u8> defaultValue)
{
    std::optional<pokegold::PokemonMove> dv;
    if (defaultValue.has_value())
        dv = {.Level = 0, .MoveId = *defaultValue};
    else
        dv = std::nullopt;

    internal::MoveEditorDialog dialog(parent, dv, false);
    dialog.ShowModal();

    if (dialog.GetResult().has_value())
        return dialog.GetResult()->MoveId;

    return std::nullopt;
}
