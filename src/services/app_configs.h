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
        base::MutableState<bool> m_showDebugLabelState = true;
        base::MutableState<bool> m_testPlaySaveState = true;
        base::MutableState<bool> m_trainerCardImageState = false;

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

        bool GetShowDebugLabel();
        void SetShowDebugLabel(bool value);
        base::State<bool> &GetShowDebugLabelState() { return m_showDebugLabelState; }

        bool GetTestPlaySave();
        void SetTestPlaySave(bool value);
        base::State<bool> &GetTestPlaySaveState() { return m_testPlaySaveState; }

        bool GetTrainerCardImage();
        void SetTrainerCardImage(bool value);
        base::State<bool> &GetTrainerCardImageState() { return m_trainerCardImageState; }
    };
}
