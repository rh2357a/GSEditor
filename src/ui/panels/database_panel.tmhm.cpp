#include "database_panel.h"

#include "ui/bindings.h"
#include "ui/dialogs/message_box.h"
#include "ui/utils.h"

#include <wx/event.h>
#include <wx/wx.h>

#include <format>

void ui::DatabasePanel::InitializeTmHmTab()
{
    ApplyListSearch(this, {m_tmhmList, m_tmhmMoveComboBox, m_tmhmPokemonList});
    ApplyNestedScrolling({m_tmhmMoveComboBox, m_tmhmPokemonList});

    BindControlSelection(this, m_tmhmList, m_selectedTMHM);

    // 롬을 다시 열었을 때, 선택 초기화...
    m_pokegold.Rom().Opened().Subscribe(this, [this](const bool &) {
        m_selectedTMHM.Update(-1);
    });

    // 기술 목록 갱신
    m_pokegold.Data().MoveNameUpdated().Subscribe(this, [this](const int &idx) {
        m_tmhmMoveComboBox->Freeze();

        if (m_tmhmMoveComboBox->GetCount() == 0)
        {
            for (int i = 0; i < 251; i++)
                m_tmhmMoveComboBox->Append(wxT(""));
        }

        if (idx == -1)
        {
            for (int i = 0; i < 251; i++)
            {
                auto &pokemon = m_pokegold.Data().Moves()[i];
                m_tmhmMoveComboBox->SetString(i, pokemon.Name.ToEditorWxString());
            }
        }
        else
        {
            auto &pokemon = m_pokegold.Data().Moves()[idx];
            m_tmhmMoveComboBox->SetString(idx, pokemon.Name.ToEditorWxString());
        }

        m_tmhmMoveComboBox->Thaw();
    });

    // 포켓몬 목록 갱신
    m_pokegold.Data().PokemonNameUpdated().Subscribe(this, [this](const int &idx) {
        m_tmhmPokemonList->Freeze();

        if (m_tmhmPokemonList->GetCount() == 0)
        {
            for (int i = 0; i < 251; i++)
                m_tmhmPokemonList->Append(wxT(""));
        }

        if (idx == -1)
        {
            for (int i = 0; i < 251; i++)
            {
                auto &pokemon = m_pokegold.Data().Pokemons()[i];
                m_tmhmPokemonList->SetString(i, pokemon.Name.ToEditorWxString());
            }
        }
        else if (idx < 251)
        {
            auto &pokemon = m_pokegold.Data().Pokemons()[idx];
            m_tmhmPokemonList->SetString(idx, pokemon.Name.ToEditorWxString());
        }

        m_tmhmPokemonList->Thaw();
    });

    // 기술머신 표시 및 변경사항 갱신
    m_pokegold.Data().TMHMsUpdated().Subscribe(this, [this] { UpdateTMHMsTab(); });
    m_selectedTMHM.Subscribe(this, [this] {
        UpdateTMHMsTab();
        m_tmhmList->SetFocus();
    });

    // 기술 수정 처리
    m_tmhmMoveComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent &ev) {
        ev.Skip();

        if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
            return;

        auto &e = m_pokegold.Data().TMHMs()[*m_selectedTMHM];
        e.MoveId = m_tmhmMoveComboBox->GetSelection() + 1;

        m_pokegold.Data().TMHMsUpdated()();
        m_pokegold.Rom().NotifyRomChanged();
    });

    // 배울 수 있는 포켓몬 체크 처리
    m_tmhmPokemonList->Bind(wxEVT_CHECKLISTBOX, [this](wxCommandEvent &ev) {
        ev.Skip();

        if (!*m_pokegold.Rom().Opened() || m_eventGuard.IsGuarded())
            return;

        for (u16 i = 0; i < 251; i++)
        {
            auto &pokemon = m_pokegold.Data().Pokemons()[i];
            pokemon.TMHMs[*m_selectedTMHM] = m_tmhmPokemonList->IsChecked(i);
        }

        m_pokegold.Data().TMHMsUpdated()();
        m_pokegold.Rom().NotifyRomChanged();
    });
}

void ui::DatabasePanel::UpdateTMHMsTab()
{
    if (!*m_pokegold.Rom().Opened())
        return;

    // 목록 업데이트
    {
        m_tmhmList->Freeze();

        if (m_tmhmList->GetCount() == 0)
        {
            for (size_t i = 0; i < m_pokegold.Data().TMHMs().size(); i++)
                m_tmhmList->Append(wxT(""));
        }

        for (size_t i = 0; i < m_pokegold.Data().TMHMs().size(); i++)
        {
            auto str = std::format(
                "{}{:02} [{}]",
                i < 50 ? "기술" : "비전",
                i < 50 ? i + 1 : i - 50 + 1,
                m_pokegold.Data().Moves()[m_pokegold.Data().TMHMs()[i].MoveId - 1].Name.ToEditorString());
            m_tmhmList->SetString(i, wxString::FromUTF8(str));
        }

        m_tmhmList->Thaw();
    }

    // 편집 UI 업데이트
    m_eventGuard([&] {
        int idx = *m_selectedTMHM;

        m_tmhmContainer->Enable(idx != -1);

        if (idx == -1)
        {
            m_tmhmMoveComboBox->Select(-1);

            for (unsigned int i = 0; i < m_tmhmPokemonList->GetCount(); i++)
                m_tmhmPokemonList->Check(i, false);
        }
        else
        {
            const int moveId = m_pokegold.Data().TMHMs()[idx].MoveId - 1;
            m_tmhmMoveComboBox->Select(moveId);

            for (unsigned int i = 0; i < m_tmhmPokemonList->GetCount(); i++)
                m_tmhmPokemonList->Check(i, m_pokegold.Data().Pokemons()[i].TMHMs[idx]);
        }
    });
}

void ui::DatabasePanel::OnTMHMsButtonClick(wxCommandEvent &event)
{
    event.Skip();

    if (!*m_pokegold.Rom().Opened() || *m_selectedTMHM == -1)
        return;

    const int id = event.GetId();
    const int selected = *m_selectedTMHM;

    if (id == wxID_CHECK_ALL)
    {
        auto result = ShowYesNoDialog(this, "모두 선택", "모두 선택하면 복구할 수 없습니다.\n계속하시겠습니까?");
        if (result == MessageBoxResult::No)
            return;

        m_eventGuard([&] {
            for (auto &pokemon : m_pokegold.Data().Pokemons())
                pokemon.TMHMs[selected] = true;

            m_pokegold.Data().TMHMsUpdated()();
            m_pokegold.Rom().NotifyRomChanged();
        });
        return;
    }

    if (id == wxID_CLEAR)
    {
        auto result = ShowYesNoDialog(this, "모두 해제", "모두 해제하면 복구할 수 없습니다.\n계속하시겠습니까?");
        if (result == MessageBoxResult::No)
            return;

        m_eventGuard([&] {
            for (auto &pokemon : m_pokegold.Data().Pokemons())
                pokemon.TMHMs[selected] = false;

            m_pokegold.Data().TMHMsUpdated()();
            m_pokegold.Rom().NotifyRomChanged();
        });
        return;
    }
}
