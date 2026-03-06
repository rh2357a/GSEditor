#include "search_dialog.h"

#include "ui/controls/colored_list_box.h"
#include "ui/controls/colored_list_ctrl.h"
#include "ui/utils.h"

#include <wx/combobox.h>
#include <wx/event.h>
#include <wx/memory.h>
#include <wx/wx.h>

#include <string>

ui::internal::SearchDialog::SearchDialog(wxWindow *parent)
    : SearchDialogBase(parent),
      m_searchTimer(this)
{
    Bind(wxEVT_INIT_DIALOG, &SearchDialog::OnInit, this);
    Bind(wxEVT_TIMER, &SearchDialog::OnSearchTimer, this);

    m_list->Bind(wxEVT_LIST_ITEM_SELECTED, [this](wxCommandEvent &ev) {
        int idx = m_list->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        Selected = std::stoi(m_list->GetItemText(idx, 0).utf8_string()) - 1;
        m_confirmButton->Enable(true);
        ev.Skip();
    });

    ApplyListCtrlFixedHeader(m_list);
    m_list->AppendColumn(wxT("순번"));
    m_list->AppendColumn(wxT("내용"));

    m_confirmButton->Enable(false);
}

void ui::internal::SearchDialog::OnInit(wxInitDialogEvent &event)
{
    m_list->Freeze();

    int i = 0;
    for (const auto &e : Items)
    {
        m_list->InsertItem(i, "");
        m_list->SetItem(i, 0, wxString::Format("%d", i + 1));
        m_list->SetItem(i, 1, e);
        i++;
    }

    AutoListCtrlColumnWidth(m_list);

    m_list->Thaw();
}

void ui::internal::SearchDialog::OnKeywordTextChanged(wxCommandEvent &event)
{
    m_searchTimer.StartOnce(100);
}

void ui::internal::SearchDialog::OnSearchTimer(wxTimerEvent &event)
{
    m_list->Freeze();

    Selected = -1;
    m_confirmButton->Enable(false);
    m_list->DeleteAllItems();

    const auto &keyword = m_keywordText->GetValue();
    if (keyword == "")
    {
        int i = 0;
        for (const auto &e : Items)
        {
            m_list->InsertItem(i, "");
            m_list->SetItem(i, 0, wxString::Format("%d", i + 1));
            m_list->SetItem(i, 1, e);
            i++;
        }
    }
    else
    {
        int i = 0, insertIndex = 0;
        for (const auto &e : Items)
        {
            if (e.find(keyword) != std::string::npos)
            {
                m_list->InsertItem(insertIndex, "");
                m_list->SetItem(insertIndex, 0, wxString::Format("%d", i + 1));
                m_list->SetItem(insertIndex, 1, e);
                insertIndex++;
            }
            i++;
        }
    }

    m_list->Thaw();
}

void ui::internal::SearchDialog::OnConfirmButtonClick(wxCommandEvent &event)
{
    EndModal(wxID_OK);
}

void ui::internal::SearchDialog::OnCancelButtonClick(wxCommandEvent &event)
{
    EndModal(wxID_CANCEL);
}

void ui::internal::ApplyListSearchDialog(wxWindow *parent, const std::initializer_list<wxWindow *> &ctrls)
{
    for (auto *ctrl : ctrls)
    {
        if (ctrl == nullptr)
            continue;

        if (auto *list = wxDynamicCast(ctrl, ui::ColoredListBox))
        {
            list->Bind(wxEVT_RIGHT_DOWN, [parent, list](wxMouseEvent &ev) {
                ev.Skip();

                internal::SearchDialog dialog(parent);

                for (int i = 0; i < list->GetCount(); i++)
                    dialog.Items.push_back(list->GetString(i));

                if (dialog.ShowModal() == wxID_OK)
                {
                    list->SetSelection(dialog.Selected);

                    wxCommandEvent event(wxEVT_LISTBOX, list->GetId());
                    event.SetInt(dialog.Selected);
                    event.SetEventObject(list);
                    list->ProcessWindowEvent(event);
                }
            });
        }
        else if (auto *list = wxDynamicCast(ctrl, ui::ColoredCheckListBox))
        {
            list->Bind(wxEVT_RIGHT_DOWN, [parent, list](wxMouseEvent &ev) {
                ev.Skip();

                internal::SearchDialog dialog(parent);

                for (u32 i = 0; i < list->GetCount(); i++)
                    dialog.Items.push_back(list->GetString(i));

                if (dialog.ShowModal() == wxID_OK)
                {
                    list->SetSelection(dialog.Selected);

                    wxCommandEvent event(wxEVT_LISTBOX, list->GetId());
                    event.SetInt(dialog.Selected);
                    event.SetEventObject(list);
                    list->ProcessWindowEvent(event);
                }
            });
        }
        else if (auto *comboBox = wxDynamicCast(ctrl, wxComboBox))
        {
            comboBox->Bind(wxEVT_RIGHT_DOWN, [parent, comboBox](wxMouseEvent &ev) {
                ev.Skip();

                internal::SearchDialog dialog(parent);

                for (u32 i = 0; i < comboBox->GetCount(); i++)
                    dialog.Items.push_back(comboBox->GetString(i));

                if (dialog.ShowModal() == wxID_OK)
                {
                    comboBox->SetSelection(dialog.Selected);

                    wxCommandEvent event(wxEVT_COMBOBOX, comboBox->GetId());
                    event.SetInt(dialog.Selected);
                    event.SetEventObject(comboBox);
                    comboBox->ProcessWindowEvent(event);
                }
            });
        }
    }
}
