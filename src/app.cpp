#include "core.h"
#include "gui.h"
#include "pokegold.h"
#include "utils.h"

#include <wx/wx.h>

#include <filesystem>

class App : public wxApp
{
public:
    bool OnInit()
    {
        init_logging();
        wxInitAllImageHandlers();

        pokegold::string::init_charmap();
        app_settings::init();
        utils::init_exec();

        // 구버전 데이터 제거
        const auto legacy_data_path = utils::files::get_app_data_path_legacy();
        std::filesystem::remove_all(legacy_data_path);

        gui::frames::MainFrame *frame = new gui::frames::MainFrame(nullptr);
        frame->Show();

        return true;
    }
};

wxIMPLEMENT_APP(App);
