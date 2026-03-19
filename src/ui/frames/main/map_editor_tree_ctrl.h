#pragma once

#include "base/functional/state.h"
#include "services/pokegold.h"
#include "services/pokegold/data/game_data.h"

#include <wx/treebase.h>
#include <wx/treectrl.h>
#include <wx/window.h>

namespace ui
{
    class MapEditorTreeCtrlItemData : public wxTreeItemData
    {
    private:
        bool m_isMapGroup;
        int m_index, m_subIndex;

    public:
        MapEditorTreeCtrlItemData(bool isMapGroup, int index, int subIndex)
            : wxTreeItemData(),
              m_isMapGroup(isMapGroup),
              m_index(index),
              m_subIndex(subIndex) {}

    public:
        bool IsMapGroup() const { return m_isMapGroup; }
        int GetIndex() const { return m_index; }
        int GetSubIndex() const { return m_subIndex; }
    };

    class MapEditorTreeCtrl : public wxTreeCtrl
    {
    private:
        inline static const auto TAG = "ui::MapEditorTreeCtrl";

        inline static int ICON_ID_MAP_GROUP = 0;
        inline static int ICON_ID_MAP_ITEM = 1;

    private:
        services::Pokegold &m_pokegold = services::Pokegold::Default();

        std::vector<int> m_iconIds;
        base::MutableState<pokegold::MapId> m_mapIdSelection = pokegold::MapId(0xff, 0xff, true);

    public:
        MapEditorTreeCtrl(wxWindow *parent,
                          wxWindowID id = wxID_ANY,
                          const wxPoint &pos = wxDefaultPosition,
                          const wxSize &size = wxDefaultSize,
                          long style = wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT,
                          const wxValidator &validator = wxDefaultValidator,
                          const wxString &name = wxASCII_STR(wxTreeCtrlNameStr));

    private:
        void OnMenuItemSelected(wxTreeEvent &ev);
        void OnMenuItemRightClick(wxTreeEvent &ev);
        void UpdateTree();

    public:
        base::State<pokegold::MapId> &GetMapIdSelectionState() { return m_mapIdSelection; }
    };
}
