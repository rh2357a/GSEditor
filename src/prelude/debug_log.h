#ifndef _PRELUDE_DEBUG_LOG_H_
#define _PRELUDE_DEBUG_LOG_H_

#ifdef __cplusplus

#include <string>
#include <sstream>
#include <iostream>
#include <format>
#include <chrono>
#include <ctime>
#include <iomanip>

constexpr bool TEST = false;
constexpr const char LOG_FILENAME[] = "GSEditor.log";

inline void init_logging()
{
    if constexpr (DEBUG_MODE || TEST)
    {
        freopen(LOG_FILENAME, "w", stdout);
        freopen(LOG_FILENAME, "a", stderr);
        setvbuf(stdout, nullptr, _IONBF, 0);
        setvbuf(stderr, nullptr, _IONBF, 0);
        std::ios::sync_with_stdio(true);
    }
    else
    {
        std::ios::sync_with_stdio(false);
    }
}

inline void debug_log(const std::string &tag, const std::string &s)
{
    if constexpr (DEBUG_MODE || TEST)
    {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto in_time_t = system_clock::to_time_t(now);
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

        std::tm buf;
        localtime_s(&buf, &in_time_t);

        std::ostringstream oss;
        oss << std::put_time(&buf, "%Y%m%d.%H%M%S")
            << '.' << std::setfill('0') << std::setw(3) << ms.count();

        std::cout << '[' << oss.str() << ']'
                  << '[' << tag << "] "
                  << s
                  << '\n';
    }
}

template <typename... _Args>
inline void debug_log(const std::string &tag, std::format_string<_Args...> fmt, _Args &&...args)
{
    if constexpr (DEBUG_MODE || TEST)
        debug_log(tag, std::format(fmt, std::forward<_Args>(args)...));
}

#endif

#endif
