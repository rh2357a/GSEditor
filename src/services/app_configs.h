#pragma once

#include "base/files/paths.h"
#include "base/functional/state.h"

#include <wx/fileconf.h>
#include <wx/wx.h>

#include <filesystem>
#include <optional>

namespace services
{
    class AppConfigs
    {
    private:
        inline static const auto TAG = "services::AppConfigs";

    private:
        std::filesystem::path m_configFilePath;
        wxFileConfig *m_configs = nullptr;

        base::MutableState<std::filesystem::path> m_emulatorPathState = base::GetNullPath();

    public:
        AppConfigs(std::filesystem::path configFilePath)
            : m_configFilePath(configFilePath) {};

    public:
        static AppConfigs &Default()
        {
            static AppConfigs instance = [] {
                auto appDataPath = base::GetAppDataPath();
                return appDataPath / "app_configs.ini";
            }();

            return instance;
        }

        void Initialize();
        void Destroy();

        std::optional<std::filesystem::path> GetEmulatorPath();
        void SetEmulatorPath(const std::filesystem::path &path);
        base::State<std::filesystem::path> &GetEmulatorPathState() { return m_emulatorPathState; }
    };
}
