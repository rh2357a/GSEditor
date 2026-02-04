#pragma once

#include "services/pokegold/data/game_data.h"
#include "services/pokegold.h"
#include "ui/ui.h"

#include <span>

namespace ui
{
    namespace internal
    {
        class BadDataDialog : public BadDataDialogBase
        {
        private:
            services::Pokegold &m_pokegold = services::Pokegold::Default();

        public:
            BadDataDialog(wxWindow *parent, std::span<const pokegold::BadData> badDataList);

        private:
            void OnDialogShow(wxShowEvent &event) override;
            void OnConfirmButtonClick(wxCommandEvent &event) override;
            void OnYesButtonClick(wxCommandEvent &event) override;
            void OnNoButtonClick(wxCommandEvent &event) override;
        };
    }

    /// @brief 손상 데이터 알림창 열기
    /// @param parent 상위 윈도우
    /// @param badDataList 손상 데이터 목록
    void ShowBadDataDialog(wxWindow *parent, std::span<const pokegold::BadData> badDataList);
};
