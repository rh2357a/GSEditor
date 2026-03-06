#include "database_panel.h"

#include "base/files/bitmap.h"
#include "base/log.h"
#include "base/strings/string_util.h"
#include "services/pokegold/data/color.h"
#include "services/pokegold/data/game_data.h"
#include "ui/bindings.h"
#include "ui/controls/color_picker_panel.h"
#include "ui/controls/colored_list_ctrl.h"
#include "ui/controls/image_editor_panel.h"
#include "ui/dialogs/evolution_editor_dialog.h"
#include "ui/dialogs/file_dialogs.h"
#include "ui/dialogs/import_move_dialog.h"
#include "ui/dialogs/message_box.h"
#include "ui/dialogs/move_editor_dialog.h"
#include "ui/utils.h"

#include <utf8cpp/utf8.h>
#include <wx/colour.h>
#include <wx/event.h>
#include <wx/gdicmn.h>

#include <algorithm>
#include <array>
#include <unordered_map>

namespace
{
    enum class PokemonTabType : size_t
    {
        Pokemon = 0,
        Dummy,
        Egg,
    };

    enum class PokemonImageContainerType : size_t
    {
        Pokemon = 0,
        Unown,
    };

    std::unordered_map<pokegold::GrowthRate, int> k_growthRateIndexes{
        {pokegold::GrowthRate::MediumFast, 0},
        {pokegold::GrowthRate::SlightlyFast, 1},
        {pokegold::GrowthRate::SlightlySlow, 2},
        {pokegold::GrowthRate::MediumSlow, 3},
        {pokegold::GrowthRate::Fast, 4},
        {pokegold::GrowthRate::Slow, 5},
    };

    std::array<pokegold::GrowthRate, 6> k_growthRateReverseIndexes{
        pokegold::GrowthRate::MediumFast,
        pokegold::GrowthRate::SlightlyFast,
        pokegold::GrowthRate::SlightlySlow,
        pokegold::GrowthRate::MediumSlow,
        pokegold::GrowthRate::Fast,
        pokegold::GrowthRate::Slow,
    };

    std::unordered_map<pokegold::GenderRate, int> k_genderRateIndexes{
        {pokegold::GenderRate::Gender_0, 0},
        {pokegold::GenderRate::Gender_12_5, 1},
        {pokegold::GenderRate::Gender_25, 2},
        {pokegold::GenderRate::Gender_37_5, 3},
        {pokegold::GenderRate::Gender_50, 4},
        {pokegold::GenderRate::Gender_62_5, 5},
        {pokegold::GenderRate::Gender_75, 6},
        {pokegold::GenderRate::Gender_87_5, 7},
        {pokegold::GenderRate::Gender_100, 8},
        {pokegold::GenderRate::Unknown, 9},
    };

    std::array<pokegold::GenderRate, 10> k_genderRateReverseIndexes{
        pokegold::GenderRate::Gender_0,
        pokegold::GenderRate::Gender_12_5,
        pokegold::GenderRate::Gender_25,
        pokegold::GenderRate::Gender_37_5,
        pokegold::GenderRate::Gender_50,
        pokegold::GenderRate::Gender_62_5,
        pokegold::GenderRate::Gender_75,
        pokegold::GenderRate::Gender_87_5,
        pokegold::GenderRate::Gender_100,
        pokegold::GenderRate::Unknown,
    };

    std::unordered_map<pokegold::EggGroup, int> k_eggGroupIndexes{
        {pokegold::EggGroup::Monster, 0},
        {pokegold::EggGroup::Water1, 1},
        {pokegold::EggGroup::Bug, 2},
        {pokegold::EggGroup::Flying, 3},
        {pokegold::EggGroup::Field, 4},
        {pokegold::EggGroup::Fairy, 5},
        {pokegold::EggGroup::Plant, 6},
        {pokegold::EggGroup::HumanLike, 7},
        {pokegold::EggGroup::Water3, 8},
        {pokegold::EggGroup::Mineral, 9},
        {pokegold::EggGroup::Indeterminate, 10},
        {pokegold::EggGroup::Water2, 11},
        {pokegold::EggGroup::Ditto, 12},
        {pokegold::EggGroup::Dragon, 13},
        {pokegold::EggGroup::None, 14},
    };

    std::array<pokegold::EggGroup, 15> k_eggGroupReverseIndexes{
        pokegold::EggGroup::Monster,
        pokegold::EggGroup::Water1,
        pokegold::EggGroup::Bug,
        pokegold::EggGroup::Flying,
        pokegold::EggGroup::Field,
        pokegold::EggGroup::Fairy,
        pokegold::EggGroup::Plant,
        pokegold::EggGroup::HumanLike,
        pokegold::EggGroup::Water3,
        pokegold::EggGroup::Mineral,
        pokegold::EggGroup::Indeterminate,
        pokegold::EggGroup::Water2,
        pokegold::EggGroup::Ditto,
        pokegold::EggGroup::Dragon,
        pokegold::EggGroup::None,
    };
}

void ui::DatabasePanel::InitializePokemonTab()
{
    ApplyListSearch(this, {m_pokemonList, m_pokemonItem1ComboBox, m_pokemonItem2ComboBox});
    ApplyNestedScrolling({
        m_pokemonGenderRateComboBox,
        m_pokemonGrowthRateComboBox,
        m_pokemonType1ComboBox,
        m_pokemonType2ComboBox,
        m_pokemonItem1ComboBox,
        m_pokemonItem2ComboBox,
        m_pokemonEggGroup1ComboBox,
        m_pokemonEggGroup2ComboBox,

        m_pokemonStatsHpValue,
        m_pokemonStatsAtkValue,
        m_pokemonStatsDefValue,
        m_pokemonStatsSpAtkValue,
        m_pokemonStatsSpDefValue,
        m_pokemonStatsSpdValue,
        m_pokemonStatsExpValue,
        m_pokemonStatsCatchRateValue,

        m_pokemonDexHeightValue,
        m_pokemonDexWeightValue,
        m_pokemonDexDescriptionText,

        m_pokemonEvolutionsList,
        m_pokemonMovesList,

        m_pokemonHmTmList1,
        m_pokemonHmTmList2,
        m_pokemonHmTmList3,
        m_pokemonHmTmList4,
        m_pokemonHmTmList5,
        m_pokemonHmTmList6,
        m_pokemonHmTmList7,
        m_pokemonHmTmList8,
    });

    BindControlSelection(this, m_pokemonList, m_selectedPokemon);
    BindControlSelection(this, m_pokemonEvolutionsList, m_selectedPokemonEvolution);
    BindControlSelection(this, m_pokemonMovesList, m_selectedPokemonMove);

    // 롬을 다시 열었을 때, 선택 초기화...
    m_pokegold.Rom().Opened().Subscribe(this, [this](const bool &) {
        m_selectedPokemon.Update(-1);
        m_selectedPokemonEvolution.Update(-1);
        m_selectedPokemonMove.Update(-1);
    });

    // 포켓몬 이름 갱신
    m_pokegold.Data().PokemonNameUpdated().Subscribe(this, [this](const int &idx) {
        m_pokemonList->Freeze();

        if (m_pokemonList->GetCount() == 0)
        {
            for (size_t i = 0; i < 256; i++)
                m_pokemonList->Append(wxT(""));
        }

        if (idx == -1)
        {
            for (size_t i = 0; i < 256; i++)
            {
                auto &e = m_pokegold.Data().Pokemons()[i];
                m_pokemonList->SetString(i, e.Name.ToEditorWxString());
            }
        }
        else
        {
            auto &e = m_pokegold.Data().Pokemons()[idx];
            m_pokemonList->SetString(idx, e.Name.ToEditorWxString());
        }

        m_pokemonList->Thaw();
    });

    // 기술명 갱신
    m_pokegold.Data().MoveNameUpdated().Subscribe(this, [this](const int &idx) {
        UpdatePokemonEvolutionAndMoveList();
    });

    // 아이템 이름 갱신
    m_pokegold.Data().ItemNameUpdated().Subscribe(this, [this](const int &idx) {
        UpdatePokemonEvolutionAndMoveList();

        m_pokemonItem1ComboBox->Freeze();
        m_pokemonItem2ComboBox->Freeze();

        if (m_pokemonItem1ComboBox->GetCount() == 0)
        {
            for (size_t i = 0; i < 256 + 1; i++)
            {
                m_pokemonItem1ComboBox->Append(wxT(""));
                m_pokemonItem2ComboBox->Append(wxT(""));
            }
        }

        if (idx == -1)
        {
            m_pokemonItem1ComboBox->SetString(0, wxT("없음"));
            m_pokemonItem2ComboBox->SetString(0, wxT("없음"));

            for (size_t i = 0; i < 256; i++)
            {
                auto &e = m_pokegold.Data().Items()[i];
                auto name = e.Name.ToEditorWxString();
                m_pokemonItem1ComboBox->SetString(i + 1, name);
                m_pokemonItem2ComboBox->SetString(i + 1, name);
            }
        }
        else
        {
            auto &e = m_pokegold.Data().Items()[idx];
            auto name = e.Name.ToEditorWxString();
            m_pokemonItem1ComboBox->SetString(idx + 1, name);
            m_pokemonItem2ComboBox->SetString(idx + 1, name);
        }

        m_pokemonItem1ComboBox->Thaw();
        m_pokemonItem2ComboBox->Thaw();
    });

    // 타입 이름 갱신
    m_pokegold.Data().TypeNameUpdated().Subscribe(this, [this](const int &idx) {
        m_pokemonType1ComboBox->Freeze();
        m_pokemonType2ComboBox->Freeze();

        if (m_pokemonType1ComboBox->GetCount() == 0)
        {
            for (size_t i = 0; i < 28; i++)
            {
                m_pokemonType1ComboBox->Append(wxT(""));
                m_pokemonType2ComboBox->Append(wxT(""));
            }
        }

        if (idx == -1)
        {
            for (size_t i = 0; i < 28; i++)
            {
                auto &e = m_pokegold.Data().Types()[i];
                auto name = e.Name.ToEditorWxString();
                m_pokemonType1ComboBox->SetString(i, name);
                m_pokemonType2ComboBox->SetString(i, name);
            }
        }
        else
        {
            auto &e = m_pokegold.Data().Types()[idx];
            auto name = e.Name.ToEditorWxString();
            m_pokemonType1ComboBox->SetString(idx, name);
            m_pokemonType2ComboBox->SetString(idx, name);
        }

        m_pokemonType1ComboBox->Thaw();
        m_pokemonType2ComboBox->Thaw();
    });

    // 기술, 비전머신 목록 갱신 & 선택 이벤트 설정
    {
        auto tmhmCtrls = std::make_shared<std::vector<ui::ColoredCheckListBox *>>(std::vector<ColoredCheckListBox *>{
            m_pokemonHmTmList1,
            m_pokemonHmTmList2,
            m_pokemonHmTmList3,
            m_pokemonHmTmList4,
            m_pokemonHmTmList5,
            m_pokemonHmTmList6,
            m_pokemonHmTmList7,
            m_pokemonHmTmList8,
        });

        auto tmhmsUpdateFunc = [this, tmhmCtrls] {
            for (size_t i = 0; i < 57; i++)
            {
                auto &e = m_pokegold.Data().Moves()[m_pokegold.Data().TMHMs()[i].MoveId - 1];
                auto ctrl = (*tmhmCtrls)[i / 8];
                ctrl->SetString(
                    i % 8,
                    wxString::Format(
                        wxT("%s%02d [%s]"),
                        i < 50 ? wxT("기술") : wxT("비전"),
                        int(i < 50 ? i + 1 : i - 49),
                        e.Name.ToEditorWxString()));
            }

            int pokemonIdx = *m_selectedPokemon;
            if (pokemonIdx != -1)
            {
                size_t tmhmIdx = 0;
                for (auto *ctrl : *tmhmCtrls)
                {
                    for (unsigned int i = 0; i < ctrl->GetCount(); i++)
                        ctrl->Check(i, m_pokegold.Data().Pokemons()[pokemonIdx].TMHMs[tmhmIdx++]);
                }
            }
        };

        m_pokegold.Data().TMHMsUpdated().Subscribe(this, [tmhmsUpdateFunc] { tmhmsUpdateFunc(); });
        m_pokegold.Data().MoveNameUpdated().Subscribe(this, [tmhmsUpdateFunc](const int &) { tmhmsUpdateFunc(); });

        for (auto *ctrl : *tmhmCtrls)
        {
            ctrl->Bind(wxEVT_CHECKLISTBOX, [&, tmhmCtrls](wxCommandEvent &ev) {
                ev.Skip();

                if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                    return;

                auto &pokemon = m_pokegold.Data().Pokemons()[m_pokemonList->GetSelection()];
                size_t i = 0;
                for (auto *ctrl2 : *tmhmCtrls)
                {
                    for (unsigned j = 0; j < ctrl2->GetCount(); j++)
                        pokemon.TMHMs[i++] = ctrl2->IsChecked(j);
                }

                m_pokegold.Data().TMHMsUpdated()();
                m_pokegold.Rom().NotifyRomChanged();
            });
        }

        // 컨트롤 표시 개수
        Bind(wxEVT_SIZE, [&](wxSizeEvent &ev) {
            ev.Skip();

            int newColumns = GetClientSize().GetWidth() / 220;
            m_pokemonTMHMsSizer->SetCols(newColumns);
        });
    }

    // 콤보 상자 이벤트 설정
    {
        const auto &comboBoxBindFunc = [&](const auto &ev) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto valueChangedFunc = [&](auto &field, const auto &value) {
                if (value != field)
                {
                    field = value;
                    return true;
                }
                return false;
            };

            auto &pokemon = m_pokegold.Data().Pokemons()[m_pokemonList->GetSelection()];
            bool hasChanged = false;
            hasChanged |= valueChangedFunc(pokemon.GenderRate, k_genderRateReverseIndexes[m_pokemonGenderRateComboBox->GetSelection()]);
            hasChanged |= valueChangedFunc(pokemon.GrowthRate, k_growthRateReverseIndexes[m_pokemonGrowthRateComboBox->GetSelection()]);
            hasChanged |= valueChangedFunc(pokemon.TypeIds[0], u8(m_pokemonType1ComboBox->GetSelection()));
            hasChanged |= valueChangedFunc(pokemon.TypeIds[1], u8(m_pokemonType2ComboBox->GetSelection()));
            hasChanged |= valueChangedFunc(pokemon.ItemIds[0], u8(m_pokemonItem1ComboBox->GetSelection()));
            hasChanged |= valueChangedFunc(pokemon.ItemIds[1], u8(m_pokemonItem2ComboBox->GetSelection()));
            hasChanged |= valueChangedFunc(pokemon.EggGroups[0], k_eggGroupReverseIndexes[m_pokemonEggGroup1ComboBox->GetSelection()]);
            hasChanged |= valueChangedFunc(pokemon.EggGroups[1], k_eggGroupReverseIndexes[m_pokemonEggGroup2ComboBox->GetSelection()]);

            if (hasChanged)
                m_pokegold.Rom().NotifyRomChanged();
        };

        m_pokemonGenderRateComboBox->Bind(wxEVT_COMBOBOX, comboBoxBindFunc);
        m_pokemonGrowthRateComboBox->Bind(wxEVT_COMBOBOX, comboBoxBindFunc);
        m_pokemonType1ComboBox->Bind(wxEVT_COMBOBOX, comboBoxBindFunc);
        m_pokemonType2ComboBox->Bind(wxEVT_COMBOBOX, comboBoxBindFunc);
        m_pokemonItem1ComboBox->Bind(wxEVT_COMBOBOX, comboBoxBindFunc);
        m_pokemonItem2ComboBox->Bind(wxEVT_COMBOBOX, comboBoxBindFunc);
        m_pokemonEggGroup1ComboBox->Bind(wxEVT_COMBOBOX, comboBoxBindFunc);
        m_pokemonEggGroup2ComboBox->Bind(wxEVT_COMBOBOX, comboBoxBindFunc);
    }

    // 스핀 컨트롤 이벤트 설정
    {
        const auto &spinCtrlBindFunc = [&](const auto &ev) {
            const auto catchRatePercentage = wxString::Format(wxT("(%.2lf%%)"), m_pokemonStatsCatchRateValue->GetValue() / 255.0 * 100.0);
            m_pokemonCatchRatePercentage->SetLabelText(catchRatePercentage);

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto valueChangedFunc = [&](u8 &field, wxSpinCtrlDouble *ctrl) {
                const auto value = u8(ctrl->GetValue());
                if (field != value)
                {
                    field = value;
                    return true;
                }
                return false;
            };

            auto &pokemon = m_pokegold.Data().Pokemons()[m_pokemonList->GetSelection()];
            bool hasChanged = false;
            hasChanged |= valueChangedFunc(pokemon.Hp, m_pokemonStatsHpValue);
            hasChanged |= valueChangedFunc(pokemon.Attack, m_pokemonStatsAtkValue);
            hasChanged |= valueChangedFunc(pokemon.Defence, m_pokemonStatsDefValue);
            hasChanged |= valueChangedFunc(pokemon.SpAttack, m_pokemonStatsSpAtkValue);
            hasChanged |= valueChangedFunc(pokemon.SpDefence, m_pokemonStatsSpDefValue);
            hasChanged |= valueChangedFunc(pokemon.Speed, m_pokemonStatsSpdValue);
            hasChanged |= valueChangedFunc(pokemon.BaseExp, m_pokemonStatsExpValue);
            hasChanged |= valueChangedFunc(pokemon.CatchRate, m_pokemonStatsCatchRateValue);

            u8 height = u8(m_pokemonDexHeightValue->GetValue() * 10);
            if (height != pokemon.Height)
            {
                pokemon.Height = height;
                hasChanged = true;
            }

            u16 weight = u16(m_pokemonDexWeightValue->GetValue() * 10);
            if (weight != pokemon.Weight)
            {
                pokemon.Weight = weight;
                hasChanged = true;
            }

            if (hasChanged)
                m_pokegold.Rom().NotifyRomChanged();
        };

        m_pokemonStatsHpValue->Bind(wxEVT_SPINCTRLDOUBLE, spinCtrlBindFunc);
        m_pokemonStatsAtkValue->Bind(wxEVT_SPINCTRLDOUBLE, spinCtrlBindFunc);
        m_pokemonStatsDefValue->Bind(wxEVT_SPINCTRLDOUBLE, spinCtrlBindFunc);
        m_pokemonStatsSpAtkValue->Bind(wxEVT_SPINCTRLDOUBLE, spinCtrlBindFunc);
        m_pokemonStatsSpDefValue->Bind(wxEVT_SPINCTRLDOUBLE, spinCtrlBindFunc);
        m_pokemonStatsSpdValue->Bind(wxEVT_SPINCTRLDOUBLE, spinCtrlBindFunc);
        m_pokemonStatsExpValue->Bind(wxEVT_SPINCTRLDOUBLE, spinCtrlBindFunc);
        m_pokemonStatsCatchRateValue->Bind(wxEVT_SPINCTRLDOUBLE, spinCtrlBindFunc);
        m_pokemonDexHeightValue->Bind(wxEVT_SPINCTRLDOUBLE, spinCtrlBindFunc);
        m_pokemonDexWeightValue->Bind(wxEVT_SPINCTRLDOUBLE, spinCtrlBindFunc);
    }

    // 진화 목록 설정
    {
        m_pokemonEvolutionsList->AppendColumn(wxT("진화 후 포켓몬"));
        m_pokemonEvolutionsList->AppendColumn(wxT("진화 방법"));
        m_pokemonEvolutionsList->AppendColumn(wxT("조건 1"));
        m_pokemonEvolutionsList->AppendColumn(wxT("조건 2"));
        ApplyListCtrlFixedHeader(m_pokemonEvolutionsList);
        AutoListCtrlColumnWidth(m_pokemonEvolutionsList);

        auto listCtrlFunc = [this] {
            int selection = *m_selectedPokemonEvolution;
            int count = m_pokemonEvolutionsList->GetItemCount();
            m_pokemonEvolutionModify->Enable(selection != -1);
            m_pokemonEvolutionRemove->Enable(selection != -1);
            m_pokemonEvolutionAdd->Enable(count <= 16);
            m_pokemonEvolutionClear->Enable(count > 0);
        };

        m_pokemonEvolutionsList->Bind(wxEVT_LIST_DELETE_ITEM, [listCtrlFunc](wxListEvent &ev) { ev.Skip(); listCtrlFunc(); });
        m_pokemonEvolutionsList->Bind(wxEVT_LIST_DELETE_ALL_ITEMS, [listCtrlFunc](wxListEvent &ev) { ev.Skip(); listCtrlFunc(); });
        m_pokemonEvolutionsList->Bind(wxEVT_LIST_INSERT_ITEM, [listCtrlFunc](wxListEvent &ev) { ev.Skip(); listCtrlFunc(); });
        m_selectedPokemonEvolution.Subscribe(this, [listCtrlFunc] { listCtrlFunc(); });
    }

    // 자력기 목록 설정
    {
        m_pokemonMovesList->AppendColumn(wxT("레벨"));
        m_pokemonMovesList->AppendColumn(wxT("기술"));
        ApplyListCtrlFixedHeader(m_pokemonMovesList);
        AutoListCtrlColumnWidth(m_pokemonMovesList);

        auto listCtrlFunc = [this] {
            int selection = *m_selectedPokemonMove;
            int count = m_pokemonMovesList->GetItemCount();
            m_pokemonMovesModify->Enable(selection != -1);
            m_pokemonMovesRemove->Enable(selection != -1);
            m_pokemonMovesImport->Enable(count <= 32);
            m_pokemonMovesAdd->Enable(count <= 32);
            m_pokemonMovesClear->Enable(count > 0);
        };

        m_pokemonMovesList->Bind(wxEVT_LIST_DELETE_ITEM, [listCtrlFunc](wxListEvent &ev) { ev.Skip(); listCtrlFunc(); });
        m_pokemonMovesList->Bind(wxEVT_LIST_DELETE_ALL_ITEMS, [listCtrlFunc](wxListEvent &ev) { ev.Skip(); listCtrlFunc(); });
        m_pokemonMovesList->Bind(wxEVT_LIST_INSERT_ITEM, [listCtrlFunc](wxListEvent &ev) { ev.Skip(); listCtrlFunc(); });
        m_selectedPokemonMove.Subscribe(this, [listCtrlFunc] { listCtrlFunc(); });
    }

    // 이름 변경 설정
    m_pokemonNameText->Bind(wxEVT_TEXT, [&](const auto &ev) {
        if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
            return;

        auto str = m_pokemonNameText->GetValue().utf8_string();
        if (pokegold::String::IsCharmapString(str))
        {
            const auto pokemonIdx = *m_selectedPokemon;
            m_pokegold.Data().Pokemons()[pokemonIdx].Name = str;
            m_pokegold.Data().PokemonNameUpdated()(pokemonIdx);
            m_pokegold.Rom().NotifyRomChanged();
        }
    });

    // 도감 설명 설정
    {
        m_pokemonDexSpeciesNameText->Bind(wxEVT_TEXT, [&](const auto ev) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto str = m_pokemonDexSpeciesNameText->GetValue().utf8_string();
            if (pokegold::String::IsCharmapString(str))
            {
                auto &pokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];
                pokemon.DexCategoryName = str + "[50]";
                m_pokegold.Rom().NotifyRomChanged();
            }
        });

        m_pokemonDexDescriptionText->Bind(wxEVT_TEXT, [&](const auto ev) {
            auto str = m_pokemonDexDescriptionText->GetValue().utf8_string();
            const auto lines = base::Split(str, '\n');

            size_t maxLen = 0;
            for (const auto &line : lines)
                maxLen = std::max(maxLen, size_t(utf8::distance(line.begin(), line.end())));

            const auto dexDescLabel = wxString::Format(wxT("설명 (너비: %d/18)："), int(maxLen));
            m_pokemonDexDescriptionLabel->SetLabel(dexDescLabel);

            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            if (pokegold::String::IsCharmapString(str))
            {
                auto &pokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];
                pokemon.Description = str + "[50]";
                m_pokegold.Rom().NotifyRomChanged();
            }
        });
    }

    // 이미지, 팔레트 설정
    {
        m_pokemonFrontImage->ImportRequested().Subscribe(this, [this] {
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
                if (!(size.x == 40 && size.y == 40)
                    && !(size.x == 48 && size.y == 48)
                    && !(size.x == 56 && size.y == 56))
                {
                    ShowErrorDialog(this, "알림", "앞모습의 이미지는 40x40, 48x48, 56x56 중 하나로 맞춰주세요.");
                    return;
                }

                auto &pokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];
                pokemon.ImageDimensions = pokegold::ToImageDimensions(size);
                pokemon.FrontImage = result.Get2bppData();

                if (ShowYesNoDialog(this, "알림", "색상을 교체하겠습니까?") == MessageBoxResult::Yes)
                {
                    pokemon.Colors[0] = result.GetPalette()[1];
                    pokemon.Colors[1] = result.GetPalette()[2];
                }

                m_pokegold.Rom().NotifyRomChanged();

                UpdatePokemonImages();
            }
        });

        m_pokemonBackImage->ImportRequested().Subscribe(this, [this] {
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

                auto &pokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];
                pokemon.BackImage = result.Get2bppData();

                if (ShowYesNoDialog(this, "알림", "색상을 교체하겠습니까?") == MessageBoxResult::Yes)
                {
                    pokemon.Colors[0] = result.GetPalette()[1];
                    pokemon.Colors[1] = result.GetPalette()[2];
                }

                m_pokegold.Rom().NotifyRomChanged();

                UpdatePokemonImages();
            }
        });

        m_pokemonShinyFrontImage->ImportRequested().Subscribe(this, [this] {
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
                if (!(size.x == 40 && size.y == 40)
                    && !(size.x == 48 && size.y == 48)
                    && !(size.x == 56 && size.y == 56))
                {
                    ShowErrorDialog(this, "알림", "앞모습의 이미지는 40x40, 48x48, 56x56 중 하나로 맞춰주세요.");
                    return;
                }

                auto &pokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];
                pokemon.ImageDimensions = pokegold::ToImageDimensions(size);
                pokemon.FrontImage = result.Get2bppData();

                if (ShowYesNoDialog(this, "알림", "색상을 교체하겠습니까?") == MessageBoxResult::Yes)
                {
                    pokemon.ShinyColors[0] = result.GetPalette()[1];
                    pokemon.ShinyColors[1] = result.GetPalette()[2];
                }

                m_pokegold.Rom().NotifyRomChanged();

                UpdatePokemonImages();
            }
        });

        m_pokemonShinyBackImage->ImportRequested().Subscribe(this, [this] {
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

                auto &pokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];
                pokemon.BackImage = result.Get2bppData();

                if (ShowYesNoDialog(this, "알림", "색상을 교체하겠습니까?") == MessageBoxResult::Yes)
                {
                    pokemon.ShinyColors[0] = result.GetPalette()[1];
                    pokemon.ShinyColors[1] = result.GetPalette()[2];
                }

                m_pokegold.Rom().NotifyRomChanged();

                UpdatePokemonImages();
            }
        });

        m_pokemonColor_1->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &pokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];
            pokemon.Colors[0].R(newColor.Red());
            pokemon.Colors[0].G(newColor.Green());
            pokemon.Colors[0].B(newColor.Blue());
            m_pokegold.Rom().NotifyRomChanged();

            UpdatePokemonImages();
        });

        m_pokemonColor_2->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &pokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];
            pokemon.Colors[1].R(newColor.Red());
            pokemon.Colors[1].G(newColor.Green());
            pokemon.Colors[1].B(newColor.Blue());
            m_pokegold.Rom().NotifyRomChanged();

            UpdatePokemonImages();
        });

        m_pokemonShinyColor_1->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &pokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];
            pokemon.ShinyColors[0].R(newColor.Red());
            pokemon.ShinyColors[0].G(newColor.Green());
            pokemon.ShinyColors[0].B(newColor.Blue());
            m_pokegold.Rom().NotifyRomChanged();

            UpdatePokemonImages();
        });

        m_pokemonShinyColor_2->GetColorState().Subscribe(this, [this](const wxColour &newColor) {
            if (m_eventGuard.IsGuarded() || !*m_pokegold.Rom().Opened())
                return;

            auto &pokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];
            pokemon.ShinyColors[1].R(newColor.Red());
            pokemon.ShinyColors[1].G(newColor.Green());
            pokemon.ShinyColors[1].B(newColor.Blue());
            m_pokegold.Rom().NotifyRomChanged();

            UpdatePokemonImages();
        });
    }

    // 포켓몬 목록 선택 처리
    m_selectedPokemon.Subscribe(this, [this](const int &idx) {
        base::Log(TAG, "pokemon selected (index={})", idx);

        m_eventGuard([&] {
            m_pokemonContainer->Enable(idx != -1);

            auto tmhmCtrls = std::vector<ui::ColoredCheckListBox *>{
                m_pokemonHmTmList1,
                m_pokemonHmTmList2,
                m_pokemonHmTmList3,
                m_pokemonHmTmList4,
                m_pokemonHmTmList5,
                m_pokemonHmTmList6,
                m_pokemonHmTmList7,
                m_pokemonHmTmList8,
            };

            if (idx == -1)
            {
                m_pokemonContainer->SetSelection(size_t(PokemonTabType::Pokemon));

                m_pokemonNoText->SetValue(wxT("-"));
                m_pokemonNameText->SetValue(wxT(""));
                m_pokemonGenderRateComboBox->Select(-1);
                m_pokemonGrowthRateComboBox->Select(-1);
                m_pokemonType1ComboBox->Select(-1);
                m_pokemonType2ComboBox->Select(-1);
                m_pokemonItem1ComboBox->Select(-1);
                m_pokemonItem2ComboBox->Select(-1);
                m_pokemonEggGroup1ComboBox->Select(-1);
                m_pokemonEggGroup2ComboBox->Select(-1);

                SetValueSpinCtrlDouble(m_pokemonStatsHpValue, 0);
                SetValueSpinCtrlDouble(m_pokemonStatsAtkValue, 0);
                SetValueSpinCtrlDouble(m_pokemonStatsDefValue, 0);
                SetValueSpinCtrlDouble(m_pokemonStatsSpAtkValue, 0);
                SetValueSpinCtrlDouble(m_pokemonStatsSpDefValue, 0);
                SetValueSpinCtrlDouble(m_pokemonStatsSpdValue, 0);
                SetValueSpinCtrlDouble(m_pokemonStatsExpValue, 0);
                SetValueSpinCtrlDouble(m_pokemonStatsCatchRateValue, 0);

                m_pokemonDexSpeciesNameText->SetValue(wxT(""));
                SetValueSpinCtrlDouble(m_pokemonDexHeightValue, 0);
                SetValueSpinCtrlDouble(m_pokemonDexWeightValue, 0);
                m_pokemonDexDescriptionText->SetValue(wxT(""));

                for (auto *ctrl : tmhmCtrls)
                {
                    for (unsigned int i = 0; i < ctrl->GetCount(); i++)
                        ctrl->Check(i, false);
                }
            }
            else
            {
                auto &e = m_pokegold.Data().Pokemons()[idx];

                if (e.Type == pokegold::PokemonType::Pokemon)
                    m_pokemonContainer->SetSelection(size_t(PokemonTabType::Pokemon));
                else
                    m_pokemonContainer->SetSelection(size_t(PokemonTabType::Dummy));

                if (e.Type == pokegold::PokemonType::Pokemon)
                {
                    if (m_pokegold.Data().UnownPokemonId == e.Id)
                        m_pokemonImageContainer->SetSelection(size_t(PokemonImageContainerType::Unown));
                    else
                        m_pokemonImageContainer->SetSelection(size_t(PokemonImageContainerType::Pokemon));
                }

                m_pokemonNoText->SetValue(wxString::Format(wxT("%d"), e.Id));
                m_pokemonNameText->SetValue(e.Name.ToEditorWxString());
                m_pokemonGenderRateComboBox->Select(k_genderRateIndexes[e.GenderRate]);
                m_pokemonGrowthRateComboBox->Select(k_growthRateIndexes[e.GrowthRate]);
                m_pokemonType1ComboBox->Select(e.TypeIds[0]);
                m_pokemonType2ComboBox->Select(e.TypeIds[1]);
                m_pokemonItem1ComboBox->Select(e.ItemIds[0]);
                m_pokemonItem2ComboBox->Select(e.ItemIds[1]);
                m_pokemonEggGroup1ComboBox->Select(k_eggGroupIndexes[e.EggGroups[0]]);
                m_pokemonEggGroup2ComboBox->Select(k_eggGroupIndexes[e.EggGroups[1]]);

                SetValueSpinCtrlDouble(m_pokemonStatsHpValue, e.Hp);
                SetValueSpinCtrlDouble(m_pokemonStatsAtkValue, e.Attack);
                SetValueSpinCtrlDouble(m_pokemonStatsDefValue, e.Defence);
                SetValueSpinCtrlDouble(m_pokemonStatsSpAtkValue, e.SpAttack);
                SetValueSpinCtrlDouble(m_pokemonStatsSpDefValue, e.SpDefence);
                SetValueSpinCtrlDouble(m_pokemonStatsSpdValue, e.Speed);
                SetValueSpinCtrlDouble(m_pokemonStatsExpValue, e.BaseExp);
                SetValueSpinCtrlDouble(m_pokemonStatsCatchRateValue, e.CatchRate);

                m_pokemonDexSpeciesNameText->SetValue(e.DexCategoryName.ToEditorWxString());
                SetValueSpinCtrlDouble(m_pokemonDexHeightValue, double(e.Height / 10.0));
                SetValueSpinCtrlDouble(m_pokemonDexWeightValue, double(e.Weight / 10.0));
                m_pokemonDexDescriptionText->SetValue(e.Description.ToEditorWxString());

                size_t tmhmIdx = 0;
                for (auto *ctrl : tmhmCtrls)
                {
                    for (unsigned int i = 0; i < ctrl->GetCount(); i++)
                        ctrl->Check(i, e.TMHMs[tmhmIdx++]);
                }
            }
        });

        UpdatePokemonImages();
        UpdatePokemonEvolutionAndMoveList();

        m_pokemonList->SetFocus();
    });
}

void ui::DatabasePanel::UpdatePokemonImages()
{
    m_eventGuard([&] {
        int index = *m_selectedPokemon;
        if (index == -1 || m_pokegold.Data().Pokemons()[index].Type != pokegold::PokemonType::Pokemon)
        {
            m_pokemonFrontImage->Clear();
            m_pokemonBackImage->Clear();
            m_pokemonShinyFrontImage->Clear();
            m_pokemonShinyBackImage->Clear();

            m_pokemonColor_1->SetColor(*wxWHITE);
            m_pokemonColor_2->SetColor(*wxWHITE);
            m_pokemonShinyColor_1->SetColor(*wxWHITE);
            m_pokemonShinyColor_2->SetColor(*wxWHITE);
        }
        else
        {
            auto &pokemon = m_pokegold.Data().Pokemons()[index];

            m_pokemonFrontImage->SetData(pokemon.ImageDimensions, pokemon.FrontImage, pokemon.Colors);
            m_pokemonBackImage->SetData(pokegold::ImageDimensions::Size_48x48, pokemon.BackImage, pokemon.Colors);
            m_pokemonShinyFrontImage->SetData(pokemon.ImageDimensions, pokemon.FrontImage, pokemon.ShinyColors);
            m_pokemonShinyBackImage->SetData(pokegold::ImageDimensions::Size_48x48, pokemon.BackImage, pokemon.ShinyColors);

            m_pokemonColor_1->SetColor(pokemon.Colors[0].ToWxColor());
            m_pokemonColor_2->SetColor(pokemon.Colors[1].ToWxColor());
            m_pokemonShinyColor_1->SetColor(pokemon.ShinyColors[0].ToWxColor());
            m_pokemonShinyColor_2->SetColor(pokemon.ShinyColors[1].ToWxColor());
        }
    });
}

void ui::DatabasePanel::UpdatePokemonEvolutionAndMoveList()
{
    m_pokemonEvolutionsList->DeleteAllItems();
    m_pokemonMovesList->DeleteAllItems();

    const auto selected = m_pokemonList->GetSelection();
    if (selected == -1)
        return;

    auto &e = m_pokegold.Data().Pokemons()[selected];

    for (size_t i = 0; i < e.EvolutionMethods.size(); i++)
    {
        m_pokemonEvolutionsList->InsertItem(i, wxT(""));

        const auto &ev = e.EvolutionMethods[i];
        switch (ev.EvolutionMethodType)
        {
        case pokegold::EvolutionMethodType::LevelUp:
            m_pokemonEvolutionsList->SetItem(i, 0, m_pokegold.Data().Pokemons()[ev.PokemonId - 1].Name.ToEditorWxString());
            m_pokemonEvolutionsList->SetItem(i, 1, wxT("레벨 업"));
            m_pokemonEvolutionsList->SetItem(i, 2, wxString::Format(wxT("레벨 %d 달성"), ev.Level));
            m_pokemonEvolutionsList->SetItem(i, 3, wxT("-"));
            break;

        case pokegold::EvolutionMethodType::UseItem:
            m_pokemonEvolutionsList->SetItem(i, 0, m_pokegold.Data().Pokemons()[ev.PokemonId - 1].Name.ToEditorWxString());
            m_pokemonEvolutionsList->SetItem(i, 1, wxT("도구 사용"));
            m_pokemonEvolutionsList->SetItem(i, 2, wxString::Format(wxT("'%s' 사용"), m_pokegold.Data().Items()[ev.ItemId - 1].Name.ToEditorWxString()));
            m_pokemonEvolutionsList->SetItem(i, 3, wxT("-"));
            break;

        case pokegold::EvolutionMethodType::Trade:
            m_pokemonEvolutionsList->SetItem(i, 0, m_pokegold.Data().Pokemons()[ev.PokemonId - 1].Name.ToEditorWxString());
            m_pokemonEvolutionsList->SetItem(i, 1, wxT("통신교환"));

            if (ev.ItemId == 0xff)
                m_pokemonEvolutionsList->SetItem(i, 2, wxT("-"));
            else
                m_pokemonEvolutionsList->SetItem(i, 2, wxString::Format(wxT("'%s' 지닌 상태"), m_pokegold.Data().Items()[ev.ItemId - 1].Name.ToEditorWxString()));
            m_pokemonEvolutionsList->SetItem(i, 3, wxT("-"));

            break;

        case pokegold::EvolutionMethodType::LevelUpWithHappiness:
            m_pokemonEvolutionsList->SetItem(i, 0, m_pokegold.Data().Pokemons()[ev.PokemonId - 1].Name.ToEditorWxString());
            m_pokemonEvolutionsList->SetItem(i, 1, wxT("레벨 업"));

            switch (ev.Happiness)
            {
            case 1:
                m_pokemonEvolutionsList->SetItem(i, 2, wxT("친밀도"));
                m_pokemonEvolutionsList->SetItem(i, 3, wxT("-"));
                break;
            case 2:
                m_pokemonEvolutionsList->SetItem(i, 2, wxT("친밀도"));
                m_pokemonEvolutionsList->SetItem(i, 3, wxT("낮 시간대"));
                break;
            case 3:
                m_pokemonEvolutionsList->SetItem(i, 2, wxT("친밀도"));
                m_pokemonEvolutionsList->SetItem(i, 3, wxT("밤 시간대"));
                break;
            default:
                m_pokemonEvolutionsList->SetItem(i, 2, wxT("?"));
                m_pokemonEvolutionsList->SetItem(i, 3, wxT("?"));
                break;
            }

            break;

        case pokegold::EvolutionMethodType::LevelUpWithStats:
            m_pokemonEvolutionsList->SetItem(i, 0, m_pokegold.Data().Pokemons()[ev.PokemonId - 1].Name.ToEditorWxString());
            m_pokemonEvolutionsList->SetItem(i, 1, wxT("레벨 업"));
            m_pokemonEvolutionsList->SetItem(i, 2, wxString::Format(wxT("레벨 %d 달성"), ev.Level));

            switch (ev.Stats)
            {
            case 1:
                m_pokemonEvolutionsList->SetItem(i, 3, wxT("공격이 방어보다 높음"));
                break;
            case 2:
                m_pokemonEvolutionsList->SetItem(i, 3, wxT("방어가 공격보다 높음"));
                break;
            case 3:
                m_pokemonEvolutionsList->SetItem(i, 3, wxT("공격과 방어가 같음"));
                break;
            default:
                m_pokemonEvolutionsList->SetItem(i, 3, wxT("?"));
                break;
            }

            break;
        }
    }

    for (size_t i = 0; i < e.Moves.size(); i++)
    {
        m_pokemonMovesList->InsertItem(i, wxT(""));

        const auto &move = e.Moves[i];
        m_pokemonMovesList->SetItem(i, 0, wxString::Format(wxT("%d"), move.Level));
        m_pokemonMovesList->SetItem(i, 1, m_pokegold.Data().Moves()[move.MoveId - 1].Name.ToEditorWxString());
    }

    m_selectedPokemonEvolution.Update(-1);
    m_selectedPokemonMove.Update(-1);

    AutoListCtrlColumnWidth(m_pokemonEvolutionsList);
    AutoListCtrlColumnWidth(m_pokemonMovesList);
}

void ui::DatabasePanel::OnPokemonEvolutionsButtonClick(wxCommandEvent &event)
{
    event.Skip();

    if (!*m_pokegold.Rom().Opened() || *m_selectedPokemon == -1)
        return;

    const int id = event.GetId();
    const int selectedEvolveIdx = *m_selectedPokemonEvolution;
    auto &selectedPokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];

    if (id == wxID_POKEMON_EVOLUTION_ADD)
    {
        auto result = ShowEvolutionEditorDialog(this);
        if (result.has_value())
        {
            for (const auto &e : selectedPokemon.EvolutionMethods)
            {
                if (e == *result)
                    return;
            }

            selectedPokemon.EvolutionMethods.push_back(*result);

            UpdatePokemonEvolutionAndMoveList();
            m_pokegold.Rom().NotifyRomChanged();
        }
        return;
    }

    if (id == wxID_POKEMON_EVOLUTION_MODIFY)
    {
        auto result = ShowEvolutionEditorDialog(this, selectedPokemon.EvolutionMethods[selectedEvolveIdx]);
        if (result.has_value())
        {
            for (const auto &e : selectedPokemon.EvolutionMethods)
            {
                if (e == *result)
                    return;
            }

            selectedPokemon.EvolutionMethods[selectedEvolveIdx] = *result;

            UpdatePokemonEvolutionAndMoveList();
            m_pokegold.Rom().NotifyRomChanged();
        }
        return;
    }

    if (id == wxID_POKEMON_EVOLUTION_REMOVE)
    {
        auto result = ShowYesNoDialog(this, "삭제", "삭제하면 복구할 수 없습니다.\n계속하시겠습니까?");
        if (result == MessageBoxResult::Yes)
        {
            auto position = selectedPokemon.EvolutionMethods.begin() + selectedEvolveIdx;
            selectedPokemon.EvolutionMethods.erase(position);
            UpdatePokemonEvolutionAndMoveList();
            m_pokegold.Rom().NotifyRomChanged();
        }
        return;
    }

    if (id == wxID_POKEMON_EVOLUTION_CLEAR)
    {
        auto result = ShowYesNoDialog(this, "전체 삭제", "삭제하면 복구할 수 없습니다.\n계속하시겠습니까?");
        if (result == MessageBoxResult::Yes)
        {
            selectedPokemon.EvolutionMethods.clear();
            UpdatePokemonEvolutionAndMoveList();
            m_pokegold.Rom().NotifyRomChanged();
        }
        return;
    }
}

void ui::DatabasePanel::OnPokemonMovesButtonClick(wxCommandEvent &event)
{
    event.Skip();

    if (!*m_pokegold.Rom().Opened() || *m_selectedPokemon == -1)
        return;

    const int id = event.GetId();
    const int selectedMoveIdx = *m_selectedPokemonMove;
    auto &selectedPokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];

    if (id == wxID_POKEMON_MOVES_IMPORT)
    {
        auto result = ShowImportMoveDialog(this);
        if (!result.empty())
        {
            for (const auto &e : result)
            {
                bool exists = false;
                for (const auto &move : selectedPokemon.Moves)
                {
                    if (e == move)
                        exists = true;
                }

                if (!exists)
                    selectedPokemon.Moves.push_back(e);
            }

            std::sort(
                selectedPokemon.Moves.begin(),
                selectedPokemon.Moves.end(),
                [&](pokegold::PokemonMove &a, pokegold::PokemonMove &b) {
                    return a.Level < b.Level;
                });

            UpdatePokemonEvolutionAndMoveList();
            m_pokegold.Rom().NotifyRomChanged();
        }
        return;
    }

    if (id == wxID_POKEMON_MOVES_ADD)
    {
        auto result = ShowMoveEditorDialog(this);
        if (result.has_value())
        {
            for (const auto &e : selectedPokemon.Moves)
            {
                if (e == *result)
                    return;
            }

            selectedPokemon.Moves.push_back(*result);
            std::sort(
                selectedPokemon.Moves.begin(),
                selectedPokemon.Moves.end(),
                [&](pokegold::PokemonMove &a, pokegold::PokemonMove &b) {
                    return a.Level < b.Level;
                });

            UpdatePokemonEvolutionAndMoveList();
            m_pokegold.Rom().NotifyRomChanged();

            // 추가된 항목 선택처리
            auto foundResult = std::find(selectedPokemon.Moves.begin(), selectedPokemon.Moves.end(), *result);
            int addedIdx = std::distance(selectedPokemon.Moves.begin(), foundResult);
            m_selectedPokemonMove.Update(addedIdx);
        }
        return;
    }

    if (id == wxID_POKEMON_MOVES_MODIFY)
    {
        auto result = ShowMoveEditorDialog(this, selectedPokemon.Moves[selectedMoveIdx]);
        if (result.has_value())
        {
            for (const auto &e : selectedPokemon.Moves)
            {
                if (e == *result)
                    return;
            }

            selectedPokemon.Moves[selectedMoveIdx] = *result;
            std::sort(
                selectedPokemon.Moves.begin(),
                selectedPokemon.Moves.end(),
                [&](pokegold::PokemonMove &a, pokegold::PokemonMove &b) {
                    return a.Level < b.Level;
                });

            UpdatePokemonEvolutionAndMoveList();
            m_pokegold.Rom().NotifyRomChanged();

            // 항목 선택처리
            auto foundResult = std::find(selectedPokemon.Moves.begin(), selectedPokemon.Moves.end(), *result);
            int changedIdx = std::distance(selectedPokemon.Moves.begin(), foundResult);
            m_selectedPokemonMove.Update(changedIdx);
        }
        return;
    }

    if (id == wxID_POKEMON_MOVES_REMOVE)
    {
        auto result = ShowYesNoDialog(this, "삭제", "삭제하면 복구할 수 없습니다.\n계속하시겠습니까?");
        if (result == MessageBoxResult::Yes)
        {
            auto position = selectedPokemon.Moves.begin() + selectedMoveIdx;
            selectedPokemon.Moves.erase(position);
            UpdatePokemonEvolutionAndMoveList();
            m_pokegold.Rom().NotifyRomChanged();
        }
        return;
    }

    if (id == wxID_POKEMON_MOVES_CLEAR)
    {
        auto result = ShowYesNoDialog(this, "전체 삭제", "삭제하면 복구할 수 없습니다.\n계속하시겠습니까?");
        if (result == MessageBoxResult::Yes)
        {
            selectedPokemon.Moves.clear();
            UpdatePokemonEvolutionAndMoveList();
            m_pokegold.Rom().NotifyRomChanged();
        }
        return;
    }
}

void ui::DatabasePanel::OnPokemonTMHMsButtonClick(wxCommandEvent &event)
{
    event.Skip();

    if (!*m_pokegold.Rom().Opened() || *m_selectedPokemon == -1)
        return;

    const int id = event.GetId();
    auto &selectedPokemon = m_pokegold.Data().Pokemons()[*m_selectedPokemon];

    auto tmhmCtrls = std::vector<ui::ColoredCheckListBox *>{
        m_pokemonHmTmList1,
        m_pokemonHmTmList2,
        m_pokemonHmTmList3,
        m_pokemonHmTmList4,
        m_pokemonHmTmList5,
        m_pokemonHmTmList6,
        m_pokemonHmTmList7,
        m_pokemonHmTmList8,
    };

    if (id == wxID_POKEMON_TMHMS_CHECK_ALL)
    {
        auto result = ShowYesNoDialog(this, "모두 선택", "모두 선택하면 복구할 수 없습니다.\n계속하시겠습니까?");
        if (result == MessageBoxResult::No)
            return;

        m_eventGuard([&] {
            for (auto *ctrl : tmhmCtrls)
            {
                for (unsigned int i = 0; i < ctrl->GetCount(); i++)
                    ctrl->Check(i, true);
            }

            for (auto &e : selectedPokemon.TMHMs)
                e = true;

            m_pokegold.Data().TMHMsUpdated()();
            m_pokegold.Rom().NotifyRomChanged();
        });
        return;
    }

    if (id == wxID_POKEMON_TMHMS_CLEAR)
    {
        auto result = ShowYesNoDialog(this, "모두 해제", "모두 해제하면 복구할 수 없습니다.\n계속하시겠습니까?");
        if (result == MessageBoxResult::No)
            return;

        m_eventGuard([&] {
            for (auto *ctrl : tmhmCtrls)
            {
                for (unsigned int i = 0; i < ctrl->GetCount(); i++)
                    ctrl->Check(i, false);
            }

            for (auto &e : selectedPokemon.TMHMs)
                e = false;

            m_pokegold.Data().TMHMsUpdated()();
            m_pokegold.Rom().NotifyRomChanged();
        });
        return;
    }
}
