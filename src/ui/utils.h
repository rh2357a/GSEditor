#pragma once

#include <wx/wx.h>
#include <wx/listctrl.h>

#include <span>

namespace ui
{
    /// @brief wxListCtrl 헤더 항목을 이동할 수 없도록 함
    /// @param ctrl wxListCtrl 포인터
    void ApplyListCtrlFixedHeader(wxListCtrl *ctrl);

    /// @brief wxListCtrl 헤더의 열 너비 자동 조절
    /// @param ctrl wxListCtrl 포인터
    void AutoListCtrlColumnWidth(wxListCtrl *ctrl);
}
