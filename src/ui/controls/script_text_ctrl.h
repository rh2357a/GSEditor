#pragma once

#include <wx/event.h>
#include <wx/stc/stc.h>
#include <wx/wx.h>

#include <cstddef>
#include <unordered_set>
#include <vector>

namespace ui
{
    struct ScriptTokenInfo
    {
        size_t Start;
        size_t Length;
        int Style;
        wxString Text;
        bool IsFirstOfLine = false;
        bool IsLastOfLine = false;
    };

    class ScriptTextCtrl : public wxStyledTextCtrl
    {
    private:
        std::unordered_set<wxString> m_labels;
        std::unordered_map<int, std::vector<ScriptTokenInfo>> m_lineTokens;

    public:
        ScriptTextCtrl(wxWindow *parent,
                       wxWindowID id = wxID_ANY,
                       const wxPoint &pos = wxDefaultPosition,
                       const wxSize &size = wxDefaultSize,
                       long style = 0,
                       const wxString &name = wxSTCNameStr);

    private:
        void OnStyleNeeded(wxStyledTextEvent &ev);
        void OnCharAdded(wxStyledTextEvent &ev);
        void OnKeyDown(wxKeyEvent &ev);

        void UpdateTokensForRange(int startLine, int endLine, bool applyStyle);
        void ShowAutoComplete();
    };
}
