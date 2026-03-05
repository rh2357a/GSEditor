#include "database_panel.h"

#include "base/files/bitmap.h"
#include "base/log.h"
#include "services/pokegold/data/game_data.h"
#include "ui/bindings.h"
#include "ui/dialogs/file_dialogs.h"
#include "ui/dialogs/message_box.h"

#include <format>

void ui::DatabasePanel::InitializeTrainerGroupTab()
{
    ApplyListSearch(this, {m_trainerGroupList});

    BindControlSelection(this, m_trainerGroupList, m_selectedTrainerGroup);

    // 롬을 다시 열었을 때, 선택 초기화...
    m_pokegold.Rom().Opened().Subscribe(this, [this](const bool &) {
        m_selectedTrainerGroup.Update(-1);
    });

    // 목록 갱신
    m_pokegold.Data().TrainerGroupUpdated().Subscribe(this, [this](const int &) {
        m_trainerGroupList->Freeze();

        if (m_trainerGroupList->GetCount() == 0)
        {
            for (int i = 0; i < 67; i++)
                m_trainerGroupList->Append(wxT(""));
        }

        for (int i = 0; i < 67; i++)
        {
            auto &e = m_pokegold.Data().TrainerGroups()[i];
            auto str = std::format("{:02} [{}]", i + 1, e.Name.ToEditorString());
            m_trainerGroupList->SetString(i, wxString::FromUTF8(str));
        }

        // 67번 이미지 경고 라벨
        auto &group9 = m_pokegold.Data().TrainerGroups()[9 - 1];
        auto warnLabel = std::format("'09 [{}]' 항목의 이미지를 편집해 주세요.", group9.Name.ToEditorString());
        m_trainerGroupImageWarningLabel->SetLabel(wxString::FromUTF8(warnLabel));

        m_trainerGroupList->Thaw();
    });

    // 선택
    m_selectedTrainerGroup.Subscribe(this, [this](const int &idx) {
        base::Log(TAG, "trainer group selected (index={})", idx);

        m_eventGuard([this, idx] {
            m_trainerGroupContainer->Enable(idx != -1);

            if (idx != -1)
                m_trainerGroupNameText->SetValue(m_pokegold.Data().TrainerGroups()[idx].Name.ToEditorWxString());

            UpdateTrainerGroupImages();
        });

        m_trainerGroupList->SetFocus();
    });

    // 이름 변경 처리
    m_trainerGroupNameText->Bind(wxEVT_TEXT, [this](wxCommandEvent &ev) {
        ev.Skip();

        if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
            return;

        auto str = m_trainerGroupNameText->GetValue().utf8_string();
        if (pokegold::String::IsCharmapString(str))
        {
            int selected = *m_selectedTrainerGroup;
            auto &e = m_pokegold.Data().TrainerGroups()[selected];
            e.Name = str + "[50]";

            m_pokegold.Data().TrainerGroupUpdated()(selected);
            m_pokegold.Rom().NotifyRomChanged();
        }
    });

    // 이미지 변경 처리
    m_trainerGroupImage->ImportRequested().Subscribe(this, [this] {
        const auto path = ShowOpenFileDialog(this, "이미지 교체...", {"png 파일|*.png"});
        if (path.has_value())
        {
            auto result = base::ImportIndexedPngFile(*path);
            if (result == base::ImportIndexedPngResult::PngError)
            {
                ShowErrorDialog(this, "알림", "png 파일의 형식이 올바르지 않습니다.");
                return;
            }

            const auto size = result.GetBitmap().GetSize();
            if (!(size.x == 56 && size.y == 56))
            {
                ShowErrorDialog(this, "알림", "앞모습의 이미지는 56x56으로 맞춰주세요.");
                return;
            }

            auto &e = m_pokegold.Data().TrainerGroups()[*m_selectedTrainerGroup];
            e.Image = result.Get2bppData();
            e.Colors[0] = result.GetPalette()[1];
            e.Colors[1] = result.GetPalette()[2];

            m_pokegold.Data().TrainerGroupUpdated()(*m_selectedTrainerGroup);
            m_pokegold.Rom().NotifyRomChanged();

            UpdateTrainerGroupImages();
        }
    });

    // 색상 변경 처리
    {
        m_trainerGroupColor_1->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().TrainerGroups()[*m_selectedTrainerGroup];
            e.Colors[0].R(newColor.Red());
            e.Colors[0].G(newColor.Green());
            e.Colors[0].B(newColor.Blue());

            m_pokegold.Data().TrainerGroupUpdated()(*m_selectedTrainerGroup);
            m_pokegold.Rom().NotifyRomChanged();

            UpdateTrainerGroupImages();
        });

        m_trainerGroupColor_2->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &e = m_pokegold.Data().TrainerGroups()[*m_selectedTrainerGroup];
            e.Colors[1].R(newColor.Red());
            e.Colors[1].G(newColor.Green());
            e.Colors[1].B(newColor.Blue());

            m_pokegold.Data().TrainerGroupUpdated()(*m_selectedTrainerGroup);
            m_pokegold.Rom().NotifyRomChanged();

            UpdateTrainerGroupImages();
        });
    }
}

void ui::DatabasePanel::UpdateTrainerGroupImages()
{
    m_eventGuard([&] {
        int index = *m_selectedTrainerGroup;
        if (index == -1 || index == 67 - 1)
        {
            m_trainerGroupImageContainer->SetSelection(index == 67 - 1 ? 1 : 0);

            m_trainerGroupImage->Clear();
            m_trainerGroupColor_1->SetColor(*wxWHITE);
            m_trainerGroupColor_2->SetColor(*wxWHITE);
        }
        else
        {
            m_trainerGroupImageContainer->SetSelection(0);

            auto &e = m_pokegold.Data().TrainerGroups()[index];
            m_trainerGroupImage->SetData(pokegold::ImageDimensions::Size_56x56, e.Image, e.Colors);
            m_trainerGroupColor_1->SetColor(e.Colors[0].ToWxColor());
            m_trainerGroupColor_2->SetColor(e.Colors[1].ToWxColor());
        }
    });
}
