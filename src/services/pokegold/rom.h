#pragma once

#include "base/files/paths.h"
#include "base/progress.h"
#include "services/pokegold/data.h"

#include <filesystem>
#include <fstream>
#include <optional>

namespace pokegold::internal
{
    class RomBuildData
    {
    private:
        std::filesystem::path m_workDir;
        std::filesystem::path m_baseromPath;

        std::ofstream m_source;

    public:
        RomBuildData(std::filesystem::path workDir)
            : m_workDir(std::move(workDir)),
              m_baseromPath(m_workDir / "base.bin"),
              m_source(m_workDir / "GSEditor.asm") {}

    public:
        auto &WorkDir() { return m_workDir; }
        auto &BaseromPath() { return m_baseromPath; }
        auto &SourceStream() { return m_source; }
    };
}

namespace pokegold
{
    class Rom
    {
    private:
        inline static const auto TAG = "pokegold::Rom";

    private:
        Data &m_data;

        base::MutableState<bool> m_romOpenedState = false;
        base::MutableState<bool> m_romDataChangedState = false;
        base::MutableState<std::filesystem::path> m_romFilePathState = base::GetNullPath();
        base::MutableState<std::filesystem::path> m_workspacePathState = base::GetNullPath();

        base::MutableProgressState m_openProgressState = {2792};
        base::MutableProgressState m_buildProgressState = {0};

    public:
        Rom(Data &data) : m_data(data) {}

    public:
        base::State<bool> &Opened() { return m_romOpenedState; }
        base::State<bool> &DataChanged() { return m_romDataChangedState; }
        base::State<std::filesystem::path> &FilePath() { return m_romFilePathState; }

        base::ProgressState &OpenProgressState() { return m_openProgressState; }
        base::ProgressState &BuildProgressState() { return m_buildProgressState; }

        /// @brief 롬 파일 열기, `OpenProgressState` 함수로 상태 구독 가능
        /// @param romFilePath 롬 파일 경로
        /// @return 성공 유무
        bool Open(const std::filesystem::path &romFilePath);

        /// @brief 롬 파일 빌드, `BuildProgressState` 함수로 상태 구독 가능
        /// @return 빌드된 파일 경로, 실패 시 `std::nullopt`를 반환
        std::optional<std::filesystem::path> Build();

    private:
        bool Open_ReadItems(Data &data);
        bool Open_ReadMoves(Data &data);
        bool Open_ReadPokemons(Data &data);
        bool Open_ReadTrainerGroups(Data &data);
        bool Open_ReadTypes(Data &data);

        bool Build_Startup(internal::RomBuildData &data);
        bool Build_CommonSources(internal::RomBuildData &data);
        bool Build_ItemSources(internal::RomBuildData &data);
        bool Build_MoveSources(internal::RomBuildData &data);
        bool Build_PokemonSources(internal::RomBuildData &data);
        bool Build_TrainerGroupSources(internal::RomBuildData &data);
        bool Build_TypeSources(internal::RomBuildData &data);
    };
}
