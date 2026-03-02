#include "database_panel.h"

#include "base/log.h"
#include "base/strings/string_util.h"
#include "ui/bindings.h"
#include "ui/utils.h"

#include <utf8cpp/utf8.h>

void ui::DatabasePanel::InitializeMoveTab()
{
    ApplyNestedScrolling({
        m_moveContainer,

        m_movePrimaryTypeComboBox,
        m_movePrimaryPowerSpinCtrl,
        m_movePrimaryAccuracySpinCtrl,
        m_movePrimaryPPSpinCtrl,

        m_moveEffectTypeComboBox,
        m_moveEffectValueSpinCtrl,
    });

    // 목록
    {
        BindControlSelection(this, m_moveList, m_selectedMove);

        // 롬을 다시 열었을 때, 선택 초기화...
        m_pokegold.Rom().Opened().Subscribe(this, [this](const bool &) {
            m_selectedMove.Update(-1);
        });

        // 항목 이름 갱신
        m_pokegold.Data().MoveNameUpdated().Subscribe(this, [this](const int &idx) {
            m_moveList->Freeze();

            if (m_moveList->GetCount() == 0)
            {
                for (size_t i = 0; i < 251; i++)
                    m_moveList->Append(wxT(""));
            }

            if (idx == -1)
            {
                for (size_t i = 0; i < 251; i++)
                {
                    auto &e = m_pokegold.Data().Moves()[i];
                    auto name = e.Name.ToEditorWxString();
                    m_moveList->SetString(i, name);
                }
            }
            else
            {
                auto &e = m_pokegold.Data().Moves()[idx];
                auto name = e.Name.ToEditorWxString();
                m_moveList->SetString(idx, name);
            }

            m_moveList->Thaw();
        });

        // 항목 선택 처리
        m_selectedMove.Subscribe(this, [this](const int &idx) {
            base::Log(TAG, "move selected (index={})", idx);

            m_eventGuard([&] {
                m_moveContainer->Enable(idx != -1);

                if (idx == -1)
                {
                    m_movePrimaryNumberText->SetValue(wxT("-"));
                    m_movePrimaryNameText->SetValue(wxT(""));
                    m_movePrimaryTypeComboBox->Select(-1);
                    SetValueSpinCtrlDouble(m_movePrimaryPowerSpinCtrl, 0.0);
                    SetValueSpinCtrlDouble(m_movePrimaryAccuracySpinCtrl, 0.0);
                    SetValueSpinCtrlDouble(m_movePrimaryPPSpinCtrl, 0.0);
                    m_movePrimaryDescriptionText->SetValue(wxT(""));

                    m_moveEffectTypeComboBox->Select(-1);
                    SetValueSpinCtrlDouble(m_moveEffectValueSpinCtrl, 0.0);
                }
                else
                {
                    auto &e = m_pokegold.Data().Moves()[idx];

                    m_movePrimaryNumberText->SetValue(wxString::Format("%d", e.Id));
                    m_movePrimaryNameText->SetValue(e.Name.ToEditorWxString());
                    m_movePrimaryTypeComboBox->Select(e.Type);
                    SetValueSpinCtrlDouble(m_movePrimaryPowerSpinCtrl, e.Power);
                    SetValueSpinCtrlDouble(m_movePrimaryAccuracySpinCtrl, e.Accuracy);
                    SetValueSpinCtrlDouble(m_movePrimaryPPSpinCtrl, e.PP);
                    m_movePrimaryDescriptionText->SetValue(e.Description.ToEditorWxString());

                    m_moveEffectTypeComboBox->Select(e.Effect);
                    SetValueSpinCtrlDouble(m_moveEffectValueSpinCtrl, e.EffectChance);
                }
            });

            m_moveList->SetFocus();
        });
    }

    // 타입 이름 갱신
    m_pokegold.Data().TypeNameUpdated().Subscribe(this, [this](const int &idx) {
        m_movePrimaryTypeComboBox->Freeze();

        if (m_movePrimaryTypeComboBox->GetCount() == 0)
        {
            for (size_t i = 0; i < 28; i++)
                m_movePrimaryTypeComboBox->Append(wxT(""));
        }

        if (idx == -1)
        {
            for (size_t i = 0; i < 28; i++)
            {
                auto &e = m_pokegold.Data().Types()[i];
                auto name = e.Name.ToEditorWxString();
                m_movePrimaryTypeComboBox->SetString(i, name);
            }
        }
        else
        {
            auto &e = m_pokegold.Data().Types()[idx];
            auto name = e.Name.ToEditorWxString();
            m_movePrimaryTypeComboBox->SetString(idx, name);
        }

        m_movePrimaryTypeComboBox->Thaw();
    });

    InitializeMoveEditor();
}

void ui::DatabasePanel::InitializeMoveEditor()
{
    // 기본 정보
    {
        // 이름
        m_movePrimaryNameText->Bind(wxEVT_TEXT, [this](wxCommandEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto str = m_movePrimaryNameText->GetValue().utf8_string();
            if (pokegold::String::IsCharmapString(str))
            {
                int selected = *m_selectedMove;
                auto &e = m_pokegold.Data().Moves()[selected];
                e.Name = str + "[50]";
                m_pokegold.Data().MoveNameUpdated()(selected);
                m_pokegold.Rom().NotifyRomChanged();
            }
        });

        // 타입
        m_movePrimaryTypeComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Moves()[*m_selectedMove];
            e.Type = m_movePrimaryTypeComboBox->GetSelection();
            m_pokegold.Rom().NotifyRomChanged();
        });

        // 위력
        m_movePrimaryPowerSpinCtrl->Bind(wxEVT_SPINCTRLDOUBLE, [this](wxSpinDoubleEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Moves()[*m_selectedMove];
            e.Power = u8(m_movePrimaryPowerSpinCtrl->GetValue());
            m_pokegold.Rom().NotifyRomChanged();
        });

        // 명중률
        m_movePrimaryAccuracySpinCtrl->Bind(wxEVT_SPINCTRLDOUBLE, [this](wxSpinDoubleEvent &ev) {
            ev.Skip();

            const auto percentage = wxString::Format(wxT("(%.2lf%%)"), m_movePrimaryAccuracySpinCtrl->GetValue() / 255.0 * 100.0);
            m_movePrimaryAccuracyPercentageLabel->SetLabelText(percentage);

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Moves()[*m_selectedMove];
            e.Accuracy = u8(m_movePrimaryAccuracySpinCtrl->GetValue());
            m_pokegold.Rom().NotifyRomChanged();
        });

        // PP
        m_movePrimaryPPSpinCtrl->Bind(wxEVT_SPINCTRLDOUBLE, [this](wxSpinDoubleEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Moves()[*m_selectedMove];
            e.PP = u8(m_movePrimaryPPSpinCtrl->GetValue());
            m_pokegold.Rom().NotifyRomChanged();
        });

        // 설명
        m_movePrimaryDescriptionText->Bind(wxEVT_TEXT, [this](wxCommandEvent &ev) {
            ev.Skip();

            auto str = m_movePrimaryDescriptionText->GetValue().utf8_string();
            const auto lines = base::Split(str, '\n');

            size_t maxLen = 0;
            for (const auto &line : lines)
                maxLen = std::max(maxLen, size_t(utf8::distance(line.begin(), line.end())));

            const auto label = wxString::Format(wxT("설명 (너비: %d/18)："), int(maxLen));
            m_movePrimaryDescriptionLabel->SetLabel(label);

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            if (pokegold::String::IsCharmapString(str))
            {
                auto &e = m_pokegold.Data().Moves()[*m_selectedMove];
                e.Description = str + "[50]";
                m_pokegold.Rom().NotifyRomChanged();
            }
        });
    }

    // 효과
    {
        // 타입
        m_moveEffectTypeComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Moves()[*m_selectedMove];
            e.Effect = m_moveEffectTypeComboBox->GetSelection();
            m_pokegold.Rom().NotifyRomChanged();
        });

        // 값
        m_moveEffectValueSpinCtrl->Bind(wxEVT_SPINCTRLDOUBLE, [this](wxSpinDoubleEvent &ev) {
            ev.Skip();

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().Moves()[*m_selectedMove];
            e.EffectChance = u8(m_moveEffectValueSpinCtrl->GetValue());
            m_pokegold.Rom().NotifyRomChanged();
        });
    }
}
