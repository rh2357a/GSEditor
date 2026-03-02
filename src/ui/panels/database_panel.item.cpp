#include "database_panel.h"

#include "base/log.h"
#include "base/strings/string_util.h"
#include "ui/bindings.h"
#include "ui/utils.h"

#include <utf8cpp/utf8.h>
#include <wx/event.h>
#include <wx/spinctrl.h>

void ui::DatabasePanel::InitializeItemTab()
{
    ApplyNestedScrolling({
        m_itemContainer,

        m_itemPrimaryGroupComboBox,
        m_itemPrimaryPriceSpinCtrl,

        m_itemFieldMenuComboBox,
        m_itemBattleMenuComboBox,

        m_itemEtcEffectComboBox,
        m_itemEtcRegisterComboBox,
        m_itemEtcValueSpinCtrl,
    });

    BindControlSelection(this, m_itemList, m_selectedItem);

    // 롬을 다시 열었을 때, 선택 초기화...
    m_pokegold.Rom().Opened().Subscribe(this, [this](const bool &) {
        m_selectedItem.Update(-1);
    });

    // 아이템 이름 갱신
    m_pokegold.Data().ItemNameUpdated().Subscribe(this, [this](const int &idx) {
        m_itemList->Freeze();

        if (m_itemList->GetCount() == 0)
        {
            for (size_t i = 0; i < 256; i++)
                m_itemList->Append(wxT(""));
        }

        if (idx == -1)
        {
            for (size_t i = 0; i < 256; i++)
            {
                auto &e = m_pokegold.Data().Items()[i];
                auto name = e.Name.ToEditorWxString();
                m_itemList->SetString(i, name);
            }
        }
        else
        {
            auto &e = m_pokegold.Data().Items()[idx];
            auto name = e.Name.ToEditorWxString();
            m_itemList->SetString(idx, name);
        }

        m_itemList->Thaw();
    });

    // 항목 선택 처리
    m_selectedItem.Subscribe(this, [this](const int &idx) {
        base::Log(TAG, "item selected (index={})", idx);

        m_eventGuard([&] {
            m_itemContainer->Enable(idx != -1);

            if (idx == -1)
            {
                m_itemPrimaryGroupComboBox->Select(-1);
                m_itemPrimaryNameText->SetValue(wxT(""));
                SetValueSpinCtrlDouble(m_itemPrimaryPriceSpinCtrl, 0.0);
                m_itemPrimaryDescriptionText->SetValue(wxT(""));

                m_itemFieldMenuComboBox->Select(-1);
                m_itemBattleMenuComboBox->Select(-1);

                m_itemEtcEffectComboBox->Select(-1);
                m_itemEtcRegisterComboBox->Select(-1);
                SetValueSpinCtrlDouble(m_itemEtcValueSpinCtrl, 0.0);
            }
            else
            {
                auto &e = m_pokegold.Data().Items()[idx];

                m_itemPrimaryGroupComboBox->Select(e.Pocket);
                m_itemPrimaryNameText->SetValue(e.Name.ToEditorWxString());
                SetValueSpinCtrlDouble(m_itemPrimaryPriceSpinCtrl, e.Price);
                m_itemPrimaryDescriptionText->SetValue(e.Description.ToEditorWxString());

                m_itemFieldMenuComboBox->Select(e.FieldMenu);
                m_itemBattleMenuComboBox->Select(e.BattleMenu);

                m_itemEtcEffectComboBox->Select(e.Effect);
                m_itemEtcRegisterComboBox->Select(e.Property >> 6);
                SetValueSpinCtrlDouble(m_itemEtcValueSpinCtrl, e.Parameter);
            }
        });

        m_itemList->SetFocus();
    });

    InitializeItemEditor();
}

void ui::DatabasePanel::InitializeItemEditor()
{
    // 기본 정보
    {
        // 아이템 분류
        m_itemPrimaryGroupComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Items()[*m_selectedItem];
            e.Pocket = m_itemPrimaryGroupComboBox->GetSelection();
            m_pokegold.Rom().NotifyRomChanged();
        });

        // 아이템 이름
        m_itemPrimaryNameText->Bind(wxEVT_TEXT, [this](wxCommandEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto str = m_itemPrimaryNameText->GetValue().utf8_string();
            if (pokegold::String::IsCharmapString(str))
            {
                int selected = *m_selectedItem;
                auto &e = m_pokegold.Data().Items()[selected];
                e.Name = str + "[50]";
                m_pokegold.Data().ItemNameUpdated()(selected);
                m_pokegold.Rom().NotifyRomChanged();
            }
        });

        // 아이템 가격
        m_itemPrimaryPriceSpinCtrl->Bind(wxEVT_SPINCTRLDOUBLE, [this](wxSpinDoubleEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Items()[*m_selectedItem];
            e.Price = u16(m_itemPrimaryPriceSpinCtrl->GetValue());
            m_pokegold.Rom().NotifyRomChanged();
        });

        // 아이템 설명
        m_itemPrimaryDescriptionText->Bind(wxEVT_TEXT, [this](wxCommandEvent &ev) {
            ev.Skip();

            auto str = m_itemPrimaryDescriptionText->GetValue().utf8_string();
            const auto lines = base::Split(str, '\n');

            size_t maxLen = 0;
            for (const auto &line : lines)
                maxLen = std::max(maxLen, size_t(utf8::distance(line.begin(), line.end())));

            const auto label = wxString::Format(wxT("설명 (너비: %d/18)："), int(maxLen));
            m_itemPrimaryDescriptionLabel->SetLabel(label);

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            if (pokegold::String::IsCharmapString(str))
            {
                auto &e = m_pokegold.Data().Items()[*m_selectedItem];
                e.Description = str + "[50]";
                m_pokegold.Rom().NotifyRomChanged();
            }
        });
    }

    // 메뉴
    {
        // 필드
        m_itemFieldMenuComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Items()[*m_selectedItem];
            e.FieldMenu = m_itemFieldMenuComboBox->GetSelection();
            m_pokegold.Rom().NotifyRomChanged();
        });

        // 배틀
        m_itemBattleMenuComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Items()[*m_selectedItem];
            e.BattleMenu = m_itemBattleMenuComboBox->GetSelection();
            m_pokegold.Rom().NotifyRomChanged();
        });
    }

    // 기타
    {
        // 지닌 도구 효과
        m_itemEtcEffectComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Items()[*m_selectedItem];
            e.Effect = m_itemEtcEffectComboBox->GetSelection();
            m_pokegold.Rom().NotifyRomChanged();
        });

        // 지닌 도구 효과
        m_itemEtcRegisterComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Items()[*m_selectedItem];
            e.Property = u8(m_itemEtcRegisterComboBox->GetSelection() << 6);
            m_pokegold.Rom().NotifyRomChanged();
        });

        // 값
        m_itemEtcValueSpinCtrl->Bind(wxEVT_SPINCTRLDOUBLE, [this](wxSpinDoubleEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Items()[*m_selectedItem];
            e.Parameter = u8(m_itemEtcValueSpinCtrl->GetValue());
            m_pokegold.Rom().NotifyRomChanged();
        });
    }
}
