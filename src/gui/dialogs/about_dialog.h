#ifndef _GUI_DIALOGS_ABOUT_DIALOG_H_
#define _GUI_DIALOGS_ABOUT_DIALOG_H_

#include "gui.h"

namespace gui::dialogs {

class AboutDialog : public AboutDialogBase
{
public:
    AboutDialog(wxWindow *parent = nullptr);
};

} // namespace gui::dialogs

#endif
