#pragma once

#include "services/pokegold.h"
#include "services/pokegold/data/game_data.h"
#include "ui/generated/ui_base.h"
#include "ui/ui.h"

#include <wx/window.h>

#include <optional>

namespace ui
{
    namespace internal
    {
        class MoveEditorDialog : public MoveEditorDialogBase
        {
        private:
            services::Pokegold &m_pokegold = services::Pokegold::Default();

            std::optional<pokegold::PokemonMove> m_result;

        public:
            MoveEditorDialog(wxWindow *parent, std::optional<pokegold::PokemonMove> defaultValue);

        private:
            void OnConfirmButtonClick(wxCommandEvent &event) override;
            void OnCancelButtonClick(wxCommandEvent &event) override;

        public:
            std::optional<pokegold::PokemonMove> GetResult() { return m_result; }
        };
    }

    /**
     * @brief 기술 편집창 열기
     *
     * @param parent 부모 윈도우
     * @param defaultValue 기본값 전달
     * @return 편집 또는 추가 결과값
     * @return std::nullopt 사용자의 취소를 처리
     */
    std::optional<pokegold::PokemonMove> ShowMoveEditorDialog(wxWindow *parent, std::optional<pokegold::PokemonMove> defaultValue = std::nullopt);
}
