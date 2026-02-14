#pragma once

#include <filesystem>
#include <string>

namespace base
{
    /// @brief sidecar 결과가 기록되는 클래스
    class SidecarResult
    {
    private:
        int m_exitCode;
        std::string m_output;

    public:
        SidecarResult(int exitCode, const std::string &output) : m_exitCode(exitCode), m_output(output) {}
        SidecarResult(int exitCode, std::string &&output) : m_exitCode(exitCode), m_output(std::move(output)) {}

    public:
        int GetExitCode() const { return m_exitCode; }
        std::string GetOutput() const { return m_output; }
    };
}

namespace base
{
    /// @brief sidecar 초기화
    void InitializeSidecar();

    /// @brief 프로세스 실행
    /// @param binPath 실행 실제 경로
    /// @param args 실행 인자값
    /// @param cwd 작업 디렉터리 경로
    /// @return 결과
    SidecarResult RunSidecar(const std::filesystem::path &binPath, const std::string &args, const std::string &cwd);
}
