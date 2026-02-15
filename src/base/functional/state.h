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
     * @brief 상태 관리 클래스
     *
     * @tparam _Value 내부 값 타입
     */
    template <typename _Value>
    class State
    {
    private:
        using _Observer = std::function<void(_Value)>;

    private:
        _Value m_value;

        mutable std::mutex m_mutex;
        bool m_destroy = false;

        std::unordered_map<size_t, _Observer> m_observers;
        size_t m_ovserverId = 0;

    public:
        State() = default;
        State(const _Value &defaultValue) : m_value(defaultValue) {}
        ~State() { m_destroy = true; }

    public:
        bool IsDestroy() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_destroy;
        }

        const _Value &operator*() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_value;
        }

    protected:
        void Update(_Value val)
        {
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_value = std::move(val);
            }

            Notify();
        }

        void Notify()
        {
            std::vector<std::pair<size_t, _Observer>> observersCopy;
            _Value valueCopy;

            {
                std::lock_guard<std::mutex> lock(m_mutex);
                valueCopy = m_value;
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
                    observer(valueCopy);
            }
        }

        void NotifyById(size_t id)
        {
            _Observer observerCopy;
            _Value valueCopy;

            bool stillExists = false;
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                if (m_observers.contains(id))
                {
                    observerCopy = m_observers.at(id);
                    valueCopy = m_value;
                    stillExists = true;
                }
            }

            if (stillExists)
                observerCopy(valueCopy);
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
         * @brief 상태 변경 구독
         *
         * @param control wx 윈도우 호스트에 바인딩하여 안전하게 해제
         * @param func 옵저버 함수
         */
        void Subscribe(wxWindowBase *control, _Observer func)
        {
            auto id = std::make_shared<size_t>(AddObserver(std::move(func)));

            control->Bind(wxEVT_DESTROY, [this, id](wxWindowDestroyEvent &ev) {
                if (!IsDestroy())
                    RemoveObserver(*id);
                ev.Skip();
            });

            NotifyById(*id);
        }

        /**
         * @brief 상태 변경 구독
         *
         * @param control wx 윈도우 호스트에 바인딩하여 안전하게 해제
         * @param func 옵저버 함수
         */
        void Subscribe(wxWindowBase *control, std::function<void()> func)
        {
            auto id = std::make_shared<size_t>(AddObserver([func](auto) { func(); }));

            control->Bind(wxEVT_DESTROY, [this, id](wxWindowDestroyEvent &ev) {
                if (!IsDestroy())
                    RemoveObserver(*id);
                ev.Skip();
            });

            NotifyById(*id);
        }
    };

    /**
     * @brief 상태 관리 클래스 (캡슐화용 변경 클래스)
     *
     * @tparam _Value 내부 값 타입
     */
    template <typename _Value>
    class MutableState : public State<_Value>
    {
    public:
        MutableState() = default;
        MutableState(const _Value &defaultValue) : State<_Value>(defaultValue) {}

    public:
        void Update(_Value val)
        {
            State<_Value>::Update(val);
        }
    };
}
