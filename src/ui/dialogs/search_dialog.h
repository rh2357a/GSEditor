#pragma once

#include "ui/ui.h"

#include <wx/string.h>
#include <wx/timer.h>
#include <wx/window.h>

#include <vector>

namespace ui::internal
{
    class SearchDialog : public SearchDialogBase
    {
    public:
        wxTimer m_searchTimer;
        std::vector<wxString> Items;
        int Selected = -1;

    public:
        SearchDialog(wxWindow *parent);

    private:
        void OnInit(wxInitDialogEvent &event);
        void OnKeywordTextChanged(wxCommandEvent &event) override;
        void OnSearchTimer(wxTimerEvent &event);
        void OnConfirmButtonClick(wxCommandEvent &event) override;
        void OnCancelButtonClick(wxCommandEvent &event) override;
    };

    void ApplyListSearchDialog(wxWindow *parent, const std::initializer_list<wxWindow *> &ctrls);
}
