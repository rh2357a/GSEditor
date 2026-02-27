#pragma once

#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <wx/window.h>
#include <wx/wx.h>

#include <initializer_list>

namespace ui
{
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

    /**
     * @brief 이벤트가 발생되는 wxSpinCtrlDouble 값 설정
     *
     * @param ctrl 컨트롤
     * @param value 값
     */
    void SetValueSpinCtrlDouble(wxSpinCtrlDouble *ctrl, double value);
}
