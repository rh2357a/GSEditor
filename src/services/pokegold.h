#pragma once

#include "base/files/paths.h"
#include "base/progress.h"
#include "base/sidecar/sidecar.h"
#include "services/app_configs.h"
#include "services/pokegold/data.h"
#include "services/pokegold/utils.h"

#include <filesystem>
#include <optional>

namespace services
{
    class Pokegold
    {
    private:
        inline static const auto TAG = "pokegold::Pokegold";

        inline static const std::string s_baseName = "base";
        inline static const std::string s_targetName = "target";

    public:
        pokegold::Data Data;

    private:
        services::AppConfigs &m_appConfigs = services::AppConfigs::Default();

        base::MutableState<bool> m_isOpenedState = false;
        base::MutableState<bool> m_isDataChangedState = false;
        base::MutableState<std::filesystem::path> m_romFilePathState = base::NullPath;
        base::MutableState<std::filesystem::path> m_workspacePathState = base::NullPath;

        base::MutableProgressState m_openProgressState{2835};
        base::MutableProgressState m_buildProgressState{5839};

    public:
        static Pokegold &Default()
        {
            static Pokegold instance;
            return instance;
        }

        base::State<bool> &IsOpenedState() { return m_isOpenedState; }
        base::State<bool> &IsDataChangedState() { return m_isDataChangedState; }
        base::State<std::filesystem::path> &FilePathState() { return m_romFilePathState; }

        base::ProgressState &OpenProgressState() { return m_openProgressState; }
        base::ProgressState &BuildProgressState() { return m_buildProgressState; }

        /**
         * @brief 롬 파일이 변경됨을 통지
         */
        void NotifyRomChanged() { m_isDataChangedState.Update(true); }

        /**
         * @brief 롬 파일이 저장됨을 통지
         */
        void NotifyRomSaved() { m_isDataChangedState.Update(false); }

        /**
         * @brief 테스트 플레이 실행
         *
         * @return base::SidecarResult
         * @see Build 빌드가 먼저 되어 있어야 함
         */
        base::SidecarResult RunTestPlay();

        /**
         * @brief 롬 파일 열기
         *
         * @param romFilePath 롬 파일 경로
         * @return true 성공
         * @return false 취소 또는 실패
         * @see OpenProgressState 진행 상태 구독 함수
         */
        bool Open(const std::filesystem::path &romFilePath);

        /**
         * @brief 롬 파일 빌드
         *
         * @return 빌드된 롬 파일 임시 경로
         * @return std::nullopt 취소 또는 실패
         * @see BuildProgressState 진행 상태 구독 함수
         */
        std::optional<std::filesystem::path> Build();

    private:
        bool Open_ReadItems(pokegold::Data &data);
        bool Open_ReadMoves(pokegold::Data &data);
        bool Open_ReadPokemons(pokegold::Data &data);
        bool Open_ReadTrainerGroups(pokegold::Data &data);
        bool Open_ReadTypes(pokegold::Data &data);
        bool Open_ReadMaps(pokegold::Data &data);

        bool Build_Startup(pokegold::internal::RomBuildData &data);
        bool Build_ItemSources(pokegold::internal::RomBuildData &data);
        bool Build_MoveSources(pokegold::internal::RomBuildData &data);
        bool Build_PokemonSources(pokegold::internal::RomBuildData &data);
        bool Build_TrainerGroupSources(pokegold::internal::RomBuildData &data);
        bool Build_TypeSources(pokegold::internal::RomBuildData &data);
        bool Build_MapsSources(pokegold::internal::RomBuildData &data);
        bool Build_HackSources(pokegold::internal::RomBuildData &data);
        bool Build_Assemble(pokegold::internal::RomBuildData &data);
    };
}
