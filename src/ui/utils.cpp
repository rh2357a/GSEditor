#include "utils.h"

#include <windows.h>
#include <commctrl.h>

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
