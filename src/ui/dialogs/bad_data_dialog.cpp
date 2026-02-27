#include "bad_data_dialog.h"

#include "ui/utils.h"

#include <wx/wx.h>

#include <format>

ui::internal::BadDataDialog::BadDataDialog(wxWindow *parent, std::span<const pokegold::BadData> badDataList) : BadDataDialogBase(parent)
{
    ApplyListCtrlFixedHeader(m_badDataList);

    m_badDataList->InsertColumn(0, wxT("순번"));
    m_badDataList->InsertColumn(1, wxT("손상 내용"));
    m_badDataList->InsertColumn(2, wxT("대응 내용"));

    m_badDataList->Freeze();

    for (size_t i = 0; i < badDataList.size(); i++)
    {
        const auto &e = badDataList[i];
        m_badDataList->InsertItem(i, wxT(""));

        switch (e.Reason())
        {
        case pokegold::BadDataReason::EvolutionAndMoves:
            {
                const size_t idx = std::any_cast<size_t>(e.Data());
                const auto name = m_pokegold.Data().Pokemons()[idx].Name.ToEditorString();
                m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
                m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("진화·자력기 데이터 손상 (번호: {}, 이름: '{}')", idx, name)));
                m_badDataList->SetItem(i, 2, wxT("해당 포켓몬의 진화·자력기를 비움"));
            }
            break;

        case pokegold::BadDataReason::EggImage:
            {
                m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
                m_badDataList->SetItem(i, 1, wxT("알 이미지 데이터 손상"));
                m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 변경"));
            }
            break;

        case pokegold::BadDataReason::PokemonImage:
            {
                const size_t idx = std::any_cast<size_t>(e.Data());
                const auto name = m_pokegold.Data().Pokemons()[idx].Name.ToEditorString();
                m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
                m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("포켓몬 이미지 손상 (번호: {}, 이름: '{}')", idx, name)));
                m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 변경"));
            }
            break;

        case pokegold::BadDataReason::UnownImage:
            {
                const size_t idx = std::any_cast<size_t>(e.Data());
                m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
                m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("안농 이미지 손상 (알파벳: '{}')", char('A' + idx))));
                m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 변경"));
            }
            break;

        case pokegold::BadDataReason::TrainerGroupImage:
            {
                const size_t idx = std::any_cast<size_t>(e.Data());
                const auto name = m_pokegold.Data().TrainerGroups()[idx].Name.ToEditorString();
                m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
                m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("트레이너 이미지 손상 (그룹명: '{}')", name)));
                m_badDataList->SetItem(i, 2, wxT("비어있는 이미지로 변경"));
            }
            break;

        case pokegold::BadDataReason::PokemonName:
            {
                const size_t idx = std::any_cast<size_t>(e.Data());
                m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
                m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("포켓몬 이름 손상 (번호: {})", idx)));
                m_badDataList->SetItem(i, 2, wxT("비어있는 내용으로 변경"));
            }
            break;

        case pokegold::BadDataReason::Pokedex:
            {
                const size_t idx = std::any_cast<size_t>(e.Data());
                m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
                m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("포켓몬 도감 손상 (번호: {})", idx)));
                m_badDataList->SetItem(i, 2, wxT("비어있는 내용으로 변경"));
            }
            break;

        case pokegold::BadDataReason::TrainerGroupName:
            {
                const size_t idx = std::any_cast<size_t>(e.Data());
                m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
                m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("트레이너 그룹 이름 손상 (번호: {})", idx)));
                m_badDataList->SetItem(i, 2, wxT("비어있는 내용으로 변경"));
            }
            break;

        case pokegold::BadDataReason::TypeName:
            {
                const size_t idx = std::any_cast<size_t>(e.Data());
                m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
                m_badDataList->SetItem(i, 1, wxString::FromUTF8(std::format("타입 이름 손상 (번호: {}", idx)));
                m_badDataList->SetItem(i, 2, wxT("비어있는 내용으로 변경"));
            }
            break;

        case pokegold::BadDataReason::TypeMatchups:
            {
                m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
                m_badDataList->SetItem(i, 1, wxT("타입 상성 데이터 손상"));
                m_badDataList->SetItem(i, 2, wxT("기본값으로 변경"));
            }
            break;

        case pokegold::BadDataReason::WeatherTypeModifiers:
            {
                m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
                m_badDataList->SetItem(i, 1, wxT("날씨에 의한 타입 위력 증가 데이터 손상"));
                m_badDataList->SetItem(i, 2, wxT("기본값으로 변경"));
            }
            break;

        case pokegold::BadDataReason::WeatherMoveModifiers:
            {
                m_badDataList->SetItem(i, 0, wxString::FromUTF8(std::format("{}", i)));
                m_badDataList->SetItem(i, 1, wxT("날씨에 의한 기술 위력 증가 데이터 손상"));
                m_badDataList->SetItem(i, 2, wxT("기본값으로 변경"));
            }
            break;
        }
    }

    m_badDataList->Thaw();

    AutoListCtrlColumnWidth(m_badDataList);
}

void ui::internal::BadDataDialog::OnDialogShow(wxShowEvent &event)
{
    if (event.IsShown())
        wxBell();
}

void ui::internal::BadDataDialog::OnConfirmButtonClick(wxCommandEvent &event)
{
    EndModal(wxID_OK);
}

void ui::internal::BadDataDialog::OnCancelButtonClick(wxCommandEvent &event)
{
    EndModal(wxID_CANCEL);
}

void ui::ShowBadDataDialog(wxWindow *parent, std::span<const pokegold::BadData> badDataList)
{
    internal::BadDataDialog dialog(parent, badDataList);
    dialog.ShowModal();
}
