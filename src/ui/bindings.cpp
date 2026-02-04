#include "bindings.h"

namespace
{
    wxEventTypeTag<wxCommandEvent> GetControlSelectionEvent(wxControlWithItemsBase *control)
    {
        if (control != nullptr)
        {
            if (auto *list = wxDynamicCast(control, wxListBox))
                return wxEVT_LISTBOX;
            else if (auto *combo = wxDynamicCast(control, wxComboBox))
                return wxEVT_COMBOBOX;
        }
        return wxEVT_ANY;
    }
}

void ui::BindCheckBoxValue(wxWindowBase *hostControl, wxCheckBoxBase *control, base::MutableState<bool> &state)
{
    if (control != nullptr)
    {
        control->SetValue(*state);

        auto guard = std::make_shared<base::Guard>();

        state.Subscribe(hostControl, [control, guard](const bool &val) {
            if (!(*guard).IsGuarded())
                control->SetValue(val);
        });

        control->Bind(wxEVT_CHECKBOX, [control, &state, guard](wxCommandEvent &ev) {
            if (!(*guard).IsGuarded())
            {
                (*guard)([control, &state] {
                    state.Update(control->IsChecked());
                });
            }

            ev.Skip();
        });
    }
}

void ui::BindTextBoxText(wxWindowBase *hostControl, wxTextCtrlBase *control, base::MutableState<wxString> &state)
{
    if (control != nullptr)
    {
        control->SetValue(*state);

        auto guard = std::make_shared<base::Guard>();

        state.Subscribe(hostControl, [control, guard](const wxString &val) {
            if (!(*guard).IsGuarded())
                control->SetValue(val);
        });

        control->Bind(wxEVT_TEXT, [control, &state, guard](wxCommandEvent &ev) {
            if (!(*guard).IsGuarded())
            {
                (*guard)([control, &state] {
                    state.Update(control->GetValue());
                });
            }

            ev.Skip();
        });
    }
}

void ui::BindControlSelection(wxWindowBase *hostControl, wxControlWithItemsBase *control, base::MutableState<int> &state)
{
    const auto event = GetControlSelectionEvent(control);
    if (event != wxEVT_ANY)
    {
        control->SetSelection(*state);

        auto guard = std::make_shared<base::Guard>();
        auto latestCount = std::make_shared<int>(0);

        control->Bind(wxEVT_PAINT, [control, &state, latestCount, guard](wxPaintEvent &ev) {
            if (!(*guard).IsGuarded())
            {
                int currentCount = control->GetCount();
                if (*latestCount != currentCount)
                {
                    *latestCount = currentCount;
                    control->SetSelection(*state);
                }
            }

            ev.Skip();
        });

        state.Subscribe(hostControl, [control, guard](const int &val) {
            if (!(*guard).IsGuarded())
                control->SetSelection(val);
        });

        control->Bind(event, [control, &state, guard](wxCommandEvent &ev) {
            if (!(*guard).IsGuarded())
            {
                (*guard)([control, &state] {
                    state.Update(control->GetSelection());
                });
            }

            ev.Skip();
        });
    }
}

void ui::BindControlSelection(wxWindowBase *hostControl, wxListCtrl *control, base::MutableState<int> &state)
{
    if (control != nullptr)
    {
        control->SetItemState(*state, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);

        auto guard = std::make_shared<base::Guard>();

        auto itemChangedEvent = [control, &state, guard](wxListEvent &ev) {
            if (!(*guard).IsGuarded())
                control->SetItemState(*state, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
            ev.Skip();
        };

        control->Bind(wxEVT_LIST_DELETE_ITEM, itemChangedEvent);
        control->Bind(wxEVT_LIST_DELETE_ALL_ITEMS, itemChangedEvent);
        control->Bind(wxEVT_LIST_INSERT_ITEM, itemChangedEvent);

        state.Subscribe(hostControl, [control, guard](const int &val) {
            if (!(*guard).IsGuarded())
                control->SetItemState(val, val == -1 ? 0 : wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
        });

        control->Bind(wxEVT_LIST_ITEM_SELECTED, [control, &state, guard](wxCommandEvent &ev) {
            if (!(*guard).IsGuarded())
            {
                (*guard)([control, &state] {
                    state.Update(control->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED));
                });
            }

            ev.Skip();
        });
    }
}
