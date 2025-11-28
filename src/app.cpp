#include "gui/main_frame.h"
#include "pokegold.h"
#include "utils.h"

#include <wx/wx.h>

#include <iostream>

class App : public wxApp
{
public:
    bool OnInit()
    {
#ifdef DEBUG
        freopen("GSEditor.log", "w", stdout);
        freopen("GSEditor.log", "a", stderr);
        setvbuf(stdout, nullptr, _IONBF, 0);
        setvbuf(stderr, nullptr, _IONBF, 0);
        std::ios::sync_with_stdio(true);
#else
        std::ios::sync_with_stdio(false);
#endif

        pokegold::bytes::init_charmap();
        utils::init_exec();
        wxInitAllImageHandlers();

        gui::MainFrame *frame = new gui::MainFrame(nullptr);
        frame->Show();

        return true;
    }
};

wxIMPLEMENT_APP(App);
