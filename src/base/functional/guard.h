#pragma once

#include <functional>

namespace base
{
    /**
     * @brief 중복 호출 방지용 클래스
     */
    class Guard
    {
    private:
        int m_guardCount = 0;

    private:
        class Scope
        {
        private:
            Guard &m_guard;

        public:
            explicit Scope(Guard &guard) : m_guard(guard) { m_guard.m_guardCount++; }
            ~Scope() { m_guard.m_guardCount--; }
        };

    public:
        bool IsGuarded() const
        {
            return m_guardCount > 0;
        }

        void operator()(const std::function<void()> &func)
        {
            Scope thiz(*this);
            func();
        }
    };
}
