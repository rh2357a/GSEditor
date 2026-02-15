#pragma once

#ifdef __cplusplus

#include <format>

namespace base
{
    /**
     * @brief 로깅 초기화
     */
    void InitializeLog();

    /**
     * @brief 디버그 로깅
     *
     * @param tag
     * @param s
     */
    void Log(std::string_view tag, std::string_view s);

    /**
     * @brief 디버그 로깅
     *
     * @tparam _Args
     * @param tag
     * @param fmt
     * @param args
     */
    template <typename... _Args>
    inline void Log(std::string_view tag, std::format_string<_Args...> fmt, _Args &&...args)
    {
#ifdef DEBUG
        Log(tag, std::format(fmt, std::forward<_Args>(args)...));
#endif
    }
}

#endif
