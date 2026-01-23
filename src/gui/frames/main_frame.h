#ifndef _GUI_FRAMES_MAIN_FRAME_H_
#define _GUI_FRAMES_MAIN_FRAME_H_

#include "gui.h"
#include "core.h"
#include <vector>

namespace gui::frames {

class MainFrame : public MainFrameBase
{
private:
    core::subscriptions m_subscriptions;

public:
    MainFrame(wxWindow *parent);

private:
    void OnMenuSelected(wxCommandEvent &event) override;
    void OnClose(wxCloseEvent &event) override;
};

} // namespace gui::frames

#endif
