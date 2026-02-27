#pragma once

#include "base/functional/state.h"
#include "services/pokegold.h"
#include "services/pokegold/data/game_data.h"
#include "ui/ui.h"

#include <wx/window.h>

#include <vector>

namespace ui
{
    namespace internal
    {
        class ImportMoveDialog : public ImportMoveDialogBase
        {
        private:
            services::Pokegold &m_pokegold = services::Pokegold::Default();

            base::MutableState<int> m_selectedPokemon = -1;
            base::MutableState<int> m_selectedMove = -1;

        public:
            std::vector<pokegold::PokemonMove> Result;

        public:
            ImportMoveDialog(wxWindow *parent);

        private:
            void OnConfirmButtonClick(wxCommandEvent &event) override;
            void OnCancelButtonClick(wxCommandEvent &event) override;
            void OnIgnoreButtonClick(wxCommandEvent &event) override;
        };
    }

    /**
     * @brief 기술 가져오기 창 열기
     *
     * @param parent 부모 윈도우
     * @return 가져오기 결과 (기술 목록)
     */
    std::vector<pokegold::PokemonMove> ShowImportMoveDialog(wxWindow *parent);
}
