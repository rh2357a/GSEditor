#include "colored_list_ctrl.h"

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
    : wxListCtrl(parent, id, pos, size, style, validator, name)
{
    Initialize();
}

void ui::ColoredListCtrl::Initialize()
{
    auto listCtrlFunc = [this](wxListEvent &ev) {
        ev.Skip();

        CallAfter([this]() {
            Freeze();

            int count = GetItemCount();
            for (int i = 0; i < count; ++i)
                SetItemBackgroundColour(i, i % 2 ? k_oddItemColor : k_evenItemColor);

            Thaw();
        });
    };

    Bind(wxEVT_LIST_DELETE_ITEM, listCtrlFunc);
    Bind(wxEVT_LIST_DELETE_ALL_ITEMS, listCtrlFunc);
    Bind(wxEVT_LIST_INSERT_ITEM, listCtrlFunc);
}
