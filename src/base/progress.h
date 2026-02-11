#pragma once

#include "base/functional/state.h"

#include <optional>
#include <string>
#include <array>
#include <mutex>
#include <condition_variable>

namespace base
{
    class Progress
    {
    private:
        double m_progress = 0.0;
        std::string m_message = "";

    public:
        Progress() = default;
        Progress(double progress, std::string message) : m_progress(progress), m_message(message) {}

    public:
        double GetProgress() const { return m_progress; }
        std::string GetMessage() const { return m_message; }
    };

    class ProgressState : public MutableState<Progress>
    {
    private:
        std::mutex m_mutex;
        std::condition_variable m_cv;

        bool m_paused = false;
        bool m_canceled = false;
        bool m_finish = false;

    public:
        bool IsPaused() const { return m_paused; }
        bool IsCanceled() const { return m_canceled; }
        bool IsPausedOrCanceled() const { return m_paused || m_canceled; }
        bool IsFinish() const { return m_finish; }

        void Pause();
        void Resume();
        void Cancel();
        void Finish();

        /// @brief Paused 상태에서 재진행 신호까지 대기
        void WaitForResumeOrCancel();
    };

    class MutableProgressState : public ProgressState
    {
    private:
        inline static const auto TAG = "base::MutableProgressState";

    private:
        size_t m_numTasks = 0;
        size_t m_currentTask = 0;
        std::string m_message = "-";

    public:
        /// @brief 총 진행률을 지정하는 생성자
        /// @param numTasks 진행률 max 값, `0`으로 설정할 경우 진행률 디버그 로그가 남겨짐
        MutableProgressState(size_t numTasks) : m_numTasks(numTasks) {};

    public:
        /// @brief 상태 초기화
        void Reset();

        /// @brief Paused, Canceled 핸들링
        /// @return 취소 확정 시 true를 반환
        bool HandlePausedOrCanceled();

        /// @brief 작업률 증가
        void Increase();

        /// @brief 작업 메시지 갱신
        /// @param message 메시지
        void UpdateMessage(std::string message);

    private:
        void UpdateInternal();
    };
}
