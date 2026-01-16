#ifndef _GUI_CONTROLS_DATABASE_PANEL_H_
#define _GUI_CONTROLS_DATABASE_PANEL_H_

#include "gui/generated/gui_base.h"
#include "utils.h"

namespace gui::controls {

class DatabasePanel : public DatabasePanelBase
{
private:
    utils::subscriptions m_subscriptions;
    utils::event_guard m_eventGuard;

public:
    DatabasePanel(wxWindow *parent,
                  wxWindowID id = wxID_ANY,
                  const wxPoint &pos = wxDefaultPosition,
                  const wxSize &size = wxSize(500, 300),
                  long style = wxTAB_TRAVERSAL,
                  const wxString &name = wxEmptyString)
        : DatabasePanelBase(parent, id, pos, size, style, name)
    {
        InitPokemonTab();
    }

private:
    void InitPokemonTab();

private:
    void OnPokemonSelected(wxCommandEvent &event) override;
    void OnPokemonTMHMsButtonClick(wxCommandEvent &event) override;
};

} // namespace gui::controls

#endif
