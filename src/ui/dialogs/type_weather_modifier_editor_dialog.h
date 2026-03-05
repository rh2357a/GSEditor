#pragma once

#include "services/pokegold.h"
#include "services/pokegold/data/game_data.h"
#include "ui/ui.h"

#include <wx/window.h>

#include <optional>

namespace ui
{
    namespace internal
    {
        class TypeWeatherModifierEditorDialog : public TypeWeatherModifierEditorDialogBase
        {
        private:
            services::Pokegold &m_pokegold = services::Pokegold::Default();

        public:
            std::optional<pokegold::WeatherTypeModifier> Result;

        public:
            TypeWeatherModifierEditorDialog(wxWindow *parent, std::optional<pokegold::WeatherTypeModifier> defaultValue = std::nullopt);

        private:
            void OnConfirmButtonClick(wxCommandEvent &event) override;
            void OnCancelButtonClick(wxCommandEvent &event) override;
        };
    }

    /**
     * @brief 타입 날씨 보정 편집창 열기
     *
     * @param parent 부모 윈도우
     * @param defaultValue 편집할 데이터
     * @return 편집 또는 추가 결과
     * @return std::nullopt 사용자 취소
     */
    std::optional<pokegold::WeatherTypeModifier> ShowTypeWeatherModifierEditorDialog(wxWindow *parent, std::optional<pokegold::WeatherTypeModifier> defaultValue = std::nullopt);
}
