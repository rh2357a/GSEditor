#include "log.h"

#include <iostream>
#include <chrono>

constexpr const char LOG_FILENAME[] = "GSEditor.log";

void base::InitializeLog()
{
#ifdef DEBUG
    freopen(LOG_FILENAME, "w", stdout);
    freopen(LOG_FILENAME, "a", stderr);
    setvbuf(stdout, nullptr, _IONBF, 0);
    setvbuf(stderr, nullptr, _IONBF, 0);
    std::ios::sync_with_stdio(true);
#else
    std::ios::sync_with_stdio(false);
#endif
}

void base::Log(std::string_view tag, std::string_view s)
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
