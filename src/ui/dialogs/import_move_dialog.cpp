#include "import_move_dialog.h"

#include "ui/bindings.h"
#include "ui/utils.h"

ui::internal::ImportMoveDialog::ImportMoveDialog(wxWindow *parent) : ImportMoveDialogBase(parent)
{
    BindControlSelection(this, m_pokemonListBox, m_selectedPokemon);
    BindControlSelection(this, m_movesListCtrl, m_selectedMove);

    // 포켓몬 목록 로딩
    {
        m_pokemonListBox->Freeze();

        for (auto &e : m_pokegold.Data().Pokemons())
        {
            if (e.Type == pokegold::PokemonType::Pokemon || e.Type == pokegold::PokemonType::Unown)
            {
                const auto name = e.Name.ToEditorWxString();
                m_pokemonListBox->Append(name);
            }
        }

        m_pokemonListBox->Thaw();
    }

    m_movesListCtrl->AppendColumn(wxT("레벨"));
    m_movesListCtrl->AppendColumn(wxT("기술"));
    ApplyListCtrlFixedHeader(m_movesListCtrl);
    AutoListCtrlColumnWidth(m_movesListCtrl);

    m_selectedMove.Subscribe(this, [this](const int &idx) {
        m_ignoreButton->Enable(idx != -1);
    });

    m_selectedPokemon.Subscribe(this, [this](const int &idx) {
        m_selectedMove.Update(-1);

        if (idx != -1)
        {
            m_movesListCtrl->DeleteAllItems();

            auto &moves = m_pokegold.Data().Pokemons()[idx].Moves;

            Result.clear();
            Result.insert(Result.begin(), moves.begin(), moves.end());

            for (int i = 0; i < int(moves.size()); i++)
            {
                const auto &e = moves[i];
                m_movesListCtrl->InsertItem(i, wxT(""));
                m_movesListCtrl->SetItem(i, 0, wxString::Format("%d", e.Level));
                m_movesListCtrl->SetItem(i, 1, m_pokegold.Data().Moves()[e.MoveId - 1].Name.ToEditorWxString());
            }

            AutoListCtrlColumnWidth(m_movesListCtrl);
        }
    });
}

void ui::internal::ImportMoveDialog::OnConfirmButtonClick(wxCommandEvent &event)
{
    EndModal(wxID_OK);
}

void ui::internal::ImportMoveDialog::OnCancelButtonClick(wxCommandEvent &event)
{
    Result.clear();
    EndModal(wxID_CANCEL);
}

void ui::internal::ImportMoveDialog::OnIgnoreButtonClick(wxCommandEvent &event)
{
    int selectedMoveIdx = *m_selectedMove;
    if (selectedMoveIdx != -1)
    {
        Result.erase(Result.begin() + selectedMoveIdx);
        m_movesListCtrl->DeleteItem(selectedMoveIdx);
        m_selectedMove.Update(-1);
    }
}

std::vector<pokegold::PokemonMove> ui::ShowImportMoveDialog(wxWindow *parent)
{
    internal::ImportMoveDialog dialog(parent);
    dialog.ShowModal();
    return dialog.Result;
}
