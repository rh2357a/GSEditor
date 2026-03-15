#pragma once

#include "base/functional/guard.h"
#include "base/functional/state.h"
#include "services/pokegold.h"
#include "ui/ui.h"

namespace ui
{
    class DatabasePanel : public DatabasePanelBase
    {
    private:
        inline static const auto TAG = "ui::DatabasePanel";

        services::Pokegold &m_pokegold = services::Pokegold::Default();

        base::Guard m_eventGuard;

        base::MutableState<int> m_selectedPokemon = -1;
        base::MutableState<int> m_selectedPokemonEvolution = -1;
        base::MutableState<int> m_selectedPokemonMove = -1;
        base::MutableState<int> m_selectedPokemonEggMove = -1;

        base::MutableState<int> m_selectedUnown = -1;
        base::MutableState<int> m_selectedItem = -1;
        base::MutableState<int> m_selectedMove = -1;
        base::MutableState<int> m_selectedTMHM = -1;
        base::MutableState<int> m_selectedTrainerGroup = -1;

        base::MutableState<int> m_selectedType = -1;
        base::MutableState<int> m_selectedTypeMatchup = -1;

    public:
        DatabasePanel(wxWindow *parent,
                      wxWindowID id = wxID_ANY,
                      const wxPoint &pos = wxDefaultPosition,
                      const wxSize &size = wxSize(500, 300),
                      long style = wxTAB_TRAVERSAL,
                      const wxString &name = wxEmptyString)
            : DatabasePanelBase(parent, id, pos, size, style, name)
        {
            InitializePokemonTab();
            InitializeUnownTab();
            InitializeItemTab();
            InitializeMoveTab();
            InitializeTmHmTab();
            InitializeTrainerGroupTab();
            InitializeTypeTab();
        }

    private:
        void InitializePokemonTab();
        void ClearPokemonTab();
        void UpdatePokemonImages();
        void UpdatePokemonEvolutionAndMoveList();
        void OnPokemonEvolutionsButtonClick(wxCommandEvent &event) override;
        void OnPokemonMovesButtonClick(wxCommandEvent &event) override;
        void OnPokemonEggMovesButtonClick(wxCommandEvent &event) override;
        void OnPokemonTMHMsButtonClick(wxCommandEvent &event) override;

        void InitializeUnownTab();
        void UpdateUnownImages();

        void InitializeItemTab();
        void InitializeItemEditor();

        void InitializeMoveTab();
        void InitializeMoveEditor();

        void InitializeTmHmTab();
        void UpdateTMHMsTab();
        void OnTMHMsButtonClick(wxCommandEvent &event) override;

        void InitializeTrainerGroupTab();
        void UpdateTrainerGroupImages();

        void InitializeTypeTab();
        void UpdateTypeMatchups();
        void OnTypeMatchupsButtonClick(wxCommandEvent &event) override;
        void OnTypeWeatherModifierRadioBox(wxCommandEvent &event) override;
    };
}
