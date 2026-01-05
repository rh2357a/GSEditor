#ifndef _GUI_WINDOWS_MAIN_FRAME_H_
#define _GUI_WINDOWS_MAIN_FRAME_H_

#include "gui/generated/gui_base.h"

namespace gui::windows {

class MainFrame : public MainFrameBase
{
public:
    MainFrame(wxWindow *parent);

private:
    void OnMenuSelected(wxCommandEvent &event) override;
};

} // namespace gui::windows

#endif
