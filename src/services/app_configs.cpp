#include "app_configs.h"

#include "base/files/paths.h"
#include "base/log.h"

namespace
{
    constexpr const auto KEY_EMULATOR_PATH = wxT("App/EmulatorPath");
}

void services::AppConfigs::Initialize()
{
    // 구버전 데이터 제거
    auto legacyDataPath = base::GetAppLegacyDataPath();
    if (std::filesystem::exists(legacyDataPath))
    {
        base::Log(TAG, "Initialize: legacy app data removed.");
        std::filesystem::remove_all(legacyDataPath);
    }

    // wxConfig 초기화
    {
        auto configFileParentDir = m_configFilePath.parent_path();
        std::filesystem::create_directories(configFileParentDir);

        m_configs = new wxFileConfig(APP_NAME, APP_AUTHOR, wxString::FromUTF8(m_configFilePath.string()));
        wxConfigBase::Set(m_configs);

        base::Log(TAG, "Initialize: wxConfigBase::Set (path=\"{}\")", m_configFilePath.string());
    }

    // 현재 설정의 상태 통지
    {
        auto emulatorPath = GetEmulatorPath();
        if (emulatorPath)
            m_emulatorPathState.Update(*emulatorPath);
    }
}

void services::AppConfigs::Destroy()
{
    base::Log(TAG, "Destroy");

    wxConfigBase::Set(nullptr);

    delete m_configs;
    m_configs = nullptr;
}

std::optional<std::filesystem::path> services::AppConfigs::GetEmulatorPath()
{
    if (m_configs != nullptr && m_configs->Exists(KEY_EMULATOR_PATH))
    {
        const auto pathStr = m_configs->Read(KEY_EMULATOR_PATH);
        return pathStr.utf8_string();
    }
    return std::nullopt;
}

void services::AppConfigs::SetEmulatorPath(const std::filesystem::path &path)
{
    if (m_configs != nullptr)
    {
        m_configs->Write(KEY_EMULATOR_PATH, wxString::FromUTF8(path.string()));
        m_configs->Flush();

        m_emulatorPathState.Update(path);
    }
}
