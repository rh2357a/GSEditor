#include "database_panel.h"

#include "pokegold.h"
#include "utils.h"

gui::controls::DatabasePanel::DatabasePanel(
    wxWindow *parent,
    wxWindowID id,
    const wxPoint &pos,
    const wxSize &size,
    long style,
    const wxString &name) : DatabasePanelBase(parent, id, pos, size, style, name)
{
    m_subscriptions.subscribe(pokegold::event::pokemon_changed, [this] {
        // 초기 상태 구성
        if (m_pokemonList->GetCount() == 0)
        {
            m_pokemonList->Clear();

            for (size_t i = 0; i < 256; i++)
                m_pokemonList->Append(wxT(""));
        }

        for (size_t i = 0; i < 256; i++)
        {
            auto &e = pokegold::data::pokemons[i];
            auto name = utils::strings::replace_all(e.name.u8string(), "[50]", "");
            m_pokemonList->SetString(i, wxString::FromUTF8(name));
        }
    });
}

void gui::controls::DatabasePanel::OnPokemonSelected(wxCommandEvent &event)
{
}
