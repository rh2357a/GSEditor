#include "gui/main_frame.h"
#include "pokegold.h"
#include "utils.h"
#include <wx/wx.h>

class App : public wxApp
{
public:
    bool OnInit()
    {
        init_logging();
        pokegold::bytes::init_charmap();
        utils::init_exec();
        wxInitAllImageHandlers();

        gui::MainFrame *frame = new gui::MainFrame(nullptr);
        frame->Show();

        return true;
    }
};

wxIMPLEMENT_APP(App);
