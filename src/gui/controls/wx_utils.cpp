#include "wx_utils.h"

#include <windows.h>
#include <commctrl.h>

#include <functional>

void gui::controls::AutoColumnsWidth(wxListCtrl *ctrl)
{
    for (int i = 0; i < ctrl->GetColumnCount(); i++)
        ctrl->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
}

void gui::controls::FixedHeaderWidth(wxListCtrl *ctrl, const std::vector<ListCtrlColumn> columns)
{
    HWND listViewHwnd = ctrl->GetHWND();
    HWND headerHwnd = (HWND)::SendMessage(listViewHwnd, LVM_GETHEADER, 0, 0);
    LONG headerStyle = ::GetWindowLong(headerHwnd, GWL_STYLE);
    headerStyle |= HDS_NOSIZING;
    headerStyle &= ~HDS_DRAGDROP;
    ::SetWindowLong(headerHwnd, GWL_STYLE, headerStyle);

    double totalFlex = 0.0;
    int totalPixels = 0;

    int i = 0;
    for (const auto &column : columns)
    {
        totalFlex += (column.width < 0.0 ? -column.width : 0.0);
        totalPixels += (column.width >= 0.0 ? (int)column.width : 0);
        ctrl->InsertColumn(i++, column.title);
    }

    auto resizedFunc = [ctrl, totalFlex, totalPixels, columns](auto &ev) {
        int totalWidth = ctrl->GetClientSize().GetWidth();
        int flexPixels = totalWidth - totalPixels;

        for (int i = 0; i < ctrl->GetColumnCount(); i++)
        {
            const auto &column = columns[i];
            if (column.width >= 0)
            {
                ctrl->SetColumnWidth(i, (int)column.width);
            }
            else
            {
                int flexPixel = (int)flexPixels * (-column.width / totalFlex);
                ctrl->SetColumnWidth(i, flexPixel);
            }
        }

        ctrl->Layout();
    };

    ctrl->Bind(wxEVT_SIZE, resizedFunc);
}

void gui::controls::NestedScrolling(const std::initializer_list<wxWindow *> &ctrls)
{
    for (auto *ctrl : ctrls)
    {
        if (ctrl == nullptr)
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
                bool canScrollToBottom = pos <= range - cntPage - 1;
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

void gui::controls::Select(wxWindow *ctrl, int selection)
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

void gui::controls::SetValue(wxSpinCtrlDouble *ctrl, double value)
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
