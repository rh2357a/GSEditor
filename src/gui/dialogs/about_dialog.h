#ifndef _GUI_DIALOGS_ABOUT_DIALOG_H_
#define _GUI_DIALOGS_ABOUT_DIALOG_H_

#include "gui/generated/gui_base.h"

namespace gui::dialogs {

class AboutDialog : public AboutDialogBase
{
public:
    AboutDialog(wxWindow *parent = nullptr);
};

} // namespace gui::dialogs

#endif
