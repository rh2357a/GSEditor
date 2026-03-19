#pragma once

#include "services/app_configs.h"
#include "services/pokegold.h"
#include "ui/dialogs/database_dialog.h"
#include "ui/ui.h"

namespace ui
{
    class MainFrame : public MainFrameBase
    {
    private:
        inline static const auto TAG = "ui::MainFrame";

    private:
        services::AppConfigs &m_configs = services::AppConfigs::Default();
        services::Pokegold &m_pokegold = services::Pokegold::Default();

        ui::DatabaseDialog m_dbDialog;

    public:
        MainFrame();

    private:
        void RomOpenedControlHandler();
        void StatusBarTextHandler();
        void SettingsMenusHandler();

        void OnClose(wxCloseEvent &event) override;
        void OnMenuSelected(wxCommandEvent &event) override;
        void OnMenuItemSelected(wxCommandEvent &event) override;

        void SaveRomFile();
    };
}
