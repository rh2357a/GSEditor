#pragma once

#include "ui/ui.h"

namespace ui
{
    class DatabasePanel : public DatabasePanelBase
    {
    public:
        DatabasePanel(wxWindow *parent,
                      wxWindowID id = wxID_ANY,
                      const wxPoint &pos = wxDefaultPosition,
                      const wxSize &size = wxSize(500, 300),
                      long style = wxTAB_TRAVERSAL,
                      const wxString &name = wxEmptyString)
            : DatabasePanelBase(parent, id, pos, size, style, name)
        {
        }
    };
}
