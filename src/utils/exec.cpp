#include "exec.h"

#include "utils.h"

#include <windows.h>

#include <iomanip>
#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <vector>

std::vector<u8> read_bin(int id)
{
    const auto module = ::GetModuleHandle(nullptr);

    const auto res = ::FindResource(module, MAKEINTRESOURCEW(id), RT_RCDATA);
    const auto res_data = ::LoadResource(module, res);
    const auto res_size = ::SizeofResource(module, res);

    const u8 *data = static_cast<const u8 *>(::LockResource(res_data));
    return std::vector<u8>(data, data + res_size);
}

void prepare_bin_file(const std::filesystem::path &exe_path, int res_id)
{
    static const auto bin_dir = utils::files::get_app_data_path() / "bin";
    std::filesystem::create_directories(bin_dir);

    if (std::filesystem::exists(exe_path))
    {
        const auto bin = read_bin(res_id);
        const auto current_bin = utils::files::read_bytes_from_file(exe_path);
        const auto bin_hash = utils::crypto::hash(bin);
        const auto current_bin_hash = utils::crypto::hash(current_bin);
        if (current_bin_hash != bin_hash)
        {
            std::filesystem::remove(exe_path);
            utils::files::write_bytes_to_file(exe_path, bin);
        }
    }
    else
    {
        const auto bin = read_bin(res_id);
        utils::files::write_bytes_to_file(exe_path, bin);
    }
}

utils::exec_result run_process(const std::filesystem::path &exe_path, const std::string &args, const std::string &cwd)
{
    SECURITY_ATTRIBUTES sa{};
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;

    HANDLE read_handle = nullptr;
    HANDLE write_handle = nullptr;
    ::CreatePipe(&read_handle, &write_handle, &sa, 0);
    ::SetHandleInformation(read_handle, HANDLE_FLAG_INHERIT, 0);

    STARTUPINFOW si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = write_handle;
    si.hStdError = write_handle;
    si.hStdInput = ::GetStdHandle(STD_INPUT_HANDLE);

    std::wstring cmd = L"\"" + exe_path.wstring() + L"\" " + utils::strings::to_wstring(args);
    const auto ok = ::CreateProcessW(
        nullptr,
        cmd.data(),
        nullptr,
        nullptr,
        true,
        CREATE_NO_WINDOW,
        nullptr,
        cwd == "" ? nullptr : utils::strings::to_wstring(cwd).c_str(),
        &si,
        &pi);

    ::CloseHandle(write_handle);

    if (!ok)
    {
        ::CloseHandle(read_handle);
        return {-1, ""};
    }

    utils::exec_result result;

    char buffer[4096];
    DWORD read = 0;
    while (::ReadFile(read_handle, buffer, sizeof(buffer) - 1, &read, nullptr) && read > 0)
    {
        buffer[read] = '\0';
        result.output += buffer;
    }

    ::WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exit_code;
    ::GetExitCodeProcess(pi.hProcess, &exit_code);
    result.exit_code = static_cast<int>(exit_code);

    ::CloseHandle(pi.hProcess);
    ::CloseHandle(pi.hThread);
    ::CloseHandle(read_handle);

    return result;
}

utils::exec_result utils::rgbasm(const std::string &args, const std::string &cwd)
{
    static const auto path = utils::files::get_app_data_path() / "bin" / "rgbasm.exe";
    return run_process(path, args, cwd);
}

utils::exec_result utils::rgblink(const std::string &args, const std::string &cwd)
{
    static const auto path = utils::files::get_app_data_path() / "bin" / "rgblink.exe";
    return run_process(path, args, cwd);
}

utils::exec_result utils::rgbfix(const std::string &args, const std::string &cwd)
{
    static const auto path = utils::files::get_app_data_path() / "bin" / "rgbfix.exe";
    return run_process(path, args, cwd);
}

void utils::init_exec()
{
    const auto bin_path = utils::files::get_app_data_path() / "bin";
    prepare_bin_file(bin_path / "rgbasm.exe", 102);
    prepare_bin_file(bin_path / "rgblink.exe", 103);
    prepare_bin_file(bin_path / "rgbfix.exe", 104);
}
