#include "sidecar.h"

#include "base/strings/string_util.h"
#include "base/sidecar/rgbds.h"

#include <windows.h>

base::SidecarResult base::RunSidecar(const std::filesystem::path &binPath, const std::string &args, const std::string &cwd)
{
    SECURITY_ATTRIBUTES sa{};
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;

    HANDLE readHandle;
    HANDLE writeHandle;
    ::CreatePipe(&readHandle, &writeHandle, &sa, 0);
    ::SetHandleInformation(readHandle, HANDLE_FLAG_INHERIT, 0);

    STARTUPINFOW si{};
    PROCESS_INFORMATION pi{};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = writeHandle;
    si.hStdError = writeHandle;
    si.hStdInput = ::GetStdHandle(STD_INPUT_HANDLE);

    std::wstring cmd = L"\"" + binPath.wstring() + L"\" " + base::ToWString(args);
    const auto ok = ::CreateProcessW(
        nullptr,
        cmd.data(),
        nullptr,
        nullptr,
        true,
        CREATE_NO_WINDOW,
        nullptr,
        cwd == "" ? nullptr : base::ToWString(cwd).c_str(),
        &si,
        &pi);

    ::CloseHandle(writeHandle);

    if (!ok)
    {
        ::CloseHandle(readHandle);
        return {-1, ""};
    }

    std::string output;

    char buffer[4096];
    DWORD read = 0;
    while (::ReadFile(readHandle, buffer, sizeof(buffer) - 1, &read, nullptr) && read > 0)
    {
        buffer[read] = '\0';
        output += buffer;
    }

    ::WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exitCode;
    ::GetExitCodeProcess(pi.hProcess, &exitCode);

    ::CloseHandle(pi.hProcess);
    ::CloseHandle(pi.hThread);
    ::CloseHandle(readHandle);

    return {int(exitCode), output};
}

void base::InitializeSidecar()
{
    internal::InitializeRgbds();
}
