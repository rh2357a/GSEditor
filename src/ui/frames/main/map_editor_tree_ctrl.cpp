#include "map_editor_tree_ctrl.h"

#include "base/log.h"
#include "base/resources_embed.h"

#include <wx/treebase.h>

ui::MapEditorTreeCtrl::MapEditorTreeCtrl(wxWindow *parent,
                                         wxWindowID id,
                                         const wxPoint &pos,
                                         const wxSize &size,
                                         long style,
                                         const wxValidator &validator,
                                         const wxString &name)
    : wxTreeCtrl(parent, id, pos, size, style, validator, name)
{
    // 아이콘 등록
    {
        wxImageList *imageList = new wxImageList(16, 16, true);

        // ICON_ID_MAP_GROUP
        {
            wxIcon icon;
            icon.CopyFromBitmap(embed::GetMapGroupIconBitmap());
            m_iconIds.push_back(imageList->Add(icon));
        }

        // ICON_ID_MAP_ITEM
        {
            wxIcon icon;
            icon.CopyFromBitmap(embed::GetMapItemIconBitmap());
            m_iconIds.push_back(imageList->Add(icon));
        }

        AssignImageList(imageList);
    }

    // 롬을 다시 열 때, 목록을 갱신
    m_pokegold.IsOpenedState().Subscribe(this, [this](const bool &isOpened) {
        if (isOpened)
            UpdateTree();
    });

    Bind(wxEVT_TREE_SEL_CHANGED, &MapEditorTreeCtrl::OnMenuItemSelected, this);
    Bind(wxEVT_TREE_ITEM_RIGHT_CLICK, &MapEditorTreeCtrl::OnMenuItemRightClick, this);
}

void ui::MapEditorTreeCtrl::OnMenuItemSelected(wxTreeEvent &ev)
{
    ev.Skip();

    wxTreeItemId item = ev.GetItem();
    if (!item.IsOk())
        return;

    MapEditorTreeCtrlItemData *data = (MapEditorTreeCtrlItemData *)GetItemData(item);
    if (data == nullptr)
        return;

    base::Log(TAG, "map item selected (group={}, map={})", data->GetIndex(), data->GetSubIndex());
    if (!data->IsMapGroup())
        m_mapIdSelection.Update({u8(data->GetIndex()), u8(data->GetSubIndex()), false});
}

void ui::MapEditorTreeCtrl::OnMenuItemRightClick(wxTreeEvent &ev)
{
    ev.Skip();

    wxTreeItemId item = ev.GetItem();
    if (!item.IsOk())
        return;

    MapEditorTreeCtrlItemData *data = (MapEditorTreeCtrlItemData *)GetItemData(item);
    if (data == nullptr)
        return;

    base::Log(TAG, "open map item menu (group={}, map={})", data->GetIndex(), data->GetSubIndex());
    SelectItem(item, true);
}

void ui::MapEditorTreeCtrl::UpdateTree()
{
    Freeze();
    DeleteAllItems();

    auto rootId = AddRoot(wxT("맵"));

    for (size_t i = 0; i < m_pokegold.Data.Maps.MapGroups.size(); i++)
    {
        auto mapGroupId = AppendItem(rootId, wxString::Format(wxT("맵 %d (%d)"), int(i + 1), int(m_pokegold.Data.Maps.MapGroups[i].size())));
        SetItemImage(mapGroupId, ICON_ID_MAP_GROUP);
        SetItemData(mapGroupId, new MapEditorTreeCtrlItemData(true, i, -1));

        for (size_t j = 0; j < m_pokegold.Data.Maps.MapGroups[i].size(); j++)
        {
            auto mapItemId = AppendItem(mapGroupId, wxString::Format(wxT("%d"), int(j + 1)));
            SetItemImage(mapItemId, ICON_ID_MAP_ITEM);
            SetItemData(mapItemId, new MapEditorTreeCtrlItemData(false, i, j));
        }
    }

    Thaw();
}
