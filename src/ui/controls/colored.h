#pragma once

#include <wx/listctrl.h>
#include <wx/wx.h>

namespace ui
{
    inline wxColour OddItemColor(255, 255, 255);
    inline wxColour EvenItemColor(240, 248, 255);

    class ColoredListBox : public wxListBox
    {
    private:
        unsigned int m_lastItemCount = -1;

    public:
        ColoredListBox() : wxListBox()
        {
            InitItemColorEvent();
        }

        ColoredListBox(wxWindow *parent, wxWindowID id,
                       const wxPoint &pos = wxDefaultPosition,
                       const wxSize &size = wxDefaultSize,
                       int n = 0, const wxString choices[] = NULL,
                       long style = 0,
                       const wxValidator &validator = wxDefaultValidator,
                       const wxString &name = wxASCII_STR(wxListBoxNameStr))
            : wxListBox(parent, id, pos, size, n, choices, style | wxLB_OWNERDRAW, validator, name)
        {
            InitItemColorEvent();
        }

        ColoredListBox(wxWindow *parent, wxWindowID id,
                       const wxPoint &pos,
                       const wxSize &size,
                       const wxArrayString &choices,
                       long style = 0,
                       const wxValidator &validator = wxDefaultValidator,
                       const wxString &name = wxASCII_STR(wxListBoxNameStr))
            : wxListBox(parent, id, pos, size, choices, style | wxLB_OWNERDRAW, validator, name)
        {
            InitItemColorEvent();
        }

    private:
        void InitItemColorEvent()
        {
            Bind(wxEVT_PAINT, [this](wxPaintEvent &ev) {
                unsigned int cnt = GetCount();
                if (cnt != m_lastItemCount)
                {
                    m_lastItemCount = cnt;

                    for (size_t i = 0; i < cnt; i++)
                    {
                        const auto color = i % 2 == 0 ? EvenItemColor : OddItemColor;
                        GetItem(i)->SetBackgroundColour(color);
                    }
                }

                ev.Skip();
            });
        }
    };

    class ColoredCheckListBox : public wxCheckListBox
    {
    private:
        unsigned int m_lastItemCount = -1;

    public:
        ColoredCheckListBox() : wxCheckListBox()
        {
            InitItemColorEvent();
        }

        ColoredCheckListBox(wxWindow *parent, wxWindowID id,
                            const wxPoint &pos = wxDefaultPosition,
                            const wxSize &size = wxDefaultSize,
                            int n = 0, const wxString choices[] = NULL,
                            long style = 0,
                            const wxValidator &validator = wxDefaultValidator,
                            const wxString &name = wxASCII_STR(wxListBoxNameStr))
            : wxCheckListBox(parent, id, pos, size, n, choices, style | wxLB_OWNERDRAW, validator, name)
        {
            InitItemColorEvent();
        }

        ColoredCheckListBox(wxWindow *parent, wxWindowID id,
                            const wxPoint &pos,
                            const wxSize &size,
                            const wxArrayString &choices,
                            long style = 0,
                            const wxValidator &validator = wxDefaultValidator,
                            const wxString &name = wxASCII_STR(wxListBoxNameStr))
            : wxCheckListBox(parent, id, pos, size, choices, style | wxLB_OWNERDRAW, validator, name)
        {
            InitItemColorEvent();
        }

    private:
        void InitItemColorEvent()
        {
            Bind(wxEVT_LEAVE_WINDOW, [this](wxMouseEvent &ev) {
                SetSelection(wxNOT_FOUND);
                ev.Skip();
            });

            Bind(wxEVT_PAINT, [this](wxPaintEvent &ev) {
                unsigned int cnt = GetCount();
                if (cnt != m_lastItemCount)
                {
                    m_lastItemCount = cnt;

                    for (size_t i = 0; i < cnt; i++)
                    {
                        const auto color = i % 2 == 0 ? EvenItemColor : OddItemColor;
                        GetItem(i)->SetBackgroundColour(color);
                    }
                }

                ev.Skip();
            });
        }
    };

    class ColoredListCtrl : public wxListCtrl
    {
    public:
        ColoredListCtrl() : wxListCtrl()
        {
            InitItemColorEvent();
        }

        ColoredListCtrl(wxWindow *parent,
                        wxWindowID id = wxID_ANY,
                        const wxPoint &pos = wxDefaultPosition,
                        const wxSize &size = wxDefaultSize,
                        long style = wxLC_ICON,
                        const wxValidator &validator = wxDefaultValidator,
                        const wxString &name = wxASCII_STR(wxListCtrlNameStr))
            : wxListCtrl(parent, id, pos, size, style, validator, name)
        {
            InitItemColorEvent();
        }

    private:
        void InitItemColorEvent()
        {
            auto listCtrlFunc = [this](wxListEvent &ev) {
                for (int i = 0; i < GetItemCount(); i++)
                {
                    if (i % 2 == 0)
                        SetItemBackgroundColour(i, EvenItemColor);
                    else
                        SetItemBackgroundColour(i, OddItemColor);
                }

                ev.Skip();
            };

            Bind(wxEVT_LIST_DELETE_ITEM, listCtrlFunc);
            Bind(wxEVT_LIST_DELETE_ALL_ITEMS, listCtrlFunc);
            Bind(wxEVT_LIST_INSERT_ITEM, listCtrlFunc);
        }
    };
}
