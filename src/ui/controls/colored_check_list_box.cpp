#include "colored_check_list_box.h"

#include "ui/utils.h"

#include <wx/gdicmn.h>
#include <wx/renderer.h>

namespace
{
    const wxColour k_oddItemColor(255, 255, 255);
    const wxColour k_evenItemColor(240, 248, 255);
    const wxColour k_focusItemColor(0, 120, 215);

    const size_t k_maxVisibleItems = 10;
}

ui::ColoredCheckListBox::ColoredCheckListBox() : wxVListBox()
{
    SetItemCount(0);
    Bind(wxEVT_LEFT_DOWN, &ColoredCheckListBox::OnLeftDown, this);
    FixBorderThemeBug(this);
}

ui::ColoredCheckListBox::ColoredCheckListBox(wxWindow *parent,
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
    {
        m_items.assign(choices, choices + n);
        m_checked.assign(m_items.size(), false);
    }

    SetItemCount(m_items.size());
    Bind(wxEVT_LEFT_DOWN, &ColoredCheckListBox::OnLeftDown, this);
    FixBorderThemeBug(this);
}

ui::ColoredCheckListBox::ColoredCheckListBox(wxWindow *parent,
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
    m_checked.assign(m_items.size(), false);

    SetItemCount(m_items.size());
    Bind(wxEVT_LEFT_DOWN, &ColoredCheckListBox::OnLeftDown, this);
    FixBorderThemeBug(this);
}

wxCoord ui::ColoredCheckListBox::OnMeasureItem(size_t n) const
{
    return FromDIP(20);
}

wxSize ui::ColoredCheckListBox::DoGetBestSize() const
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

void ui::ColoredCheckListBox::OnDrawItem(wxDC &dc, const wxRect &rect, size_t n) const
{
    bool isEnabled = IsEnabled();
    bool isSelected = IsSelected(n);

    wxColour bg = isEnabled
                      ? isSelected ? k_focusItemColor : (n % 2 ? k_oddItemColor : k_evenItemColor)
                      : wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE);
    dc.SetBrush(wxBrush(bg));

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(rect);

    if (isSelected)
        dc.SetTextForeground(*wxWHITE);
    else
        dc.SetTextForeground(wxSystemSettings::GetColour(isEnabled ? wxSYS_COLOUR_WINDOWTEXT : wxSYS_COLOUR_GRAYTEXT));

    wxRect checkRect(rect.x + FromDIP(4), rect.y + FromDIP(2), FromDIP(16), FromDIP(16));

    int flags = wxCONTROL_NONE;
    flags |= m_checked[n] ? wxCONTROL_CHECKED : wxCONTROL_NONE;
    flags |= !isEnabled ? wxCONTROL_DISABLED : wxCONTROL_NONE;
    wxRendererNative::Get().DrawCheckBox(m_win, dc, checkRect, flags);

    dc.DrawText(m_items[n], rect.x + FromDIP(22), rect.y + 3);
}

void ui::ColoredCheckListBox::OnLeftDown(wxMouseEvent &event)
{
    wxPoint pt = event.GetPosition();

    wxCoord h = OnMeasureItem(0);
    size_t first = GetVisibleBegin();

    size_t item = first + pt.y / h;

    if (item >= GetItemCount())
    {
        event.Skip();
        return;
    }

    wxSize cbSize = wxRendererNative::Get().GetCheckBoxSize(this);
    if (pt.x >= 4 && pt.x <= 4 + cbSize.x)
    {
        m_checked[item] = !m_checked[item];
        RefreshRow(item);

        wxCommandEvent evt(wxEVT_CHECKLISTBOX, GetId());
        evt.SetInt(item);
        evt.SetEventObject(this);
        ProcessWindowEvent(evt);

        return;
    }

    event.Skip();
}

unsigned int ui::ColoredCheckListBox::GetCount() const
{
    return (unsigned int)m_items.size();
}

void ui::ColoredCheckListBox::Append(wxString item)
{
    m_items.push_back(item);
    m_checked.push_back(false);
    SetItemCount(m_items.size());
}

wxString ui::ColoredCheckListBox::GetString(int index)
{
    return m_items[index];
}

void ui::ColoredCheckListBox::SetString(int index, wxString str)
{
    m_items[index] = str;
    RefreshRow(index);
}

void ui::ColoredCheckListBox::Check(int index, bool checked)
{
    m_checked[index] = checked;
    RefreshRow(index);
}

bool ui::ColoredCheckListBox::IsChecked(int index) const
{
    return m_checked[index];
}
