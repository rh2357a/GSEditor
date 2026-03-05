#pragma once

#include <wx/listctrl.h>
#include <wx/wx.h>

namespace ui
{
    class ColoredListCtrl : public wxListCtrl
    {
    private:
        int m_columnCount = 0;
        std::vector<std::vector<wxString>> m_items;

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

    protected:
        virtual wxString OnGetItemText(long item, long column) const override;
        virtual wxListItemAttr *OnGetItemAttr(long item) const override;

    public:
        long AppendColumn(const wxString &heading);
        long InsertItem(int idx, const wxString &str);
        bool DeleteItem(long item);
        bool DeleteAllItems();
        bool SetItem(long index, int col, const wxString &label);
    };
}
