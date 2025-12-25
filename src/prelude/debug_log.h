#ifndef _PRELUDE_DEBUG_LOG_H_
#define _PRELUDE_DEBUG_LOG_H_

#include <string>
#include <sstream>
#include <iostream>
#include <format>
#include <chrono>
#include <ctime>
#include <iomanip>

inline void debug_log(const std::string &tag, const std::string &s)
{
#ifdef DEBUG
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
#endif
}

template <typename... _Args>
inline void debug_log(const std::string &tag, std::format_string<_Args...> fmt, _Args &&...args)
{
#ifdef DEBUG
    debug_log(tag, std::format(fmt, std::forward<_Args>(args)...));
#endif
}

#endif
