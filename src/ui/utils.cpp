#include "utils.h"

#include <commctrl.h>
#include <windows.h>
#include <wx/event.h>
#include <wx/object.h>
#include <wx/popupwin.h>
#include <wx/spinctrl.h>
#include <wx/vlbox.h>
#include <wx/wx.h>

#include <memory>

namespace
{
    class DestroyPopupTransientWindow : public wxPopupTransientWindow
    {
    public:
        DestroyPopupTransientWindow() : wxPopupTransientWindow() {}
        DestroyPopupTransientWindow(wxWindow *parent, int style = wxBORDER_NONE) : wxPopupTransientWindow(parent, style) {}

    private:
        void OnDismiss() override
        {
            Destroy();
        }
    };
}

void ui::ApplyListCtrlFixedHeader(wxListCtrl *ctrl)
{
    HWND listViewHwnd = ctrl->GetHWND();
    HWND headerHwnd = (HWND)::SendMessage(listViewHwnd, LVM_GETHEADER, 0, 0);
    LONG headerStyle = ::GetWindowLong(headerHwnd, GWL_STYLE);
    // headerStyle |= HDS_NOSIZING;
    headerStyle &= ~HDS_DRAGDROP;
    ::SetWindowLong(headerHwnd, GWL_STYLE, headerStyle);
}

void ui::AutoListCtrlColumnWidth(wxListCtrl *ctrl)
{
    for (int i = 0; i < ctrl->GetColumnCount(); i++)
        ctrl->SetColumnWidth(i, wxLIST_AUTOSIZE_USEHEADER);
}

void ui::ShowDropdownPopup(wxWindow *parent, wxWindow *popupCtrl)
{
    DestroyPopupTransientWindow *popupWindow = new DestroyPopupTransientWindow(parent, wxBORDER_SIMPLE | wxPU_CONTAINS_CONTROLS);
    popupCtrl->Reparent(popupWindow);

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(popupCtrl, 1, wxEXPAND);
    popupWindow->SetSizerAndFit(sizer);

    wxPoint screenPos = parent->ClientToScreen(wxPoint(0, 0));
    {
        int popupHeight = popupWindow->GetSize().GetHeight();
        int parentHeight = parent->GetSize().GetHeight();

        wxRect screenRect = wxGetClientDisplayRect();
        if (screenPos.y + parentHeight + popupHeight > screenRect.GetBottom())
            screenPos.y -= popupHeight;
        else
            screenPos.y += parentHeight;
    }

    popupWindow->Move(screenPos);
    popupWindow->Popup();
}

void ui::ApplyNestedScrolling(const std::initializer_list<wxWindow *> &ctrls)
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
        else if (auto *list = wxDynamicCast(ctrl, wxVListBox))
        {
            list->Bind(wxEVT_MOUSEWHEEL, [list](wxMouseEvent &event) {
                size_t total = list->GetItemCount();
                if (total == 0)
                {
                    event.Skip();
                    return;
                }

                bool scrollUp = event.GetWheelRotation() > 0;
                bool scrollDown = event.GetWheelRotation() < 0;

                size_t first = list->GetVisibleBegin();
                size_t end = list->GetVisibleEnd();

                bool atTop = (first == 0);
                bool atBottom = (end >= total);

                if ((scrollUp && atTop) || (scrollDown && atBottom))
                {
                    wxMouseEvent evt(event);
                    evt.SetEventObject(list->GetParent());
                    list->GetParent()->GetEventHandler()->ProcessEvent(evt);
                    return;
                }

                event.Skip();
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

void ui::SetValueSpinCtrlDouble(wxSpinCtrlDouble *ctrl, double value)
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

void ui::FixBorderThemeBug(wxWindow *ctrl)
{
    if (ctrl != nullptr)
    {
        auto lastEnabled = std::make_shared<bool>(false);
        ctrl->Bind(wxEVT_UPDATE_UI, [ctrl, lastEnabled](wxUpdateUIEvent &ev) {
            bool isEnabled = ctrl->IsEnabled();
            if (isEnabled != *lastEnabled)
            {
                *lastEnabled = isEnabled;
                ::RedrawWindow(ctrl->GetHandle(), nullptr, nullptr, RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW);
            }

            ev.Skip();
        });
    }
}
