#include "pokegold.h"

#include "base/log.h"
#include "base/sidecar/sidecar.h"
#include "services/app_configs.h"

#include <filesystem>

namespace
{
    const base::SidecarResult k_emulatorNotFoundResult{-1, "-"};
    const base::SidecarResult k_romNotFoundResult{-2, "-"};
}

base::SidecarResult services::Pokegold::RunTestPlay()
{
    auto emulatorPath = services::AppConfigs::Default().GetEmulatorPath();
    if (!emulatorPath.has_value())
    {
        base::Log(TAG, "RunTestPlay: emulator not found");
        return k_emulatorNotFoundResult;
    }

    auto romPath = *m_workspacePathState / (s_targetName + ".bin");
    if (!std::filesystem::exists(romPath))
    {
        base::Log(TAG, "RunTestPlay: target rom file not found");
        return k_romNotFoundResult;
    }

    auto result = base::RunSidecar(*emulatorPath, romPath.string(), (*m_workspacePathState).string());

    // 테스트 종료 후, 세이브 파일 덮어쓰기
    if (m_appConfigs.GetTestPlaySave())
    {
        auto savePath = (*m_romFilePathState).parent_path() / ((*m_romFilePathState).stem().string() + ".sav");
        auto targetSavePath = *m_workspacePathState / (s_targetName + ".sav");
        if (std::filesystem::exists(targetSavePath))
            std::filesystem::copy_file(targetSavePath, savePath, std::filesystem::copy_options::overwrite_existing);
    }

    return result;
}
