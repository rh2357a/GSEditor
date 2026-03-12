#include "labeled_separator.h"

#include <wx/event.h>
#include <wx/sizer.h>

ui::LabeledSeparator::LabeledSeparator(wxWindow *parent,
                                       wxWindowID id,
                                       const wxString &label,
                                       const wxPoint &pos,
                                       const wxSize &size,
                                       long style,
                                       const wxString &name)
    : wxBoxSizer(wxHORIZONTAL)
{
    m_label = new wxStaticText(parent, wxID_ANY, label, wxDefaultPosition, wxDefaultSize, 0, name);
    Add(m_label, 0, wxRIGHT, 5);

    m_separator = new wxStaticLine(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    Add(m_separator, 1, wxALIGN_CENTER_VERTICAL | wxALL, 0);
}

void ui::LabeledSeparator::Wrap(int width)
{
    if (m_label != nullptr)
        m_label->Wrap(width);
}
