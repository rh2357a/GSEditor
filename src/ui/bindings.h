#pragma once

#include "base/functional/guard.h"
#include "base/functional/state.h"

#include <wx/listctrl.h>
#include <wx/slider.h>
#include <wx/spinctrl.h>
#include <wx/wx.h>

#include <memory>


namespace ui
{
    /**
     * @brief 체크 상자 값 상태 바인딩
     *
     * @param hostControl 바인딩 자동 해제를 위한 호스트 윈도우
     * @param control 컨트롤
     * @param state 바인딩 대상 상태 객체
     */
    void BindCheckBoxValue(wxWindowBase *hostControl, wxCheckBoxBase *control, base::MutableState<bool> &state);

    /**
     * @brief 텍스트 상자 값 상태 바인딩
     *
     * @param hostControl 바인딩 자동 해제를 위한 호스트 윈도우
     * @param control 컨트롤
     * @param state 바인딩 대상 상태 객체
     */
    void BindTextBoxText(wxWindowBase *hostControl, wxTextCtrlBase *control, base::MutableState<wxString> &state);

    /**
     * @brief double 형식의 스핀 컨트롤 값 상태 바인딩
     *
     * @param hostControl 바인딩 자동 해제를 위한 호스트 윈도우
     * @param control 컨트롤
     * @param state 바인딩 대상 상태 객체
     */
    void BindSpinCtrlDoubleValue(wxWindowBase *hostControl, wxSpinCtrlDouble *control, base::MutableState<double> &state);

    /**
     * @brief int 형식의 스핀 컨트롤 값 상태 바인딩
     *
     * @param hostControl 바인딩 자동 해제를 위한 호스트 윈도우
     * @param control 컨트롤
     * @param state 바인딩 대상 상태 객체
     */
    void BindSpinCtrlValue(wxWindowBase *hostControl, wxSpinCtrlDouble *control, base::MutableState<int> &state);

    /**
     * @brief double 형식의 스핀 컨트롤 값 상태 바인딩
     *
     * @param hostControl 바인딩 자동 해제를 위한 호스트 윈도우
     * @param control 컨트롤
     * @param state 바인딩 대상 상태 객체
     */
    void BindSliderValue(wxWindowBase *hostControl, wxSlider *control, base::MutableState<int> &state);

    /**
     * @brief 선택 값 상태 바인딩
     *
     * @param hostControl 바인딩 자동 해제를 위한 호스트 윈도우
     * @param control 선택 가능한 컨트롤
     * @param state 바인딩 대상 상태 객체
     */
    void BindControlSelection(wxWindowBase *hostControl, wxControlWithItemsBase *control, base::MutableState<int> &state);

    /**
     * @brief 선택 값 상태 바인딩
     *
     * @param hostControl 바인딩 자동 해제를 위한 호스트 윈도우
     * @param control 선택 가능한 컨트롤
     * @param state 바인딩 대상 상태 객체
     */
    void BindControlSelection(wxWindowBase *hostControl, wxListCtrl *control, base::MutableState<int> &state);
}

namespace ui
{
    /**
     * @brief 라디오 버튼 값 상태 바인딩
     *
     * @tparam _Type enum 등, 열겨 가능한 객체
     * @param hostControl 바인딩 자동 해제를 위한 호스트 윈도우
     * @param control 라디오 버튼 컨트롤
     * @param state 바인딩 대상 상태 객체
     * @param expectValue 바인딩 대상과 일치하는 값
     */
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
