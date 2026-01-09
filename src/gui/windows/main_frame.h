#ifndef _GUI_WINDOWS_MAIN_FRAME_H_
#define _GUI_WINDOWS_MAIN_FRAME_H_

#include "gui/generated/gui_base.h"
#include "utils.h"
#include <vector>

namespace gui::windows {

class MainFrame : public MainFrameBase
{
private:
    utils::subscriptions m_subscriptions;

public:
    MainFrame(wxWindow *parent);

private:
    void OnMenuSelected(wxCommandEvent &event) override;
};

} // namespace gui::windows

#endif
