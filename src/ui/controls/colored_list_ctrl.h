#pragma once

#include <wx/listctrl.h>
#include <wx/wx.h>

namespace ui
{
    class ColoredListCtrl : public wxListCtrl
    {
    public:
        ColoredListCtrl();

        ColoredListCtrl(wxWindow *parent,
                        wxWindowID id = wxID_ANY,
                        const wxPoint &pos = wxDefaultPosition,
                        const wxSize &size = wxDefaultSize,
                        long style = wxLC_ICON,
                        const wxValidator &validator = wxDefaultValidator,
                        const wxString &name = wxASCII_STR(wxListCtrlNameStr));

    private:
        void Initialize();
    };
}
