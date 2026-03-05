#include "file_dialogs.h"

#include <optional>
#include <sstream>

std::optional<std::filesystem::path> ui::ShowOpenFileDialog(wxWindow *parent, const std::string &title, const std::vector<std::string> &filter)
{
    std::stringstream filterStream;
    for (size_t i = 0; i < filter.size(); i++)
    {
        const auto &e = filter[i];
        filterStream << e;

        if (i < filter.size() - 1)
            filterStream << '|';
    }

    wxFileDialog fileDialog(parent, wxString::FromUTF8(title), "", "", wxString::FromUTF8(filterStream.str()), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (fileDialog.ShowModal() == wxID_CANCEL)
        return std::nullopt;

    return fileDialog.GetPath().utf8_string();
}

std::optional<std::filesystem::path> ui::ShowSaveFileDialog(wxWindow *parent, const std::string &title, const std::vector<std::string> &filter)
{
    std::stringstream filterStream;
    for (size_t i = 0; i < filter.size(); i++)
    {
        const auto &e = filter[i];
        filterStream << e;

        if (i < filter.size() - 1)
            filterStream << '|';
    }

    wxFileDialog fileDialog(parent, wxString::FromUTF8(title), "", "", wxString::FromUTF8(filterStream.str()), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if (fileDialog.ShowModal() == wxID_CANCEL)
        return std::nullopt;

    return fileDialog.GetPath().utf8_string();
}
