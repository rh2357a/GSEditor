#pragma once

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/stattext.h>

namespace ui
{
    class LabeledSeparator : public wxBoxSizer
    {
    private:
        wxStaticText *m_label = nullptr;
        wxStaticLine *m_separator = nullptr;

    public:
        LabeledSeparator(wxWindow *parent,
                         wxWindowID id,
                         const wxString &label,
                         const wxPoint &pos = wxDefaultPosition,
                         const wxSize &size = wxDefaultSize,
                         long style = 0,
                         const wxString &name = wxASCII_STR(wxStaticTextNameStr));

    public:
        void Wrap(int width);
    };
}
