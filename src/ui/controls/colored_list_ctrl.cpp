#include "colored_list_ctrl.h"

#include "ui/utils.h"

#include <wx/listbase.h>
#include <wx/listctrl.h>

#include <vector>

namespace
{
    const wxColour k_oddItemColor(255, 255, 255);
    const wxColour k_evenItemColor(240, 248, 255);
}

ui::ColoredListCtrl::ColoredListCtrl() : wxListCtrl()
{
    Initialize();
}

ui::ColoredListCtrl::ColoredListCtrl(wxWindow *parent,
                                     wxWindowID id,
                                     const wxPoint &pos,
                                     const wxSize &size,
                                     long style,
                                     const wxValidator &validator,
                                     const wxString &name)
    : wxListCtrl(parent, id, pos, size, style | wxLC_VIRTUAL, validator, name)
{
    Initialize();
}

void ui::ColoredListCtrl::Initialize()
{
    FixBorderThemeBug(this);
    SetItemCount(0);
}

wxString ui::ColoredListCtrl::OnGetItemText(long item, long column) const
{
    return m_items[item][column];
}

wxListItemAttr *ui::ColoredListCtrl::OnGetItemAttr(long item) const
{
    static wxListItemAttr oddAttr;
    static wxListItemAttr evenAttr;
    oddAttr.SetBackgroundColour(k_oddItemColor);
    evenAttr.SetBackgroundColour(k_evenItemColor);
    return (item % 2) ? &oddAttr : &evenAttr;
}

long ui::ColoredListCtrl::AppendColumn(const wxString &heading)
{
    long ret = ((wxListCtrl *)this)->AppendColumn(heading);
    m_columnCount++;
    return ret;
}

long ui::ColoredListCtrl::InsertItem(int idx, const wxString &str)
{
    m_items.emplace_back(std::vector<wxString>(m_columnCount, wxT("")));
    SetItemCount((long)m_items.size());

    wxListEvent ev(wxEVT_LIST_INSERT_ITEM, GetId());
    ev.SetEventObject(this);
    ev.m_itemIndex = idx;
    ProcessWindowEvent(ev);

    return long(m_items.size() - 1);
}

bool ui::ColoredListCtrl::DeleteAllItems()
{
    m_items.clear();
    SetItemCount(0);

    wxListEvent ev(wxEVT_LIST_DELETE_ALL_ITEMS, GetId());
    ev.SetEventObject(this);
    ProcessWindowEvent(ev);

    return true;
}

bool ui::ColoredListCtrl::DeleteItem(long item)
{
    m_items.erase(m_items.begin() + item);
    SetItemCount((long)m_items.size());

    wxListEvent ev(wxEVT_LIST_DELETE_ITEM, GetId());
    ev.SetEventObject(this);
    ev.m_itemIndex = item;
    ProcessWindowEvent(ev);

    return true;
}

bool ui::ColoredListCtrl::SetItem(long index, int col, const wxString &label)
{
    m_items[index][col] = label;
    return true;
}
