#ifndef _CORE_EVENT_H_
#define _CORE_EVENT_H_

#include <functional>
#include <utility>
#include <unordered_map>
#include <vector>

namespace core {

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
    bool is_guarded() const { return m_guard_count > 0; }

    void operator()(const std::function<void()> &func)
    {
        scope thiz(*this);
        func();
    }
};

} // namespace core

namespace core {

class subscription
{
private:
    std::function<void()> m_unsubscribe_func;

public:
    subscription() = default;
    explicit subscription(std::function<void()> fn) : m_unsubscribe_func(std::move(fn)) {}
    subscription(const subscription &) = delete;
    subscription &operator=(const subscription &) = delete;
    subscription(subscription &&other) noexcept : m_unsubscribe_func(std::move(other.m_unsubscribe_func)) { other.m_unsubscribe_func = nullptr; }
    ~subscription() { reset(); }

public:
    explicit operator bool() const noexcept { return static_cast<bool>(m_unsubscribe_func); }

    subscription &operator=(subscription &&other)
    {
        if (this != &other)
        {
            reset();
            m_unsubscribe_func = std::move(other.m_unsubscribe_func);
            other.m_unsubscribe_func = nullptr;
        }

        return *this;
    }

    void reset()
    {
        if (m_unsubscribe_func)
        {
            m_unsubscribe_func();
            m_unsubscribe_func = nullptr;
        }
    }
};

class subscriptions
{
private:
    std::vector<subscription> m_subscriptions;

public:
    subscriptions() = default;
    subscriptions(const subscriptions &) = delete;
    subscriptions &operator=(const subscriptions &) = delete;
    subscriptions(subscriptions &&) = default;
    subscriptions &operator=(subscriptions &&) = default;

public:
    template <typename _Subject, typename _Observer>
    void subscribe(_Subject &subject, _Observer &&observer) { m_subscriptions.emplace_back(subject.subscribe(std::forward<_Observer>(observer))); }
    void clear() { m_subscriptions.clear(); }
    bool empty() const noexcept { return m_subscriptions.empty(); }
};

template <typename... _Args>
class event
{
private:
    bool m_alive = true;
    size_t m_current_id = 0;
    std::unordered_map<size_t, std::function<void(_Args...)>> m_observers;

public:
    ~event() { m_alive = false; }

public:
    subscription subscribe(std::function<void(_Args...)> observer)
    {
        const size_t id = m_current_id++;
        m_observers.emplace(id, std::move(observer));
        return subscription([this, id]() {
            if (m_alive)
                m_observers.erase(id);
        });
    }

    void operator()(_Args... args)
    {
        std::vector<size_t> ids;
        ids.reserve(m_observers.size());

        for (const auto &[id, _] : m_observers)
            ids.push_back(id);

        for (size_t id : ids)
        {
            if (auto it = m_observers.find(id); it != m_observers.end())
                it->second(args...);
        }
    }
};

} // namespace core

#endif
