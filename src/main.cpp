#include "base/sidecar/sidecar.h"
#include "base/log.h"
#include "services/app_configs.h"
#include "services/pokegold/data/string.h"
#include "ui/frames/main_frame.h"
#include "resources.h"

#include <wx/wx.h>

class App : public wxApp
{
private:
    inline static const auto TAG = "App";

    services::AppConfigs &m_appConfigs = services::AppConfigs::Default();

public:
    bool OnInit() override
    {
        wxInitAllImageHandlers();
        base::InitializeLog();
        base::InitializeSidecar();
        pokegold::String::InitializeCharmap();
        m_appConfigs.Initialize();

        base::Log(TAG, "OnInit: run app");
        auto *frame = new ui::MainFrame();
        SetTopWindow(frame);
        frame->Show();

        return true;
    }

    int OnExit() override
    {
        base::Log(TAG, "OnExit");
        m_appConfigs.Destroy();
        return 0;
    }
};

wxIMPLEMENT_APP(App);
