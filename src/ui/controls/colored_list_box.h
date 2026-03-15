#pragma once

#include <wx/dc.h>
#include <wx/listbox.h>
#include <wx/vlbox.h>

namespace ui
{
    class ColoredListBox : public wxVListBox
    {
    private:
        std::vector<wxString> m_items;

    public:
        ColoredListBox();

        ColoredListBox(wxWindow *parent,
                       wxWindowID id,
                       const wxPoint &pos = wxDefaultPosition,
                       const wxSize &size = wxDefaultSize,
                       int n = 0,
                       const wxString choices[] = NULL,
                       long style = 0,
                       const wxValidator &validator = wxDefaultValidator,
                       const wxString &name = wxASCII_STR(wxListBoxNameStr));

        ColoredListBox(wxWindow *parent,
                       wxWindowID id,
                       const wxPoint &pos,
                       const wxSize &size,
                       const wxArrayString &choices,
                       long style = 0,
                       const wxValidator &validator = wxDefaultValidator,
                       const wxString &name = wxASCII_STR(wxListBoxNameStr));

    protected:
        virtual wxCoord OnMeasureItem(size_t n) const override;
        virtual wxSize DoGetBestSize() const override;
        virtual void OnDrawItem(wxDC &dc, const wxRect &rect, size_t n) const override;

    public:
        int GetCount() const;
        wxString GetString(int index);
        void SetString(int index, wxString str);
        void Append(wxString item);
        void Clear();
    };
}
