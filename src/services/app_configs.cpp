#include "app_configs.h"

#include "base/files/paths.h"
#include "base/log.h"
#include "base/resources.h"

namespace
{
    constexpr const auto k_emulatorPathKey = wxT("App/EmulatorPath");

    constexpr const auto k_showDebugLabelKey = wxT("App/TestPlay/ShowDebugLabel");
    constexpr const auto k_testPlaySaveKey = wxT("App/TestPlay/TestPlaySave");

    constexpr const auto k_trainerCardImageKey = wxT("App/Build/TrainerCardImage");
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

        m_showDebugLabelState.Update(GetShowDebugLabel());
        m_testPlaySaveState.Update(GetTestPlaySave());
    }
}

void services::AppConfigs::Destroy()
{
    base::Log(TAG, "Destroy");

    wxConfigBase::Set(nullptr);

    delete m_configs;
    m_configs = nullptr;
}

///////////////////////////////////////////////////////////////////////////////

std::optional<std::filesystem::path> services::AppConfigs::GetEmulatorPath()
{
    if (m_configs != nullptr && m_configs->Exists(k_emulatorPathKey))
    {
        const auto pathStr = m_configs->Read(k_emulatorPathKey);
        return pathStr.utf8_string();
    }
    return std::nullopt;
}

void services::AppConfigs::SetEmulatorPath(const std::filesystem::path &path)
{
    if (m_configs != nullptr)
    {
        m_configs->Write(k_emulatorPathKey, wxString::FromUTF8(path.string()));
        m_configs->Flush();

        m_emulatorPathState.Update(path);
    }
}

///////////////////////////////////////////////////////////////////////////////

bool services::AppConfigs::GetShowDebugLabel()
{
    if (m_configs != nullptr && m_configs->Exists(k_showDebugLabelKey))
    {
        const bool value = m_configs->ReadBool(k_showDebugLabelKey, true);
        return value;
    }
    return true;
}

void services::AppConfigs::SetShowDebugLabel(bool value)
{
    if (m_configs != nullptr)
    {
        m_configs->Write(k_showDebugLabelKey, value);
        m_configs->Flush();

        m_showDebugLabelState.Update(value);
    }
}

///////////////////////////////////////////////////////////////////////////////

bool services::AppConfigs::GetTestPlaySave()
{
    if (m_configs != nullptr && m_configs->Exists(k_testPlaySaveKey))
    {
        const bool value = m_configs->ReadBool(k_testPlaySaveKey, true);
        return value;
    }
    return true;
}

void services::AppConfigs::SetTestPlaySave(bool value)
{
    if (m_configs != nullptr)
    {
        m_configs->Write(k_testPlaySaveKey, value);
        m_configs->Flush();

        m_testPlaySaveState.Update(value);
    }
}

///////////////////////////////////////////////////////////////////////////////

bool services::AppConfigs::GetTrainerCardImage()
{
    if (m_configs != nullptr && m_configs->Exists(k_trainerCardImageKey))
    {
        const bool value = m_configs->ReadBool(k_trainerCardImageKey, false);
        return value;
    }
    return false;
}

void services::AppConfigs::SetTrainerCardImage(bool value)
{
    if (m_configs != nullptr)
    {
        m_configs->Write(k_trainerCardImageKey, value);
        m_configs->Flush();

        m_trainerCardImageState.Update(value);
    }
}
