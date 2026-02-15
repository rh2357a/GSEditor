#pragma once

#include "ui/ui.h"

namespace ui
{
    namespace internal
    {
        class AboutDialog : public AboutDialogBase
        {
        public:
            AboutDialog(wxWindow *parent);
        };
    }

    /**
     * @brief 앱 정보창 열기
     *
     * @param parent 부모 윈도우
     */
    void ShowAboutDialog(wxWindow *parent);
}
