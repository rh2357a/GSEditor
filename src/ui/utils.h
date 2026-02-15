#pragma once

#include <wx/listctrl.h>
#include <wx/wx.h>

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
}
