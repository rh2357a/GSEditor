#ifndef _GUI_CONTROLS_H_
#define _GUI_CONTROLS_H_

#include "gui/controls/database_panel.h"
#include <initializer_list>

namespace gui::controls {

inline void NestedScrolling(const std::initializer_list<wxWindow *> &ctrls)
{
    for (auto *ctrl : ctrls)
    {
        if (!ctrl)
            continue;

        if (auto *spin = wxDynamicCast(ctrl, wxSpinCtrlDouble))
        {
            spin->Bind(wxEVT_MOUSEWHEEL, [spin](wxMouseEvent &event) {
                wxWindow *focus = wxWindow::FindFocus();
                bool focused = focus == spin || spin->IsDescendant(focus);
                event.Skip(focused);
            });
        }
        else if (auto *scrolled = wxDynamicCast(ctrl, wxScrolledWindow))
        {
            scrolled->Bind(wxEVT_MOUSEWHEEL, [scrolled](wxMouseEvent &event) {
                int vx, vy;
                scrolled->GetViewStart(&vx, &vy);

                int px, py;
                scrolled->GetScrollPixelsPerUnit(&px, &py);

                wxSize virt = scrolled->GetVirtualSize();
                wxSize client = scrolled->GetClientSize();

                bool scrollUp = event.GetWheelRotation() > 0;
                bool scrollDown = event.GetWheelRotation() < 0;
                bool canScrollToTop = vy > 0;
                bool canScrollToBottom = vy < (virt.y - client.y) / py;
                if ((scrollUp && canScrollToTop) || (scrollDown && canScrollToBottom))
                {
                    event.Skip();
                    return;
                }

                event.ResumePropagation(wxEVENT_PROPAGATE_MAX);
                event.Skip();
            });
        }
        else if (auto *list = wxDynamicCast(ctrl, wxListCtrl))
        {
            list->Bind(wxEVT_MOUSEWHEEL, [list](wxMouseEvent &event) {
                int pos = list->GetScrollPos(wxVERTICAL);
                int range = list->GetScrollRange(wxVERTICAL);
                int cntPage = list->GetCountPerPage();

                bool scrollUp = event.GetWheelRotation() > 0;
                bool scrollDown = event.GetWheelRotation() < 0;
                bool canScrollToTop = pos > 0;
                bool canScrollToBottom = pos < range - cntPage - 1;
                if ((scrollUp && canScrollToTop) || (scrollDown && canScrollToBottom))
                {
                    event.Skip();
                    return;
                }

                event.ResumePropagation(wxEVENT_PROPAGATE_MAX);
                event.Skip();
            });
        }
        else if (auto *control = wxDynamicCast(ctrl, wxControl))
        {
            control->Bind(wxEVT_MOUSEWHEEL, [](wxMouseEvent &event) {
                event.ResumePropagation(wxEVENT_PROPAGATE_MAX);
                event.Skip();
            });
        }
    }
}

inline void Select(wxWindow *ctrl, int selection)
{
    if (!ctrl)
        return;

    if (auto *list = wxDynamicCast(ctrl, wxListBox))
    {
        list->Select(selection);

        if (selection == -1)
        {
            wxCommandEvent event(wxEVT_LISTBOX, list->GetId());
            event.SetEventObject(list);
            event.SetInt(-1);
            list->ProcessWindowEvent(event);
        }
    }
    else if (auto *combo = wxDynamicCast(ctrl, wxComboBox))
    {
        combo->Select(selection);

        if (selection == -1)
        {
            wxCommandEvent event(wxEVT_COMBOBOX, combo->GetId());
            event.SetEventObject(combo);
            event.SetInt(-1);
            combo->ProcessWindowEvent(event);
        }
    }
}

inline void SetValue(wxSpinCtrlDouble *ctrl, double value)
{
    if (ctrl != nullptr)
    {
        ctrl->SetValue(value);

        wxSpinDoubleEvent event(wxEVT_SPINCTRLDOUBLE, ctrl->GetId());
        event.SetEventObject(ctrl);
        event.SetValue(value);
        ctrl->GetEventHandler()->ProcessEvent(event);
    }
}

} // namespace gui::controls

#endif
