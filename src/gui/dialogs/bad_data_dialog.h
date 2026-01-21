#ifndef _GUI_DIALOGS_BAD_DATA_DIALOG_H_
#define _GUI_DIALOGS_BAD_DATA_DIALOG_H_

#include "gui.h"
#include "pokegold.h"

#include <vector>

namespace gui::dialogs {

class BadDataDialog : public BadDataDialogBase
{
public:
    BadDataDialog(wxWindow *parent, std::span<const pokegold::data::bad_data> badDataList);

public:
    void OnDialogShow(wxShowEvent &event) override;
    void OnConfirmButtonClick(wxCommandEvent &event) override;
    void OnYesButtonClick(wxCommandEvent &event) override;
    void OnNoButtonClick(wxCommandEvent &event) override;
};

} // namespace gui::dialogs

#endif
