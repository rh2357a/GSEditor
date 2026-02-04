#pragma once

#include <wx/wx.h>

#include <string>
#include <format>

namespace ui
{
    enum class MessageBoxResult
    {
        Yes,
        No,
        Cancel,
    };

    template <typename... _Args>
    inline void ShowAlertDialog(wxWindow *parent, const std::string &title, std::format_string<_Args...> fmt, _Args &&...args)
    {
        wxBell();

        const auto message = std::format(fmt, std::forward<_Args>(args)...);
        wxMessageBox(wxString::FromUTF8(message), wxString::FromUTF8(title), wxCENTRE | wxOK | wxICON_INFORMATION, parent);
    }

    template <typename... _Args>
    inline void ShowWarningDialog(wxWindow *parent, const std::string &title, std::format_string<_Args...> fmt, _Args &&...args)
    {
        wxBell();

        const auto message = std::format(fmt, std::forward<_Args>(args)...);
        wxMessageBox(wxString::FromUTF8(message), wxString::FromUTF8(title), wxCENTRE | wxOK | wxICON_WARNING, parent);
    }

    template <typename... _Args>
    inline void ShowErrorDialog(wxWindow *parent, const std::string &title, std::format_string<_Args...> fmt, _Args &&...args)
    {
        wxBell();

        const auto message = std::format(fmt, std::forward<_Args>(args)...);
        wxMessageBox(wxString::FromUTF8(message), wxString::FromUTF8(title), wxCENTRE | wxOK | wxICON_ERROR, parent);
    }

    template <typename... _Args>
    inline MessageBoxResult ShowYesNoDialog(wxWindow *parent, const std::string &title, std::format_string<_Args...> fmt, _Args &&...args)
    {
        wxBell();

        const auto message = std::format(fmt, std::forward<_Args>(args)...);
        const int result = wxMessageBox(wxString::FromUTF8(message), wxString::FromUTF8(title), wxCENTRE | wxYES_NO | wxICON_WARNING, parent);
        if (result == wxYES)
            return MessageBoxResult::Yes;
        return MessageBoxResult::No;
    }

    template <typename... _Args>
    inline MessageBoxResult ShowYesNoCancelDialog(wxWindow *parent, const std::string &title, std::format_string<_Args...> fmt, _Args &&...args)
    {
        wxBell();

        const auto message = std::format(fmt, std::forward<_Args>(args)...);
        const int result = wxMessageBox(wxString::FromUTF8(message), wxString::FromUTF8(title), wxCENTRE | wxYES_NO | wxCANCEL | wxICON_WARNING, parent);
        if (result == wxYES)
            return MessageBoxResult::Yes;
        else if (result == wxNO)
            return MessageBoxResult::No;
        return MessageBoxResult::Cancel;
    }
}
