#include "bad_data_dialog.h"

#include "pokegold.h"

#include <string>
#include <format>

gui::windows::BadDataDialog::BadDataDialog(wxWindow *parent, std::span<const pokegold::data::bad_data> badDataList) : BadDataDialogBase(parent)
{
    using namespace pokegold::data;

    m_badDataList->ClearAll();
    m_badDataList->InsertColumn(0, wxT("순번"));
    m_badDataList->InsertColumn(1, wxT("손상 내용"));
    m_badDataList->InsertColumn(2, wxT("대응 내용"));

    for (size_t i = 0; i < badDataList.size(); i++)
    {
        const auto &e = badDataList[i];
        m_badDataList->InsertItem(i, wxT(""));

        switch (e.reason)
        {
        case bad_data_reason::EVOLUTION_MOVES: {
            const size_t idx = std::any_cast<size_t>(e.data);
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("진화·자력기 데이터 손상 (번호: {}, 이름: {})", idx + 1, pokemons[idx].name.u8string())));
            m_badDataList->SetItem(i, 2, wxT("해당 포켓몬의 진화·자력기를 비움"));
            break;
        }
        case bad_data_reason::EGG_IMAGE: {
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxT("알 이미지 데이터 손상"));
            m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 교체"));
            break;
        }
        case bad_data_reason::POKEMON_FRONT_IMAGE: {
            const size_t idx = std::any_cast<size_t>(e.data);
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("포켓몬 앞모습 이미지 손상 (번호: {}, 이름: {})", idx + 1, pokemons[idx].name.u8string())));
            m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 교체"));
            break;
        }
        case bad_data_reason::POKEMON_BACK_IMAGE: {
            const size_t idx = std::any_cast<size_t>(e.data);
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("포켓몬 뒷모습 이미지 손상 (번호: {}, 이름: {})", idx + 1, pokemons[idx].name.u8string())));
            m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 교체"));
            break;
        }
        case bad_data_reason::UNOWN_FRONT_IMAGE: {
            const size_t idx = std::any_cast<size_t>(e.data);
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("안농 앞모습 이미지 손상 (알파뱃: {})", char('A' + idx))));
            m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 교체"));
            break;
        }
        case bad_data_reason::UNOWN_BACK_IMAGE: {
            const size_t idx = std::any_cast<size_t>(e.data);
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("안농 뒷모습 이미지 손상 (알파뱃: {})", char('A' + idx))));
            m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 교체"));
            break;
        }
        case bad_data_reason::TRAINER_IMAGE: {
            const size_t idx = std::any_cast<size_t>(e.data);
            m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
            m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("트레이너 이미지 손상 (그룹명: {})", trainer_groups[idx].name.u8string())));
            m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 교체"));
            break;
        }
        }
    }

    for (int i = 0; i < m_badDataList->GetColumnCount(); i++)
        m_badDataList->SetColumnWidth(i, wxLIST_AUTOSIZE);
}

void gui::windows::BadDataDialog::OnConfirmButtonClick(wxCommandEvent &event)
{
    Close();
}
