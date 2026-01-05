#ifndef _GUI_WINDOWS_ABOUT_DIALOG_H_
#define _GUI_WINDOWS_ABOUT_DIALOG_H_

#include "gui/generated/gui_base.h"

namespace gui::windows {

class AboutDialog : public AboutDialogBase
{
public:
    AboutDialog(wxWindow *parent = nullptr);
};

} // namespace gui::windows

#endif
