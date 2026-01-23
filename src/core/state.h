#ifndef _CORE_STATE_H_
#define _CORE_STATE_H_

#include <functional>
#include <vector>

namespace core {

template <typename _ValueType>
class state
{
private:
    using _Observer = std::function<void(const _ValueType)>;
    using _Binder = std::function<void(state<_ValueType> &)>;

private:
    bool m_dirty = false;
    _ValueType m_value;
    std::vector<_Observer> m_observers;

public:
    state() = default;
    state(_ValueType default_value) : m_value(default_value) {}
    ~state() = default;

public:
    _ValueType &operator*() & { return get(); }
    const _ValueType &operator*() const & { return get(); }
    _ValueType get() const { return m_value; }

    void operator=(_ValueType val) { set(val); }
    void set(_ValueType val)
    {
        m_value = val;
        notify();
    }

public:
    void bind(const _Binder binder, const _Observer observer)
    {
        binder(*this);
        observe(observer);
    }

    void observe(const _Observer observer) { m_observers.push_back(observer); }
    void notify()
    {
        if (!m_dirty)
        {
            m_dirty = true;
            for (const auto &obs : m_observers)
                obs(m_value);
            m_dirty = false;
        }
    }
};

} // namespace core

#endif
