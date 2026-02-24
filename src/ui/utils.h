#pragma once

#include <wx/listctrl.h>
#include <wx/window.h>
#include <wx/wx.h>

namespace ui
{
    /**
     * @brief `wxBORDER_THEME`가 적용된 컨트롤의 외선 그리기 문제 해결
     *
     * @param hostCtrl 부모 윈도우
     */
    void FixBorderTheme(wxWindow *hostCtrl);

    /**
     * @brief wxListCtrl 헤더 열 위치 고정
     *
     * @param ctrl wxListCtrl
     */
    void ApplyListCtrlFixedHeader(wxListCtrl *ctrl);

    /**
     * @brief wxListCtrl 헤더 열 너비 자동 설정
     *
     * @param ctrl wxListCtrl
     */
    void AutoListCtrlColumnWidth(wxListCtrl *ctrl);

    /**
     * @brief 컨트롤을 드롭다운 팝업 형식으로 표시
     *
     * @param parent 위치를 맞출 호스트 컨트롤
     * @param popupCtrl 팝업에 표시될 컨트롤
     */
    void ShowDropdownPopup(wxWindow *parent, wxWindow *popupCtrl);
}
