#pragma once

#include <wx/wx.h>

#include <functional>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

namespace base
{
    /**
     * @brief 이벤트 클래스
     *
     * @tparam _Value 이벤트 발생 시 전달될 값 타입
     */
    template <typename... _Value>
    class Event
    {
    private:
        using _Observer = std::function<void(_Value...)>;

    private:
        mutable std::mutex m_mutex;
        bool m_destroy = false;

        std::unordered_map<size_t, _Observer> m_observers;
        size_t m_ovserverId = 0;

    public:
        Event() = default;
        ~Event() { m_destroy = true; }

    public:
        bool IsDestroy() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_destroy;
        }

        void operator()(_Value... val)
        {
            std::vector<std::pair<size_t, _Observer>> observersCopy;

            {
                std::lock_guard<std::mutex> lock(m_mutex);
                for (const auto &[id, obs] : m_observers)
                    observersCopy.push_back({id, obs});
            }

            for (const auto &[id, observer] : observersCopy)
            {
                bool stillExists = false;
                {
                    std::lock_guard<std::mutex> lock(m_mutex);
                    stillExists = m_observers.find(id) != m_observers.end();
                }

                if (stillExists)
                    observer(val...);
            }
        }

    private:
        int AddObserver(_Observer observer)
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            size_t id = m_ovserverId++;
            m_observers[id] = std::move(observer);

            return id;
        }

        void RemoveObserver(size_t id)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_observers.erase(id);
        }

    public:
        /**
         * @brief 이벤트 구독
         * 
         * @param control wx 윈도우 호스트에 바인딩하여 안전하게 해제
         * @param func 이벤트 옵저버 함수
         */
        void Subscribe(wxWindowBase *control, _Observer func)
        {
            auto id = std::make_shared<size_t>(AddObserver(std::move(func)));

            control->Bind(wxEVT_DESTROY, [this, id](wxWindowDestroyEvent &ev) {
                if (!IsDestroy())
                    RemoveObserver(*id);
                ev.Skip();
            });
        }
    };
}
