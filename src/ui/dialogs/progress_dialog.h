#pragma once

#include "base/functional/state.h"
#include "base/progress.h"
#include "ui/dialogs/message_box.h"
#include "ui/ui.h"

#include <functional>
#include <string>
#include <thread>

namespace ui::internal
{
    template <typename _ReturnType>
    class ProgressDialog : public ProgressDialogBase
    {
    private:
        std::function<_ReturnType()> m_workerThreadFunc;
        std::thread m_jobThread;
        std::thread m_uiUpdateThread;
        std::atomic<bool> m_workerThreadJobFinished = false;
        std::atomic<bool> m_workerThreadFinished = false;

        base::ProgressState &m_state;
        base::MutableState<bool> m_enabledState = true;

        _ReturnType m_result;

    public:
        ProgressDialog(wxWindow *parent, std::string title, base::ProgressState &state, std::function<_ReturnType()> workerThreadFunc)
            : ProgressDialogBase(parent),
              m_workerThreadFunc(workerThreadFunc),
              m_state(state)
        {
            SetTitle(wxString::FromUTF8(title));

            m_enabledState.Subscribe(this, [this](const bool &isEnabled) {
                CallAfter([this, isEnabled] {
                    m_cancelButton->Enable(isEnabled);
                });
            });
        }

        ~ProgressDialog()
        {
            if (m_jobThread.joinable())
                m_jobThread.join();

            if (m_uiUpdateThread.joinable())
                m_uiUpdateThread.join();
        }

    private:
        void OnInit(wxInitDialogEvent &event) override
        {
            UpdateProgress();

            m_jobThread = std::thread([this] {
                m_result = m_workerThreadFunc();
                m_workerThreadJobFinished.store(true);
                wxMilliSleep(400);
                m_workerThreadFinished = true;
                CallAfter([this] { EndModal(0); });
            });

            m_uiUpdateThread = std::thread([this] {
                while (!m_workerThreadFinished)
                {
                    wxMilliSleep(10);

                    if (!m_workerThreadFinished)
                        CallAfter([this] { UpdateProgress(); });
                }
            });
        }

        void UpdateProgress()
        {
            auto &progress = *m_state;

            // NOTE: 불안정해 보이는 애니메이션 비활성화
            // (https://forums.wxwidgets.org/viewtopic.php?t=42138)
            m_progressGauge->SetValue(100);

            m_progressGauge->SetValue(int(progress.GetProgress() * 100));
            m_messageLabel->SetLabelText(wxString::FromUTF8(progress.GetMessage()));

            m_enabledState.Update(!m_workerThreadJobFinished);
        }

        void OnCancelButtonClick(wxCommandEvent &event) override
        {
            m_state.Pause();

            auto result = ShowYesNoDialog(this, "알림", "정말로 취소하겠습니까?");
            if (result == MessageBoxResult::Yes)
                m_state.Cancel();
            else
                m_state.Resume();
        }

    public:
        auto GetResult()
        {
            return m_result;
        }
    };
}

namespace ui
{
    template <typename Func>
    auto ShowProgressDialog(wxWindow *parent, std::string title, base::ProgressState &state, Func workerThreadFunc)
    {
        using _ReturnType = decltype(workerThreadFunc());

        std::function<_ReturnType()> funcWrapper = workerThreadFunc;
        internal::ProgressDialog<_ReturnType> dialog(parent, title, state, funcWrapper);
        dialog.ShowModal();

        return dialog.GetResult();
    }
}
