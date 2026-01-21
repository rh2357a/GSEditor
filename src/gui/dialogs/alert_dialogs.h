#ifndef _GUI_DIALOGS_ALERT_DIALOGS_H_
#define _GUI_DIALOGS_ALERT_DIALOGS_H_

#include <wx/wx.h>

#include <string>
#include <format>

namespace gui::dialogs {

template <typename... _Args>
inline int ShowAlert(wxWindow *parent, const std::string &title, std::format_string<_Args...> fmt, _Args &&...args)
{
    wxBell();

    const auto message = std::format(fmt, std::forward<_Args>(args)...);
    return wxMessageBox(wxString::FromUTF8(message), wxString::FromUTF8(title), wxCENTRE | wxOK | wxICON_INFORMATION, parent);
}

template <typename... _Args>
inline int ShowWarning(wxWindow *parent, const std::string &title, std::format_string<_Args...> fmt, _Args &&...args)
{
    wxBell();

    const auto message = std::format(fmt, std::forward<_Args>(args)...);
    return wxMessageBox(wxString::FromUTF8(message), wxString::FromUTF8(title), wxCENTRE | wxOK | wxICON_WARNING, parent);
}

template <typename... _Args>
inline int ShowError(wxWindow *parent, const std::string &title, std::format_string<_Args...> fmt, _Args &&...args)
{
    wxBell();

    const auto message = std::format(fmt, std::forward<_Args>(args)...);
    return wxMessageBox(wxString::FromUTF8(message), wxString::FromUTF8(title), wxCENTRE | wxOK | wxICON_ERROR, parent);
}

template <typename... _Args>
inline int ShowConfirm(wxWindow *parent, const std::string &title, std::format_string<_Args...> fmt, _Args &&...args)
{
    wxBell();

    const auto message = std::format(fmt, std::forward<_Args>(args)...);
    return wxMessageBox(wxString::FromUTF8(message), wxString::FromUTF8(title), wxCENTRE | wxYES_NO | wxICON_WARNING, parent);
}

template <typename... _Args>
inline int ShowYesNoCancel(wxWindow *parent, const std::string &title, std::format_string<_Args...> fmt, _Args &&...args)
{
    wxBell();

    const auto message = std::format(fmt, std::forward<_Args>(args)...);
    return wxMessageBox(wxString::FromUTF8(message), wxString::FromUTF8(title), wxCENTRE | wxYES_NO | wxCANCEL | wxICON_WARNING, parent);
}

} // namespace gui::dialogs

#endif
