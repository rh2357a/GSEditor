#include "database_panel.h"

#include "base/files/bitmap.h"
#include "base/log.h"
#include "services/pokegold/data/game_data.h"
#include "ui/bindings.h"
#include "ui/dialogs/file_dialogs.h"
#include "ui/dialogs/message_box.h"
#include "ui/utils.h"

#include <wx/combobox.h>
#include <wx/event.h>

void ui::DatabasePanel::InitializeUnownTab()
{
    // 목록 설정
    {
        ApplyListSearch(this, {m_unownPokemonComboBox});
        BindControlSelection(this, m_unownList, m_selectedUnown);

        // 롬 열기 시, 선택 초기화...
        m_pokegold.IsOpenedState().Subscribe(this, [this](const bool &isOpened) {
            m_selectedUnown.Update(-1);

            if (isOpened)
                m_unownPokemonComboBox->Select(m_pokegold.Data.UnownPokemonId);
        });

        // 포켓몬 목록 바인딩
        m_pokegold.Data.PokemonNameUpdated.Subscribe(this, [this](const int &id) {
            m_unownPokemonComboBox->Freeze();

            if (m_unownPokemonComboBox->GetCount() == 0)
            {
                for (int i = 0; i < 251 + 1; i++)
                    m_unownPokemonComboBox->Append(wxT(""));
            }

            if (id == -1)
            {
                m_unownPokemonComboBox->SetString(0, wxT("없음"));

                for (int i = 0; i < 251; i++)
                {
                    auto &name = m_pokegold.Data.Pokemons[i].Name;
                    m_unownPokemonComboBox->SetString(i + 1, name.ToEditorWxString());
                }
            }
            else if (id < 251)
            {
                auto &name = m_pokegold.Data.Pokemons[id].Name;
                m_unownPokemonComboBox->SetString(id + 1, name.ToEditorWxString());
            }

            m_unownPokemonComboBox->Thaw();
        });

        // 선택
        m_selectedUnown.Subscribe(this, [this](const int &idx) {
            base::Log(TAG, "unown selected (index={})", idx);

            m_unownInnerPanel->Enable(m_pokegold.Data.UnownPokemonId != 0xff);
            m_unownContainer->Enable(idx != -1);

            UpdateUnownImages();

            m_unownList->SetFocus();
        });

        // 콤보상자 휠 비활성화
        m_unownPokemonComboBox->Bind(wxEVT_MOUSEWHEEL, [](wxMouseEvent &ev) { ev.Skip(false); });

        // 안농 적용 포켓몬 선택
        m_unownPokemonComboBox->Bind(wxEVT_COMBOBOX, [this](wxCommandEvent &ev) {
            ev.Skip();

            m_pokegold.Data.UnownPokemonId = m_unownPokemonComboBox->GetSelection() == 0 ? 0xff : m_unownPokemonComboBox->GetSelection();
            m_pokegold.NotifyRomChanged();

            // 갱신 처리
            m_selectedUnown.Update(m_pokegold.Data.UnownPokemonId != 0xff ? *m_selectedUnown : -1);
            m_selectedPokemon.Update(*m_selectedPokemon);
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
                auto result = base::ImportIndexedPngFile(*path, base::ImportIndexedPngTileOrientation::Vertical);
                if (result == base::ImportIndexedPngResult::PngError)
                {
                    ShowErrorDialog(this, "알림", "png 파일의 형식이 올바르지 않습니다.");
                    return;
                }

                const auto size = result.GetBitmap().GetSize();
                if (!(size.x == 40 && size.y == 40)
                    && !(size.x == 48 && size.y == 48)
                    && !(size.x == 56 && size.y == 56))
                {
                    ShowErrorDialog(this, "알림", "앞모습의 이미지는 40x40, 48x48, 56x56 중 하나로 맞춰주세요.");
                    return;
                }

                auto &unown = m_pokegold.Data.UnownImages[*m_selectedUnown];
                unown.FrontImage = result.Get2bppData();
                unown.ImageDimensions = pokegold::ToImageDimensions(size);

                if (ShowYesNoDialog(this, "알림", "색상을 교체하겠습니까?") == MessageBoxResult::Yes)
                {
                    auto &pokemon = m_pokegold.Data.Pokemons[m_pokegold.Data.UnownPokemonId - 1];
                    pokemon.Colors[0] = result.GetPalette()[1];
                    pokemon.Colors[1] = result.GetPalette()[2];
                }

                m_pokegold.NotifyRomChanged();

                UpdateUnownImages();
            }
        });

        m_unownBackImage->ImportRequested().Subscribe(this, [this] {
            const auto path = ShowOpenFileDialog(this, "이미지 교체...", {"png 파일|*.png"});
            if (path.has_value())
            {
                auto result = base::ImportIndexedPngFile(*path, base::ImportIndexedPngTileOrientation::Vertical);
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

                auto &unown = m_pokegold.Data.UnownImages[*m_selectedUnown];
                unown.BackImage = result.Get2bppData();

                if (ShowYesNoDialog(this, "알림", "색상을 교체하겠습니까?") == MessageBoxResult::Yes)
                {
                    auto &pokemon = m_pokegold.Data.Pokemons[m_pokegold.Data.UnownPokemonId - 1];
                    pokemon.Colors[0] = result.GetPalette()[1];
                    pokemon.Colors[1] = result.GetPalette()[2];
                }

                m_pokegold.NotifyRomChanged();

                UpdateUnownImages();
            }
        });

        m_unownShinyFrontImage->ImportRequested().Subscribe(this, [this] {
            const auto path = ShowOpenFileDialog(this, "이미지 교체...", {"png 파일|*.png"});
            if (path.has_value())
            {
                auto result = base::ImportIndexedPngFile(*path, base::ImportIndexedPngTileOrientation::Vertical);
                if (result == base::ImportIndexedPngResult::PngError)
                {
                    ShowErrorDialog(this, "알림", "png 파일의 형식이 올바르지 않습니다.");
                    return;
                }

                const auto size = result.GetBitmap().GetSize();
                if (!(size.x == 40 && size.y == 40)
                    && !(size.x == 48 && size.y == 48)
                    && !(size.x == 56 && size.y == 56))
                {
                    ShowErrorDialog(this, "알림", "앞모습의 이미지는 40x40, 48x48, 56x56 중 하나로 맞춰주세요.");
                    return;
                }

                auto &unown = m_pokegold.Data.UnownImages[*m_selectedUnown];
                unown.FrontImage = result.Get2bppData();
                unown.ImageDimensions = pokegold::ToImageDimensions(size);

                if (ShowYesNoDialog(this, "알림", "색상을 교체하겠습니까?") == MessageBoxResult::Yes)
                {
                    auto &pokemon = m_pokegold.Data.Pokemons[m_pokegold.Data.UnownPokemonId - 1];
                    pokemon.ShinyColors[0] = result.GetPalette()[1];
                    pokemon.ShinyColors[1] = result.GetPalette()[2];
                }

                m_pokegold.NotifyRomChanged();

                UpdateUnownImages();
            }
        });

        m_unownShinyBackImage->ImportRequested().Subscribe(this, [this] {
            const auto path = ShowOpenFileDialog(this, "이미지 교체...", {"png 파일|*.png"});
            if (path.has_value())
            {
                auto result = base::ImportIndexedPngFile(*path, base::ImportIndexedPngTileOrientation::Vertical);
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

                auto &unown = m_pokegold.Data.UnownImages[*m_selectedUnown];
                unown.BackImage = result.Get2bppData();

                if (ShowYesNoDialog(this, "알림", "색상을 교체하겠습니까?") == MessageBoxResult::Yes)
                {
                    auto &pokemon = m_pokegold.Data.Pokemons[m_pokegold.Data.UnownPokemonId - 1];
                    pokemon.ShinyColors[0] = result.GetPalette()[1];
                    pokemon.ShinyColors[1] = result.GetPalette()[2];
                }

                m_pokegold.NotifyRomChanged();

                UpdateUnownImages();
            }
        });

        m_unownColor_1->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.IsOpenedState())
                return;

            auto &unown = m_pokegold.Data.UnownImages[*m_selectedUnown];
            auto &pokemon = m_pokegold.Data.Pokemons[m_pokegold.Data.UnownPokemonId - 1];
            pokemon.Colors[0].R(newColor.Red());
            pokemon.Colors[0].G(newColor.Green());
            pokemon.Colors[0].B(newColor.Blue());
            m_pokegold.NotifyRomChanged();

            UpdateUnownImages();
        });

        m_unownColor_2->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.IsOpenedState())
                return;

            auto &unown = m_pokegold.Data.UnownImages[*m_selectedUnown];
            auto &pokemon = m_pokegold.Data.Pokemons[m_pokegold.Data.UnownPokemonId - 1];
            pokemon.Colors[1].R(newColor.Red());
            pokemon.Colors[1].G(newColor.Green());
            pokemon.Colors[1].B(newColor.Blue());
            m_pokegold.NotifyRomChanged();

            UpdateUnownImages();
        });

        m_unownShinyColor_1->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.IsOpenedState())
                return;

            auto &unown = m_pokegold.Data.UnownImages[*m_selectedUnown];
            auto &pokemon = m_pokegold.Data.Pokemons[m_pokegold.Data.UnownPokemonId - 1];
            pokemon.ShinyColors[0].R(newColor.Red());
            pokemon.ShinyColors[0].G(newColor.Green());
            pokemon.ShinyColors[0].B(newColor.Blue());
            m_pokegold.NotifyRomChanged();

            UpdateUnownImages();
        });

        m_unownShinyColor_2->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.IsOpenedState())
                return;

            auto &unown = m_pokegold.Data.UnownImages[*m_selectedUnown];
            auto &pokemon = m_pokegold.Data.Pokemons[m_pokegold.Data.UnownPokemonId - 1];
            pokemon.ShinyColors[1].R(newColor.Red());
            pokemon.ShinyColors[1].G(newColor.Green());
            pokemon.ShinyColors[1].B(newColor.Blue());
            m_pokegold.NotifyRomChanged();

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
            auto &unown = m_pokegold.Data.UnownImages[index];
            auto &pokemon = m_pokegold.Data.Pokemons[m_pokegold.Data.UnownPokemonId - 1];

            m_unownFrontImage->Set2bppData(unown.ImageDimensions, unown.FrontImage, pokemon.Colors);
            m_unownBackImage->Set2bppData(pokegold::ImageDimensions::Size_48x48, unown.BackImage, pokemon.Colors);
            m_unownShinyFrontImage->Set2bppData(unown.ImageDimensions, unown.FrontImage, pokemon.ShinyColors);
            m_unownShinyBackImage->Set2bppData(pokegold::ImageDimensions::Size_48x48, unown.BackImage, pokemon.ShinyColors);

            m_unownColor_1->SetColor(pokemon.Colors[0].ToWxColor());
            m_unownColor_2->SetColor(pokemon.Colors[1].ToWxColor());
            m_unownShinyColor_1->SetColor(pokemon.ShinyColors[0].ToWxColor());
            m_unownShinyColor_2->SetColor(pokemon.ShinyColors[1].ToWxColor());
        }
    });
}
