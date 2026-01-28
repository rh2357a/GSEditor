#include "bad_data_dialog.h"

#include "pokegold.h"
#include "utils.h"

#include <string>
#include <format>
#include <vector>

gui::dialogs::BadDataDialog::BadDataDialog(wxWindow *parent, std::span<const pokegold::data::bad_data> badDataList) : BadDataDialogBase(parent)
{
    using namespace pokegold::data;

    gui::controls::FixedHeaderWidth(m_badDataList, {{wxT("순번"), 48}, {wxT("손상 내용"), -6}, {wxT("대응 내용"), -4}});

    m_badDataList->Freeze();

    for (size_t i = 0; i < badDataList.size(); i++)
    {
        const auto &e = badDataList[i];
        m_badDataList->InsertItem(i, wxT(""));

        switch (e.reason)
        {
        case bad_data_reason::EVOLUTION_MOVES: {
            const size_t idx = std::any_cast<size_t>(e.data);
            const auto name = pokemons[idx].name.editor_str();
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("진화·자력기 데이터 손상 (번호: {}, 이름: '{}')", idx, name)));
            m_badDataList->SetItem(i, 2, wxT("해당 포켓몬의 진화·자력기를 비움"));
            break;
        }

        case bad_data_reason::EGG_IMAGE: {
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxT("알 이미지 데이터 손상"));
            m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 변경"));
            break;
        }

        case bad_data_reason::POKEMON_FRONT_IMAGE: {
            const size_t idx = std::any_cast<size_t>(e.data);
            const auto name = pokemons[idx].name.editor_str();
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("포켓몬 앞모습 이미지 손상 (번호: {}, 이름: '{}')", idx, name)));
            m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 변경"));
            break;
        }
        case bad_data_reason::POKEMON_BACK_IMAGE: {
            const size_t idx = std::any_cast<size_t>(e.data);
            const auto name = pokemons[idx].name.editor_str();
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("포켓몬 뒷모습 이미지 손상 (번호: {}, 이름: '{}')", idx, name)));
            m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 변경"));
            break;
        }

        case bad_data_reason::UNOWN_FRONT_IMAGE: {
            const size_t idx = std::any_cast<size_t>(e.data);
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("안농 앞모습 이미지 손상 (알파벳: '{}')", char('A' + idx))));
            m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 변경"));
            break;
        }
        case bad_data_reason::UNOWN_BACK_IMAGE: {
            const size_t idx = std::any_cast<size_t>(e.data);
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("안농 뒷모습 이미지 손상 (알파벳: '{}')", char('A' + idx))));
            m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 변경"));
            break;
        }

        case bad_data_reason::TRAINER_IMAGE: {
            const size_t idx = std::any_cast<size_t>(e.data);
            const auto name = trainer_groups[idx].name.editor_str();
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("트레이너 이미지 손상 (그룹명: '{}')", name)));
            m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 변경"));
            break;
        }

        case bad_data_reason::POKEMON_NAME: {
            const size_t idx = std::any_cast<size_t>(e.data);
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("포켓몬 이름 손상 (번호: {})", idx)));
            m_badDataList->SetItem(i, 2, wxT("비어있는 내용으로 변경"));
            break;
        }
        case bad_data_reason::TRAINER_GROUP_NAME: {
            const size_t idx = std::any_cast<size_t>(e.data);
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("트레이너 그룹 이름 손상 (번호: {})", idx)));
            m_badDataList->SetItem(i, 2, wxT("비어있는 내용으로 변경"));
            break;
        }
        case bad_data_reason::TYPE_NAME: {
            const size_t idx = std::any_cast<size_t>(e.data);
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("타입 이름 손상 (번호: {}", idx)));
            m_badDataList->SetItem(i, 2, wxT("비어있는 내용으로 변경"));
            break;
        }

        case bad_data_reason::TYPE_MATCHUPS: {
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxT("타입 상성 데이터 손상"));
            m_badDataList->SetItem(i, 2, wxT("기본값으로 변경"));
            break;
        }
        case bad_data_reason::WEATHER_TYPE_MODIFIERS: {
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxT("날씨에 의한 타입 위력 증가 데이터 손상"));
            m_badDataList->SetItem(i, 2, wxT("기본값으로 변경"));
            break;
        }
        case bad_data_reason::WEATHER_MOVE_MODIFIERS: {
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxT("날씨에 의한 기술 위력 증가 데이터 손상"));
            m_badDataList->SetItem(i, 2, wxT("기본값으로 변경"));
            break;
        }
        }
    }

    m_badDataList->Thaw();
}

void gui::dialogs::BadDataDialog::OnDialogShow(wxShowEvent &event)
{
    if (event.IsShown())
        wxBell();
}

void gui::dialogs::BadDataDialog::OnConfirmButtonClick(wxCommandEvent &event)
{
    Close();
}

void gui::dialogs::BadDataDialog::OnYesButtonClick(wxCommandEvent &event)
{
    EndModal(wxID_YES);
}
void gui::dialogs::BadDataDialog::OnNoButtonClick(wxCommandEvent &event)
{
    EndModal(wxID_NO);
}
