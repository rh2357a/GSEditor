#pragma once

#include <wx/dc.h>
#include <wx/listbox.h>
#include <wx/vlbox.h>

namespace ui
{
    class ColoredCheckListBox : public wxVListBox
    {
    private:
        std::vector<wxString> m_items;
        std::vector<bool> m_checked;

    public:
        ColoredCheckListBox();

        ColoredCheckListBox(wxWindow *parent,
                            wxWindowID id,
                            const wxPoint &pos = wxDefaultPosition,
                            const wxSize &size = wxDefaultSize,
                            int n = 0,
                            const wxString choices[] = NULL,
                            long style = 0,
                            const wxValidator &validator = wxDefaultValidator,
                            const wxString &name = wxASCII_STR(wxListBoxNameStr));

        ColoredCheckListBox(wxWindow *parent,
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
        void OnLeftDown(wxMouseEvent &event);

    public:
        unsigned int GetCount() const;
        void Append(wxString item);

        wxString GetString(int index);
        void SetString(int index, wxString str);

        void Check(int index, bool checked);
        bool IsChecked(int index) const;
    };
}
