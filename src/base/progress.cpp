#include "progress.h"

#include "base/log.h"

#include <wx/wx.h>

void base::ProgressState::Pause()
{
    m_paused = true;
    m_canceled = false;
}

void base::ProgressState::Resume()
{
    m_paused = false;
    m_canceled = false;

    m_cv.notify_all();
}

void base::ProgressState::Cancel()
{
    m_paused = false;
    m_canceled = true;

    m_cv.notify_all();
}

void base::ProgressState::WaitForResumeOrCancel()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cv.wait(lock);
}

void base::MutableProgressState::Reset()
{
    m_currentTask = 0;
    Resume();
    UpdateInternal();
}

bool base::MutableProgressState::HandlePausedOrCanceled()
{
    if (IsPaused())
        WaitForResumeOrCancel();

    if (IsCanceled())
        return true;

    return false;
}

void base::MutableProgressState::Increase()
{
    m_currentTask++;

    // NOTE: 진행률 초기값을 계산하기 위함
#ifdef DEBUG
    if (m_numTasks == 0)
        base::Log(TAG, "increase progress (current={})", m_currentTask);
#endif

    UpdateInternal();
}

void base::MutableProgressState::UpdateMessage(std::string message)
{
    m_message = message;
    UpdateInternal();
}

void base::MutableProgressState::UpdateInternal()
{
    double progress = m_numTasks == 0 ? 0.0 : double(m_currentTask) / m_numTasks;
    MutableState::Update({progress, m_message});
}
