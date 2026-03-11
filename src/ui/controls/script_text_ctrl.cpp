#include "script_text_ctrl.h"

#include <wx/stc/stc.h>
#include <wx/string.h>

#include <set>
#include <vector>

namespace
{
    enum class TokenStyle : int
    {
        Default,
        Comment,
        Opcode,
        Flag,
        Label,
        Register,
        Number,
    };

    const std::set<wxString> k_opcodes = {
        "ld",
        "ldi",
        "ldd",
        "jp",
        "jr",
        "call",
        "ret",
        "reti",
        "inc",
        "dec",
        "add",
        "sub",
        "and",
        "or",
        "xor",
        "cp",
        "push",
        "pop",
    };

    const std::set<wxString> k_flagOpcodes = {
        "jp",
        "jr",
        "call",
    };

    const std::set<wxString> k_registers = {
        "a",
        "b",
        "c",
        "d",
        "e",
        "h",
        "l",
        "af",
        "bc",
        "de",
        "hl",
        "sp",
    };

    const std::set<wxString> k_flags = {
        "nz",
        "z",
        "nc",
        "c",
    };

    bool IsLabelLine(wxString &line)
    {
        wxString s = line.Trim(true).Trim(false);
        return !s.IsEmpty() && (s.EndsWith(":") || s.StartsWith("."));
    }
}

ui::ScriptTextCtrl::ScriptTextCtrl(wxWindow *parent,
                                   wxWindowID id,
                                   const wxPoint &pos,
                                   const wxSize &size,
                                   long style,
                                   const wxString &name)
    : wxStyledTextCtrl(parent, id, pos, size, style, name)
{
    SetLexer(wxSTC_LEX_CONTAINER);
    SetMarginType(0, wxSTC_MARGIN_NUMBER);
    SetMarginWidth(0, 40);

    AutoCompSetSeparator('\n');
    AutoCompSetIgnoreCase(true);
    AutoCompSetFillUps("");
    AutoCompStops("\n:]");
    AutoCompSetAutoHide(false);
    AutoCompSetDropRestOfWord(true);

    StyleSetForeground(int(TokenStyle::Comment), wxColour(0, 128, 0));
    StyleSetForeground(int(TokenStyle::Number), wxColour(255, 0, 255));
    StyleSetForeground(int(TokenStyle::Opcode), wxColour(0, 0, 255));
    StyleSetForeground(int(TokenStyle::Register), wxColour(128, 0, 128));
    StyleSetForeground(int(TokenStyle::Label), wxColour(0, 128, 128));

    Bind(wxEVT_STC_STYLENEEDED, &ScriptTextCtrl::OnStyleNeeded, this);
    Bind(wxEVT_STC_CHARADDED, &ScriptTextCtrl::OnCharAdded, this);
    Bind(wxEVT_KEY_DOWN, &ScriptTextCtrl::OnKeyDown, this);
}

void ui::ScriptTextCtrl::OnStyleNeeded(wxStyledTextEvent &ev)
{
    ev.Skip();

    size_t endPos = ev.GetPosition();
    size_t startPos = GetEndStyled();

    int startLine = LineFromPosition(startPos);
    int endLine = LineFromPosition(endPos);

    size_t lineStartPos = PositionFromLine(startLine);

    size_t lineEndPos;
    if (endLine + 1 < GetLineCount())
        lineEndPos = PositionFromLine(endLine + 1);
    else
        lineEndPos = GetTextLength();

    StartStyling(lineStartPos);
    SetStyling(lineEndPos - lineStartPos, int(TokenStyle::Default));

    StartStyling(lineStartPos);
    UpdateTokensForRange(startLine, endLine, true);
}

void ui::ScriptTextCtrl::OnCharAdded(wxStyledTextEvent &ev)
{
    ev.Skip();

    int line = GetCurrentLine();
    if (ev.GetKey() != '\n' || line <= 0)
    {
        int pos = GetCurrentPos();
        int line = LineFromPosition(pos);
        UpdateTokensForRange(line, line, false);
        ShowAutoComplete();
        return;
    }

    int prevLine = line - 1;
    wxString prevText = GetLine(prevLine).Trim(true).Trim(false);

    int baseIndent = 4;
    int indent = baseIndent;

    if (!IsLabelLine(prevText))
        indent = GetLineIndentation(prevLine);

    int lineStartPos = PositionFromLine(line);
    wxString spaces(indent, ' ');
    InsertText(lineStartPos, spaces);
    GotoPos(lineStartPos + indent);
}

void ui::ScriptTextCtrl::OnKeyDown(wxKeyEvent &ev)
{
    if (ev.GetKeyCode() == WXK_SPACE && ev.ControlDown())
    {
        if (ev.ControlDown())
        {
            int pos = GetCurrentPos();
            int line = LineFromPosition(pos);
            UpdateTokensForRange(line, line, false);
            ShowAutoComplete();
        }
        return;
    }

    ev.Skip();
}

void ui::ScriptTextCtrl::UpdateTokensForRange(int startLine, int endLine, bool applyStyle)
{
    for (int line = startLine; line <= endLine; line++)
    {
        if (m_lineTokens.count(line))
        {
            for (const auto &tok : m_lineTokens[line])
            {
                if (tok.Style == int(TokenStyle::Label))
                    m_labels.erase(tok.Text);
            }

            m_lineTokens.erase(line);
        }

        wxString lineText = GetLine(line);
        std::vector<ScriptTokenInfo> newTokens;

        bool lineStart = true;
        bool afterOpcode = false;
        bool afterFlagOpcode = false;

        size_t lineEnd = lineText.length();
        if (lineEnd > 0 && lineText[lineEnd - 1] == '\n')
            lineEnd--;

        size_t i = 0;
        while (i < lineEnd)
        {
            wxChar c = lineText[i];
            size_t start = i;

            // 주석
            if (c == ';')
            {
                i = lineEnd;
                newTokens.emplace_back(start, i - start, int(TokenStyle::Comment), lineText.Mid(start, i - start));
                break;
            }

            // 라벨 / opcodes+플래그 / 레지스터
            if (wxIsalpha(c) || c == '_' || c == '.')
            {
                while (i < lineEnd && (wxIsalnum(lineText[i]) || lineText[i] == '_' || lineText[i] == '.'))
                    i++;

                wxString token = lineText.Mid(start, i - start);
                wxString tokenLower = token.Lower();

                TokenStyle style = TokenStyle::Default;

                if (i < lineEnd && lineText[i] == ':')
                {
                    i++;

                    if (i < lineEnd && lineText[i] == ':')
                        i++;

                    style = TokenStyle::Label;
                    lineStart = false;
                    afterOpcode = false;
                    afterFlagOpcode = false;
                    m_labels.insert(token);
                }
                else if (lineStart && k_opcodes.count(tokenLower))
                {
                    style = TokenStyle::Opcode;
                    lineStart = false;

                    if (k_flagOpcodes.count(tokenLower))
                        afterFlagOpcode = true;
                    else
                        afterOpcode = true;
                }
                else if (afterOpcode && k_registers.count(tokenLower))
                {
                    style = TokenStyle::Register;
                }
                else if (afterFlagOpcode && k_flags.count(tokenLower))
                {
                    style = TokenStyle::Flag;
                }

                newTokens.emplace_back((int)start, (int)(i - start), int(style), token);
                continue;
            }

            // 숫자
            if (wxIsdigit(c) || c == '$' || c == '%')
            {
                if (c == '$')
                {
                    i++;
                    while (i < lineEnd && wxIsxdigit(lineText[i]))
                        i++;
                }
                else if (c == '%')
                {
                    i++;
                    while (i < lineEnd && (lineText[i] == '0' || lineText[i] == '1'))
                        i++;
                }
                else
                {
                    while (i < lineEnd && wxIsdigit(lineText[i]))
                        i++;
                }

                newTokens.emplace_back((int)start, (int)(i - start), int(TokenStyle::Number), lineText.Mid(start, i - start));
                continue;
            }

            // 입력 중
            {
                i++;
                newTokens.emplace_back((int)start, (int)(i - start), int(TokenStyle::Default), lineText.Mid(start, i - start));
            }
        }

        m_lineTokens[line] = newTokens;

        if (!m_lineTokens[line].empty())
        {
            m_lineTokens[line][0].IsFirstOfLine = true;
            m_lineTokens[line].back().IsLastOfLine = true;
        }
    }

    if (applyStyle)
    {
        for (int line = startLine; line <= endLine; line++)
        {
            if (m_lineTokens.contains(line))
            {
                int lineStart = PositionFromLine(line);

                for (const auto &token : m_lineTokens[line])
                {
                    StartStyling(lineStart + token.Start);
                    SetStyling(token.Text.ToUTF8().length(), int(token.Style));
                }
            }
        }
    }
}

void ui::ScriptTextCtrl::ShowAutoComplete()
{
    size_t pos = GetCurrentPos();

    int line = LineFromPosition(pos);
    auto it = m_lineTokens.find(line);
    if (it == m_lineTokens.end())
        return;

    size_t posInLine = pos - PositionFromLine(line);
    size_t startPos = WordStartPosition(pos, true);
    size_t endPos = WordEndPosition(pos, true);
    size_t length = endPos - startPos;

    wxString inputToken = GetTextRange(startPos, pos);
    wxString inputTokenLower = inputToken.Lower();

    // 입력중인 토큰에 맞춰 찾기
    std::vector<wxString> candidates;
    {
        int currentTokenIndex = -1;
        for (size_t i = 0; i < m_lineTokens[line].size(); i++)
        {
            const auto &token = m_lineTokens[line][i];

            if (posInLine >= token.Start && posInLine < token.Start + token.Length)
            {
                currentTokenIndex = i;
                break;
            }

            if (posInLine == token.Start + token.Length)
            {
                currentTokenIndex = i;
            }
        }

        TokenStyle tokenStyle;
        if (currentTokenIndex == -1)
        {
            tokenStyle = TokenStyle::Opcode;
        }
        else
        {
            tokenStyle = TokenStyle(m_lineTokens[line][currentTokenIndex].Style);
            if (tokenStyle == TokenStyle::Default)
            {
                bool found = false;
                for (int i = 1;; i++)
                {
                    if (currentTokenIndex - i < 0)
                    {
                        found = true;
                        tokenStyle = TokenStyle::Default;
                        break;
                    }

                    auto &next = m_lineTokens[line][currentTokenIndex - i];
                    if (next.IsFirstOfLine || next.Style != int(TokenStyle::Default))
                    {
                        found = true;

                        if (k_flagOpcodes.count(next.Text))
                            tokenStyle = TokenStyle::Flag;
                        else if (k_flags.count(next.Text))
                            tokenStyle = TokenStyle::Register;
                        else
                            tokenStyle = TokenStyle(next.Style);

                        break;
                    }

                    if (next.IsLastOfLine)
                    {
                        found = true;
                        tokenStyle = TokenStyle::Default;
                        break;
                    }
                }

                if (found)
                {
                    if (tokenStyle == TokenStyle::Default)
                        tokenStyle = TokenStyle::Opcode;
                    else if (tokenStyle == TokenStyle::Opcode)
                        tokenStyle = TokenStyle::Register;
                }
            }
        }

        switch (tokenStyle)
        {
        default:
            break;

        case TokenStyle::Opcode:
            for (auto &flag : k_opcodes)
            {
                if (flag.Lower().StartsWith(inputTokenLower))
                    candidates.push_back(flag);
            }
            break;
        case TokenStyle::Flag:
            for (auto &flag : k_flags)
            {
                if (flag.Lower().StartsWith(inputTokenLower))
                    candidates.push_back(flag);
            }
            break;
        case TokenStyle::Register:
            for (auto &flag : k_registers)
            {
                if (flag.Lower().StartsWith(inputTokenLower))
                    candidates.push_back(flag);
            }
            break;
        }
    }

    if (candidates.empty())
        return;

    // 사용자에게 보여질 자동완성 목록을 종합
    wxString list;
    {
        std::sort(candidates.begin(), candidates.end());

        for (auto &s : candidates)
        {
            if (!list.IsEmpty())
                list += '\n';
            list += s;
        }
    }

    AutoCompShow(pos - startPos, list);
}
