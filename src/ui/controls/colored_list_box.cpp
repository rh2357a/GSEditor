#include "colored_list_box.h"

#include "ui/utils.h"

namespace
{
    const wxColour k_oddItemColor(255, 255, 255);
    const wxColour k_evenItemColor(240, 248, 255);
    const wxColour k_focusItemColor(0, 120, 215);

    const size_t k_maxVisibleItems = 10;
}

ui::ColoredListBox::ColoredListBox() : wxVListBox()
{
    SetItemCount(0);
    FixBorderThemeBug(this);
}

ui::ColoredListBox::ColoredListBox(wxWindow *parent,
                                   wxWindowID id,
                                   const wxPoint &pos,
                                   const wxSize &size,
                                   int n,
                                   const wxString choices[],
                                   long style,
                                   const wxValidator &validator,
                                   const wxString &name)
    : wxVListBox(parent, id, pos, size, style, name)
{
    if (choices && n > 0)
        m_items.assign(choices, choices + n);

    SetItemCount(m_items.size());
    FixBorderThemeBug(this);
}

ui::ColoredListBox::ColoredListBox(wxWindow *parent,
                                   wxWindowID id,
                                   const wxPoint &pos,
                                   const wxSize &size,
                                   const wxArrayString &choices,
                                   long style,
                                   const wxValidator &validator,
                                   const wxString &name)
    : wxVListBox(parent, id, pos, size, style, name)
{
    m_items.insert(m_items.end(), choices.begin(), choices.end());

    SetItemCount(m_items.size());
    FixBorderThemeBug(this);
}

wxCoord ui::ColoredListBox::OnMeasureItem(size_t n) const
{
    return FromDIP(20);
}

wxSize ui::ColoredListBox::DoGetBestSize() const
{
    size_t itemCount = GetItemCount();
    size_t visibleItems = std::min(itemCount, k_maxVisibleItems);

    wxCoord totalHeight = 0;
    for (size_t i = 0; i < visibleItems; ++i)
        totalHeight += OnMeasureItem(i);

    totalHeight += GetMargins().y * 2;
    totalHeight += 5;

    wxSize size = wxVListBox::DoGetBestSize();
    size.SetHeight(totalHeight);
    return size;
}

void ui::ColoredListBox::OnDrawItem(wxDC &dc, const wxRect &rect, size_t n) const
{
    bool isEnabled = IsEnabled();

    if (isEnabled)
    {
        if (IsSelected(n))
        {
            dc.SetBrush(wxBrush(k_focusItemColor));
            dc.SetPen(*wxTRANSPARENT_PEN);
            dc.DrawRectangle(rect);
            dc.SetTextForeground(*wxWHITE);
        }
        else
        {
            dc.SetBrush(wxBrush(n % 2 ? k_oddItemColor : k_evenItemColor));
            dc.SetPen(*wxTRANSPARENT_PEN);
            dc.DrawRectangle(rect);
            dc.SetTextForeground(*wxBLACK);
        }
    }
    else
    {
        dc.SetBrush(wxBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE)));
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.DrawRectangle(rect);
        dc.SetTextForeground(wxSystemSettings::GetColour(wxSYS_COLOUR_GRAYTEXT));
    }

    dc.DrawText(m_items[n], rect.x + 4, rect.y + 3);
}

int ui::ColoredListBox::GetCount() const
{
    return m_items.size();
}

wxString ui::ColoredListBox::GetString(int index)
{
    return m_items[index];
}

void ui::ColoredListBox::SetString(int index, wxString str)
{
    m_items[index] = str;
    RefreshRow(index);
}

void ui::ColoredListBox::Append(wxString item)
{
    m_items.push_back(item);
    SetItemCount(m_items.size());
    RefreshAll();
}

void ui::ColoredListBox::Clear()
{
    m_items.clear();
    SetItemCount(0);
    RefreshAll();
}
