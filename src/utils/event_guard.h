#ifndef _UTILS_EVENT_GUARD_H_
#define _UTILS_EVENT_GUARD_H_

#include <functional>

namespace utils {

// 더티 플래그 캡슐화
class event_guard
{
private:
    int m_guard_count = 0;

private:
    class scope
    {
    private:
        event_guard &g;

    public:
        explicit scope(event_guard &guard) : g(guard) { g.m_guard_count++; }
        ~scope() { g.m_guard_count--; }
    };

public:
    bool is_guarded() const
    {
        return m_guard_count > 0;
    }

    void operator()(const std::function<void()> &func)
    {
        scope thiz(*this);
        func();
    }
};

} // namespace utils

#endif
