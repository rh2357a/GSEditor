#pragma once

#include "ui/ui.h"

#include <windows.h>
#include <wx/window.h>

namespace ui
{
    class DatabaseDialog : public DatabaseDialogBase
    {
    public:
        DatabaseDialog(wxWindow *parent) : DatabaseDialogBase(parent) {}

    public:
        int ShowModal() override
        {
            HWND hwnd = (HWND)GetHandle();
            HWND parent = (HWND)GetParent()->GetHandle();
            ::SetWindowLongPtr(hwnd, GWLP_HWNDPARENT, (LONG_PTR)parent);

            LONG exStyle = ::GetWindowLong(hwnd, GWL_EXSTYLE);
            exStyle &= ~WS_EX_APPWINDOW;
            // exStyle |= WS_EX_TOOLWINDOW;
            ::SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);

            CenterOnParent();

            return wxDialog::ShowModal();
        }

    private:
        void OnConfirmButtonClick(wxCommandEvent &event) override { EndModal(wxID_OK); }
    };
}
