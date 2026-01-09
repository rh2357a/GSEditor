#ifndef _UTILS_EXEC_H_
#define _UTILS_EXEC_H_

#include <string>
#include <filesystem>

namespace utils {

struct exec_result
{
    int exit_code;
    std::string output;
};

exec_result run_process(const std::filesystem::path &exe_path, const std::string &args, const std::string &cwd);

exec_result rgbasm(const std::string &args, const std::string &cwd = "");
exec_result rgblink(const std::string &args, const std::string &cwd = "");
exec_result rgbfix(const std::string &args, const std::string &cwd = "");

void init_exec();

} // namespace utils

#endif
