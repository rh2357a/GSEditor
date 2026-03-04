#include "database_panel.h"

#include "base/log.h"
#include "services/pokegold/data/game_data.h"
#include "ui/bindings.h"
#include "ui/dialogs/message_box.h"
#include "ui/dialogs/type_matchup_editor_dialog.h"
#include "ui/dialogs/type_weather_modifier_editor_dialog.h"
#include "ui/utils.h"

#include <algorithm>

void ui::DatabasePanel::InitializeTypeTab()
{
    ApplyNestedScrolling({
        m_typeMatchupList,
        m_typeWeatherModifierList,
    });

    BindControlSelection(this, m_typeList, m_selectedType);
    BindControlSelection(this, m_typeMatchupList, m_selectedTypeMatchup);
    BindControlSelection(this, m_typeWeatherModifierList, m_selectedTypeWeatherModifier);

    // 롬을 다시 열었을 때, 선택 초기화...
    m_pokegold.Rom().Opened().Subscribe(this, [this](const bool &) {
        m_selectedType.Update(-1);
    });

    // 목록 갱신
    m_pokegold.Data().TypeNameUpdated().Subscribe(this, [this](const int &) {
        m_typeList->Freeze();

        if (m_typeList->GetCount() == 0)
        {
            for (int i = 0; i < 28; i++)
                m_typeList->Append(wxT(""));
        }

        for (int i = 0; i < 28; i++)
        {
            auto &e = m_pokegold.Data().Types()[i];
            m_typeList->SetString(i, e.Name.ToEditorWxString());
        }

        m_typeList->Thaw();
    });

    // 선택
    m_selectedType.Subscribe(this, [this](const int &idx) {
        base::Log(TAG, "type selected (index={})", idx);

        m_eventGuard([this, idx] {
            m_typeContainer->Enable(idx != -1);

            if (idx == -1)
                m_typeNameText->SetValue(wxT(""));
            else
                m_typeNameText->SetValue(m_pokegold.Data().Types()[idx].Name.ToEditorWxString());
        });

        UpdateTypeMatchups();

        m_typeList->SetFocus();
    });

    // 이름 변경 처리
    m_typeNameText->Bind(wxEVT_TEXT, [this](wxCommandEvent &ev) {
        ev.Skip();

        if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
            return;

        auto str = m_typeNameText->GetValue().utf8_string();
        if (pokegold::String::IsCharmapString(str))
        {
            int selected = *m_selectedType;
            auto &e = m_pokegold.Data().Types()[selected];
            e.Name = str + "[50]";

            m_pokegold.Data().TypeNameUpdated()(selected);
            m_pokegold.Rom().NotifyRomChanged();
        }
    });

    // 상성 목록 설정
    {
        m_typeMatchupList->AppendColumn(wxT("공격 대상 타입"));
        m_typeMatchupList->AppendColumn(wxT("효과"));
        m_typeMatchupList->AppendColumn(wxT("비고"));
        ApplyListCtrlFixedHeader(m_typeMatchupList);
        AutoListCtrlColumnWidth(m_typeMatchupList);

        auto listCtrlFunc = [this] {
            int selection = *m_selectedTypeMatchup;
            int count = m_typeMatchupList->GetItemCount();
            m_typeMatchupsEditButton->Enable(selection != -1);
            m_typeMatchupsRemoveButton->Enable(selection != -1);
            m_typeMatchupsAddButton->Enable(count < 28);
            m_typeMatchupsClearButton->Enable(count > 0);
        };

        m_typeMatchupList->Bind(wxEVT_LIST_DELETE_ITEM, [listCtrlFunc](wxListEvent &ev) { ev.Skip(); listCtrlFunc(); });
        m_typeMatchupList->Bind(wxEVT_LIST_DELETE_ALL_ITEMS, [listCtrlFunc](wxListEvent &ev) { ev.Skip(); listCtrlFunc(); });
        m_typeMatchupList->Bind(wxEVT_LIST_INSERT_ITEM, [listCtrlFunc](wxListEvent &ev) { ev.Skip(); listCtrlFunc(); });
        m_selectedTypeMatchup.Subscribe(this, [listCtrlFunc] { listCtrlFunc(); });
    }

    // 날씨 보정 목록 설정
    {
        m_typeWeatherModifierList->AppendColumn(wxT("날씨"));
        m_typeWeatherModifierList->AppendColumn(wxT("보정 내용"));
        ApplyListCtrlFixedHeader(m_typeWeatherModifierList);
        AutoListCtrlColumnWidth(m_typeWeatherModifierList);

        auto listCtrlFunc = [this] {
            int selection = *m_selectedTypeWeatherModifier;
            int count = m_typeWeatherModifierList->GetItemCount();
            m_typeWeatherModifiersEditButton->Enable(selection != -1);
            m_typeWeatherModifiersRemoveButton->Enable(selection != -1);
            m_typeWeatherModifiersAddButton->Enable(count < 6);
            m_typeWeatherModifiersClearButton->Enable(count > 0);
        };

        m_typeWeatherModifierList->Bind(wxEVT_LIST_DELETE_ITEM, [listCtrlFunc](wxListEvent &ev) { ev.Skip(); listCtrlFunc(); });
        m_typeWeatherModifierList->Bind(wxEVT_LIST_DELETE_ALL_ITEMS, [listCtrlFunc](wxListEvent &ev) { ev.Skip(); listCtrlFunc(); });
        m_typeWeatherModifierList->Bind(wxEVT_LIST_INSERT_ITEM, [listCtrlFunc](wxListEvent &ev) { ev.Skip(); listCtrlFunc(); });
        m_selectedTypeWeatherModifier.Subscribe(this, [listCtrlFunc] { listCtrlFunc(); });
    }
}

void ui::DatabasePanel::UpdateTypeMatchups()
{
    m_typeMatchupList->DeleteAllItems();
    m_typeWeatherModifierList->DeleteAllItems();

    const int idx = *m_selectedType;
    if (idx == -1)
        return;

    auto &type = m_pokegold.Data().Types()[idx];

    int i = 0;
    for (const auto &matchup : type.TypeMatchups)
    {
        m_typeMatchupList->InsertItem(i, wxT(""));

        auto defenderTypeName = m_pokegold.Data().Types()[matchup.DefenderTypeId].Name.ToEditorWxString();
        m_typeMatchupList->SetItem(i, 0, defenderTypeName);

        switch (matchup.TypeEffectiveness)
        {
        case pokegold::TypeEffectiveness::NoEffect:
            m_typeMatchupList->SetItem(i, 1, wxT("효과가 없음"));
            break;
        case pokegold::TypeEffectiveness::NotVeryEffective:
            m_typeMatchupList->SetItem(i, 1, wxT("효과가 부족함"));
            break;
        case pokegold::TypeEffectiveness::SuperEffective:
            m_typeMatchupList->SetItem(i, 1, wxT("효과가 굉장함"));
            break;
        default:
            // No-op
            break;
        }

        if (matchup.IsForesight)
            m_typeMatchupList->SetItem(i, 2, wxT("꿰뚫어보기 상태일 때 효과 무시"));
        else
            m_typeMatchupList->SetItem(i, 2, wxT("-"));

        i++;
    }

    i = 0;
    for (const auto &modifier : type.WeatherModifiers)
    {
        m_typeWeatherModifierList->InsertItem(i, wxT(""));

        switch (modifier.Weather)
        {
        case pokegold::BattleWeather::Rain:
            m_typeWeatherModifierList->SetItem(i, 0, wxT("비바라기"));
            break;
        case pokegold::BattleWeather::Sandstorm:
            m_typeWeatherModifierList->SetItem(i, 0, wxT("모래바람"));
            break;
        case pokegold::BattleWeather::Sun:
            m_typeWeatherModifierList->SetItem(i, 0, wxT("쾌청"));
            break;
        default:
            // No-op
            break;
        }

        switch (modifier.TypeEffectiveness)
        {
        case pokegold::TypeEffectiveness::MoreEffective:
            m_typeWeatherModifierList->SetItem(i, 1, wxT("위력을 증가"));
            break;
        case pokegold::TypeEffectiveness::NotVeryEffective:
            m_typeWeatherModifierList->SetItem(i, 1, wxT("위력을 낮춤"));
            break;
        default:
            // No-op
            break;
        }

        i++;
    }

    AutoListCtrlColumnWidth(m_typeMatchupList);
    AutoListCtrlColumnWidth(m_typeWeatherModifierList);

    m_selectedTypeMatchup.Update(-1);
    m_selectedTypeWeatherModifier.Update(-1);
}

void ui::DatabasePanel::OnTypeMatchupsButtonClick(wxCommandEvent &event)
{
    event.Skip();

    if (!*m_pokegold.Rom().Opened() || *m_selectedType == -1)
        return;

    const int id = event.GetId();
    const int selectedTypeMatchupIdx = *m_selectedTypeMatchup;
    auto &type = m_pokegold.Data().Types()[*m_selectedType];

    if (id == wxID_ADD)
    {
        auto result = ShowTypeMatchupEditorDialog(this);
        if (result.has_value())
        {
            auto item = *result;
            item.AttackerTypeId = *m_selectedType;

            // 중복체크
            for (const auto &e : type.TypeMatchups)
            {
                if (e == item)
                    return;
            }

            type.TypeMatchups.push_back(item);

            UpdateTypeMatchups();
            m_pokegold.Rom().NotifyRomChanged();

            // 추가된 항목 선택처리
            auto foundResult = std::find(type.TypeMatchups.begin(), type.TypeMatchups.end(), item);
            int addedIdx = std::distance(type.TypeMatchups.begin(), foundResult);
            m_selectedTypeMatchup.Update(addedIdx);
        }
        return;
    }

    if (id == wxID_EDIT)
    {
        auto result = ShowTypeMatchupEditorDialog(this, type.TypeMatchups[selectedTypeMatchupIdx]);
        if (result.has_value())
        {
            auto item = *result;
            item.AttackerTypeId = *m_selectedType;

            // 중복체크
            for (const auto &e : type.TypeMatchups)
            {
                if (e == item)
                    return;
            }

            type.TypeMatchups[selectedTypeMatchupIdx] = item;

            UpdateTypeMatchups();
            m_pokegold.Rom().NotifyRomChanged();

            // 항목 선택처리
            auto foundResult = std::find(type.TypeMatchups.begin(), type.TypeMatchups.end(), item);
            int changedIdx = std::distance(type.TypeMatchups.begin(), foundResult);
            m_selectedTypeMatchup.Update(changedIdx);
        }
        return;
    }

    if (id == wxID_REMOVE)
    {
        auto result = ShowYesNoDialog(this, "삭제", "삭제하면 복구할 수 없습니다.\n계속하시겠습니까?");
        if (result == MessageBoxResult::Yes)
        {
            auto position = type.TypeMatchups.begin() + selectedTypeMatchupIdx;
            type.TypeMatchups.erase(position);

            UpdateTypeMatchups();
            m_pokegold.Rom().NotifyRomChanged();
        }
        return;
    }

    if (id == wxID_CLEAR)
    {
        auto result = ShowYesNoDialog(this, "전체 삭제", "삭제하면 복구할 수 없습니다.\n계속하시겠습니까?");
        if (result == MessageBoxResult::Yes)
        {
            type.TypeMatchups.clear();

            UpdateTypeMatchups();
            m_pokegold.Rom().NotifyRomChanged();
        }
        return;
    }
}

void ui::DatabasePanel::OnTypeWeatherModifiersButtonClick(wxCommandEvent &event)
{
    event.Skip();

    if (!*m_pokegold.Rom().Opened() || *m_selectedType == -1)
        return;

    const int id = event.GetId();
    const int selectedTypeWeatherModifierIdx = *m_selectedTypeWeatherModifier;
    auto &type = m_pokegold.Data().Types()[*m_selectedType];

    if (id == wxID_ADD)
    {
        auto result = ShowTypeWeatherModifierEditorDialog(this);
        if (result.has_value())
        {
            auto item = *result;
            item.TypeId = *m_selectedType;

            // 중복체크
            for (const auto &e : type.WeatherModifiers)
            {
                if (e == item)
                    return;
            }

            type.WeatherModifiers.push_back(item);

            UpdateTypeMatchups();
            m_pokegold.Rom().NotifyRomChanged();

            // 추가된 항목 선택처리
            auto foundResult = std::find(type.WeatherModifiers.begin(), type.WeatherModifiers.end(), item);
            int addedIdx = std::distance(type.WeatherModifiers.begin(), foundResult);
            m_selectedTypeWeatherModifier.Update(addedIdx);
        }
        return;
    }

    if (id == wxID_EDIT)
    {
        auto result = ShowTypeWeatherModifierEditorDialog(this, type.WeatherModifiers[selectedTypeWeatherModifierIdx]);
        if (result.has_value())
        {
            auto item = *result;
            item.TypeId = *m_selectedType;

            // 중복체크
            for (const auto &e : type.WeatherModifiers)
            {
                if (e == item)
                    return;
            }

            type.WeatherModifiers[selectedTypeWeatherModifierIdx] = item;

            UpdateTypeMatchups();
            m_pokegold.Rom().NotifyRomChanged();

            // 항목 선택처리
            auto foundResult = std::find(type.WeatherModifiers.begin(), type.WeatherModifiers.end(), item);
            int changedIdx = std::distance(type.WeatherModifiers.begin(), foundResult);
            m_selectedTypeWeatherModifier.Update(changedIdx);
        }
        return;
    }

    if (id == wxID_REMOVE)
    {
        auto result = ShowYesNoDialog(this, "삭제", "삭제하면 복구할 수 없습니다.\n계속하시겠습니까?");
        if (result == MessageBoxResult::Yes)
        {
            auto position = type.WeatherModifiers.begin() + selectedTypeWeatherModifierIdx;
            type.WeatherModifiers.erase(position);

            UpdateTypeMatchups();
            m_pokegold.Rom().NotifyRomChanged();
        }
        return;
    }

    if (id == wxID_CLEAR)
    {
        auto result = ShowYesNoDialog(this, "전체 삭제", "삭제하면 복구할 수 없습니다.\n계속하시겠습니까?");
        if (result == MessageBoxResult::Yes)
        {
            type.WeatherModifiers.clear();

            UpdateTypeMatchups();
            m_pokegold.Rom().NotifyRomChanged();
        }
        return;
    }
}
