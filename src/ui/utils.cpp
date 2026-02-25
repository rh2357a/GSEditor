#include "utils.h"

#include <commctrl.h>
#include <windows.h>
#include <wx/event.h>
#include <wx/popupwin.h>
#include <wx/wx.h>

namespace
{
    class DestroyPopupTransientWindow : public wxPopupTransientWindow
    {
    public:
        DestroyPopupTransientWindow() : wxPopupTransientWindow() {}
        DestroyPopupTransientWindow(wxWindow *parent, int style = wxBORDER_NONE) : wxPopupTransientWindow(parent, style) {}

    private:
        void OnDismiss() override
        {
            Destroy();
        }
    };
}

void ui::ApplyListCtrlFixedHeader(wxListCtrl *ctrl)
{
    HWND listViewHwnd = ctrl->GetHWND();
    HWND headerHwnd = (HWND)::SendMessage(listViewHwnd, LVM_GETHEADER, 0, 0);
    LONG headerStyle = ::GetWindowLong(headerHwnd, GWL_STYLE);
    // headerStyle |= HDS_NOSIZING;
    headerStyle &= ~HDS_DRAGDROP;
    ::SetWindowLong(headerHwnd, GWL_STYLE, headerStyle);
}

void ui::AutoListCtrlColumnWidth(wxListCtrl *ctrl)
{
    for (int i = 0; i < ctrl->GetColumnCount(); i++)
        ctrl->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
}

void ui::ShowDropdownPopup(wxWindow *parent, wxWindow *popupCtrl)
{
    DestroyPopupTransientWindow *popupWindow = new DestroyPopupTransientWindow(parent, wxBORDER_SIMPLE | wxPU_CONTAINS_CONTROLS);
    popupCtrl->Reparent(popupWindow);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(popupCtrl, 1, wxEXPAND);
    popupWindow->SetSizerAndFit(sizer);

    wxPoint screenPos = parent->ClientToScreen(wxPoint(0, 0));
    {
        int popupHeight = popupWindow->GetSize().GetHeight();
        int parentHeight = parent->GetSize().GetHeight();

        wxRect screenRect = wxGetClientDisplayRect();
        if (screenPos.y + parentHeight + popupHeight > screenRect.GetBottom())
            screenPos.y -= popupHeight;
        else
            screenPos.y += parentHeight;
    }

    popupWindow->Move(screenPos);
    popupWindow->Popup();
}
