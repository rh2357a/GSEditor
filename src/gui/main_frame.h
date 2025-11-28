#ifndef _GUI_MAIN_FRAME_H_
#define _GUI_MAIN_FRAME_H_

#include "generated/gui_base.h"

namespace gui {

class MainFrame : public MainFrameBase
{
public:
    MainFrame(wxWindow *parent);

private:
    void OnMenuSelected(wxCommandEvent &event) override;
};

} // namespace gui

#endif
