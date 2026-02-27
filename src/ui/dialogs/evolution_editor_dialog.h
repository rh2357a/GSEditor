#pragma once

#include "base/functional/state.h"
#include "services/pokegold.h"
#include "services/pokegold/data/game_data.h"
#include "ui/ui.h"

#include <optional>

namespace ui
{
    namespace internal
    {
        enum class EvolveType
        {
            LevelUp,
            UseItem,
            Trade,
        };

        enum class LevelUpType
        {
            Common,
            Happiness,
        };

        class EvolutionEditorDialog : public EvolutionEditorDialogBase
        {
        private:
            services::Pokegold &m_pokegold = services::Pokegold::Default();

            base::MutableState<EvolveType> m_evolveType = EvolveType::LevelUp;
            base::MutableState<LevelUpType> m_levelUpType = LevelUpType::Common;
            base::MutableState<bool> m_tradeGaveItem = false;

            std::optional<pokegold::EvolutionMethod> m_result;

        public:
            EvolutionEditorDialog(wxWindow *parent, std::optional<pokegold::EvolutionMethod> defaultValue);

        private:
            void OnConfirmButtonClick(wxCommandEvent &event) override;
            void OnCancelButtonClick(wxCommandEvent &event) override;

        public:
            std::optional<pokegold::EvolutionMethod> GetResult() { return m_result; }
        };
    }

    /**
     * @brief 진화 편집기 창 열기
     *
     * @param parent 부모 윈도우
     * @param defaultValue 기본값
     * @return 편집 또는 추가 결과값
     * @return std::nullopt 사용자의 취소를 처리
     */
    std::optional<pokegold::EvolutionMethod> ShowEvolutionEditorDialog(wxWindow *parent, std::optional<pokegold::EvolutionMethod> defaultValue = std::nullopt);
}
