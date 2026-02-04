#pragma once

#include "base/functional/state.h"
#include "services/app_configs.h"
#include "services/pokegold.h"
#include "ui/ui.h"

namespace ui
{
    class MainFrame : public MainFrameBase
    {
    private:
        inline static const auto TAG = "ui::main_frame";

    private:
        services::AppConfigs &m_configs = services::AppConfigs::Default();
        services::Pokegold &m_pokegold = services::Pokegold::Default();

    public:
        MainFrame();

    private:
        void RomOpenedControlHandler();
        void StatusBarTextHandler();
        void EmulatorMenuHelpHandler();

        void OnClose(wxCloseEvent &event) override;
        void OnMenuSelected(wxCommandEvent &event) override;
    };
}
