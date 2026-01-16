#ifndef _GUI_FRAMES_MAIN_FRAME_H_
#define _GUI_FRAMES_MAIN_FRAME_H_

#include "gui/generated/gui_base.h"
#include "utils.h"
#include <vector>

namespace gui::frames {

class MainFrame : public MainFrameBase
{
private:
    utils::subscriptions m_subscriptions;

public:
    MainFrame(wxWindow *parent);

private:
    void OnMenuSelected(wxCommandEvent &event) override;
    void OnClose(wxCloseEvent &event) override;
};

} // namespace gui::frames

#endif
