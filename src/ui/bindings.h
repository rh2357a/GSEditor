#pragma once

#include "base/functional/guard.h"
#include "base/functional/state.h"

#include <wx/listctrl.h>
#include <wx/wx.h>

#include <memory>

namespace ui
{
    /// @brief 체크 상자 값 바인딩
    /// @param hostControl 자동 해제를 위한 호스트 컨트롤
    /// @param control 컨트롤
    /// @param state 상태
    void BindCheckBoxValue(wxWindowBase *hostControl, wxCheckBoxBase *control, base::MutableState<bool> &state);

    /// @brief 텍스트 상자 값 바인딩
    /// @param hostControl 자동 해제를 위한 호스트 컨트롤
    /// @param control 컨트롤
    /// @param state 상태
    void BindTextBoxText(wxWindowBase *hostControl, wxTextCtrlBase *control, base::MutableState<wxString> &state);

    /// @brief 목록 선택 바인딩
    /// @param hostControl 자동 해제를 위한 호스트 컨트롤
    /// @param control 컨트롤
    /// @param state 상태
    void BindControlSelection(wxWindowBase *hostControl, wxControlWithItemsBase *control, base::MutableState<int> &state);

    /// @brief 목록 선택 바인딩
    /// @param hostControl 자동 해제를 위한 호스트 컨트롤
    /// @param control 컨트롤
    /// @param state 상태
    void BindControlSelection(wxWindowBase *hostControl, wxListCtrl *control, base::MutableState<int> &state);
}

namespace ui
{
    /// @brief 라디오 버튼 값 바인딩
    /// @tparam _Type
    /// @param hostControl 자동 해제를 위한 호스트 컨트롤
    /// @param control 컨트롤
    /// @param state 상태
    /// @param expectValue 체크 상태의 값
    template <typename _Type>
    void BindRadioButtonValue(wxWindowBase *hostControl, wxRadioButtonBase *control, base::MutableState<_Type> &state, _Type expectValue)
    {
        if (control != nullptr)
        {
            control->SetValue(*state == expectValue);

            auto guard = std::make_shared<base::Guard>();

            state.Subscribe(hostControl, [control, expectValue, guard](const _Type &val) {
                if (control != nullptr && !(*guard).IsGuarded())
                    control->SetValue(val == expectValue);
            });

            control->Bind(wxEVT_RADIOBUTTON, [&state, expectValue, guard](wxCommandEvent &ev) {
                if (!(*guard).IsGuarded())
                {
                    (*guard)([&state, expectValue] {
                        state.Update(expectValue);
                    });
                }

                ev.Skip();
            });
        }
    }
}
