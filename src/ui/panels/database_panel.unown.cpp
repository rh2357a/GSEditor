#include "database_panel.h"

#include "base/files/bitmap.h"
#include "base/log.h"
#include "services/pokegold/data/game_data.h"
#include "ui/bindings.h"
#include "ui/dialogs/file_dialogs.h"
#include "ui/dialogs/message_box.h"

void ui::DatabasePanel::InitializeUnownTab()
{
    // 목록 설정
    {
        BindControlSelection(this, m_unownList, m_selectedUnown);

        // 롬 열기 시, 선택 초기화...
        m_pokegold.Rom().Opened().Subscribe(this, [this](const bool &) {
            m_selectedUnown.Update(-1);
        });

        // 선택
        m_selectedUnown.Subscribe(this, [this](const int &idx) {
            base::Log(TAG, "unown selected (index={})", idx);
            m_unownContainer->Enable(idx != -1);
            UpdateUnownImages();
            m_unownList->SetFocus();
        });

        // 내용 초기화
        {
            m_unownList->Freeze();
            m_unownList->Clear();

            for (int i = 0; i < 26; i++)
                m_unownList->Append(wxString::Format("%c", char(i + 'A')));

            m_unownList->Thaw();
        }
    }

    // 이미지, 팔레트 설정
    {
        m_unownFrontImage->ImportRequested().Subscribe(this, [this] {
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
                if (!(size.x == 40 && size.y == 40))
                {
                    ShowErrorDialog(this, "알림", "앞모습의 이미지는 40x40으로 맞춰주세요.");
                    return;
                }

                auto &unown = m_pokegold.Data().UnownImages()[*m_selectedUnown];
                unown.FrontImage = result.Get2bppData();

                auto &pokemon = m_pokegold.Data().Pokemons()[200];
                pokemon.ImageDimensions = pokegold::ImageDimensions::Size_40x40;
                pokemon.Colors[0] = result.GetPalette()[1];
                pokemon.Colors[1] = result.GetPalette()[2];
                m_pokegold.Rom().NotifyRomChanged();

                UpdateUnownImages();
            }
        });

        m_unownBackImage->ImportRequested().Subscribe(this, [this] {
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
                if (!(size.x == 48 && size.y == 48))
                {
                    ShowErrorDialog(this, "알림", "뒷모습의 이미지는 48x48로 맞춰주세요.");
                    return;
                }

                auto &unown = m_pokegold.Data().UnownImages()[*m_selectedUnown];
                unown.BackImage = result.Get2bppData();

                auto &pokemon = m_pokegold.Data().Pokemons()[200];
                pokemon.Colors[0] = result.GetPalette()[1];
                pokemon.Colors[1] = result.GetPalette()[2];
                m_pokegold.Rom().NotifyRomChanged();

                UpdateUnownImages();
            }
        });

        m_unownShinyFrontImage->ImportRequested().Subscribe(this, [this] {
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
                if (!(size.x == 40 && size.y == 40))
                {
                    ShowErrorDialog(this, "알림", "앞모습의 이미지는 40x40으로 맞춰주세요.");
                    return;
                }

                auto &unown = m_pokegold.Data().UnownImages()[*m_selectedUnown];
                unown.FrontImage = result.Get2bppData();

                auto &pokemon = m_pokegold.Data().Pokemons()[200];
                pokemon.ImageDimensions = pokegold::ImageDimensions::Size_40x40;
                pokemon.ShinyColors[0] = result.GetPalette()[1];
                pokemon.ShinyColors[1] = result.GetPalette()[2];
                m_pokegold.Rom().NotifyRomChanged();

                UpdateUnownImages();
            }
        });

        m_unownShinyBackImage->ImportRequested().Subscribe(this, [this] {
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
                if (!(size.x == 48 && size.y == 48))
                {
                    ShowErrorDialog(this, "알림", "뒷모습의 이미지는 48x48로 맞춰주세요.");
                    return;
                }

                auto &unown = m_pokegold.Data().UnownImages()[*m_selectedUnown];
                unown.BackImage = result.Get2bppData();

                auto &pokemon = m_pokegold.Data().Pokemons()[200];
                pokemon.ShinyColors[0] = result.GetPalette()[1];
                pokemon.ShinyColors[1] = result.GetPalette()[2];
                m_pokegold.Rom().NotifyRomChanged();

                UpdateUnownImages();
            }
        });

        m_unownColor_1->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &unown = m_pokegold.Data().UnownImages()[*m_selectedUnown];
            auto &pokemon = m_pokegold.Data().Pokemons()[200];
            pokemon.Colors[0].R(newColor.Red());
            pokemon.Colors[0].G(newColor.Green());
            pokemon.Colors[0].B(newColor.Blue());
            m_pokegold.Rom().NotifyRomChanged();

            UpdateUnownImages();
        });

        m_unownColor_2->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &unown = m_pokegold.Data().UnownImages()[*m_selectedUnown];
            auto &pokemon = m_pokegold.Data().Pokemons()[200];
            pokemon.Colors[1].R(newColor.Red());
            pokemon.Colors[1].G(newColor.Green());
            pokemon.Colors[1].B(newColor.Blue());
            m_pokegold.Rom().NotifyRomChanged();

            UpdateUnownImages();
        });

        m_unownShinyColor_1->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &unown = m_pokegold.Data().UnownImages()[*m_selectedUnown];
            auto &pokemon = m_pokegold.Data().Pokemons()[200];
            pokemon.ShinyColors[0].R(newColor.Red());
            pokemon.ShinyColors[0].G(newColor.Green());
            pokemon.ShinyColors[0].B(newColor.Blue());
            m_pokegold.Rom().NotifyRomChanged();

            UpdateUnownImages();
        });

        m_unownShinyColor_2->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &unown = m_pokegold.Data().UnownImages()[*m_selectedUnown];
            auto &pokemon = m_pokegold.Data().Pokemons()[200];
            pokemon.ShinyColors[1].R(newColor.Red());
            pokemon.ShinyColors[1].G(newColor.Green());
            pokemon.ShinyColors[1].B(newColor.Blue());
            m_pokegold.Rom().NotifyRomChanged();

            UpdateUnownImages();
        });
    }
}

void ui::DatabasePanel::UpdateUnownImages()
{
    m_eventGuard([&] {
        int index = *m_selectedUnown;
        if (index == -1)
        {
            m_unownFrontImage->Clear();
            m_unownBackImage->Clear();
            m_unownShinyFrontImage->Clear();
            m_unownShinyBackImage->Clear();

            m_unownColor_1->SetColor(*wxWHITE);
            m_unownColor_2->SetColor(*wxWHITE);
            m_unownShinyColor_1->SetColor(*wxWHITE);
            m_unownShinyColor_2->SetColor(*wxWHITE);
        }
        else
        {
            auto &unown = m_pokegold.Data().UnownImages()[index];
            auto &pokemon = m_pokegold.Data().Pokemons()[200];

            m_unownFrontImage->SetData(pokemon.ImageDimensions, unown.FrontImage, pokemon.Colors);
            m_unownBackImage->SetData(pokegold::ImageDimensions::Size_48x48, unown.BackImage, pokemon.Colors);
            m_unownShinyFrontImage->SetData(pokemon.ImageDimensions, unown.FrontImage, pokemon.ShinyColors);
            m_unownShinyBackImage->SetData(pokegold::ImageDimensions::Size_48x48, unown.BackImage, pokemon.ShinyColors);

            m_unownColor_1->SetColor(pokemon.Colors[0].ToWxColor());
            m_unownColor_2->SetColor(pokemon.Colors[1].ToWxColor());
            m_unownShinyColor_1->SetColor(pokemon.ShinyColors[0].ToWxColor());
            m_unownShinyColor_2->SetColor(pokemon.ShinyColors[1].ToWxColor());
        }
    });
}
