#ifndef _UTILS_SIGNAL_H_
#define _UTILS_SIGNAL_H_

#include <functional>
#include <unordered_map>
#include <vector>
#include <utility>

namespace utils {

class subscription
{
private:
    std::function<void()> m_unsubscribe_func;

public:
    subscription() = default;

    explicit subscription(std::function<void()> fn) : m_unsubscribe_func(std::move(fn)) {}

    subscription(const subscription &) = delete;
    subscription &operator=(const subscription &) = delete;

    subscription(subscription &&other) noexcept : m_unsubscribe_func(std::move(other.m_unsubscribe_func))
    {
        other.m_unsubscribe_func = nullptr;
    }

    subscription &operator=(subscription &&other) noexcept
    {
        if (this != &other)
        {
            reset();
            m_unsubscribe_func = std::move(other.m_unsubscribe_func);
            other.m_unsubscribe_func = nullptr;
        }

        return *this;
    }

    ~subscription()
    {
        reset();
    }

    void reset()
    {
        if (m_unsubscribe_func)
        {
            m_unsubscribe_func();
            m_unsubscribe_func = nullptr;
        }
    }

    explicit operator bool() const noexcept
    {
        return static_cast<bool>(m_unsubscribe_func);
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

    template <typename _Subject, typename _Observer>
    void subscribe(_Subject &subject, _Observer &&observer)
    {
        m_subscriptions.emplace_back(subject.subscribe(std::forward<_Observer>(observer)));
    }

    void clear()
    {
        m_subscriptions.clear();
    }

    bool empty() const noexcept
    {
        return m_subscriptions.empty();
    }
};

template <typename... Args>
class event
{
private:
    bool m_alive = true;
    size_t m_current_id = 0;
    std::unordered_map<size_t, std::function<void(Args...)>> m_observers;

public:
    ~event() { m_alive = false; }

    subscription subscribe(std::function<void(Args...)> observer)
    {
        const size_t id = m_current_id++;
        m_observers.emplace(id, std::move(observer));
        return subscription([this, id]() {
            if (m_alive)
                m_observers.erase(id);
        });
    }

    void operator()(Args... args)
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

} // namespace utils

#endif
