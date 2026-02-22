#pragma once

#include "base/files/paths.h"
#include "base/progress.h"
#include "base/sidecar/sidecar.h"
#include "base/types/types.h"
#include "services/app_configs.h"
#include "services/pokegold/data.h"
#include "utils/free_space.h"

#include <lzcomp/lzcomp.h>

#include <filesystem>
#include <fstream>
#include <optional>
#include <vector>

namespace pokegold::internal
{
    class RomBuildData
    {
    private:
        std::ofstream m_source;
        std::ofstream m_namesSource;
        std::ofstream m_imagesSource;
        std::ofstream m_typeNamesSource;

        std::vector<u8> m_lzcompBuffer = std::vector<u8>(0x400);

        FreeSpaceDataResolver m_imageDataBlocks;
        FreeSpaceDataResolver m_typeNameDataBlocks;

    public:
        RomBuildData(const std::filesystem::path &workdir)
            : m_source(workdir / "GSEditor.asm"),
              m_namesSource(workdir / "GSEditor.Names.asm"),
              m_imagesSource(workdir / "GSEditor.Images.asm"),
              m_typeNamesSource(workdir / "GSEditor.TypeNames.asm") {}

    public:
        auto &GetSourceStream() { return m_source; }
        auto &GetNamesSourceStream() { return m_namesSource; }
        auto &GetImagesSourceStream() { return m_imagesSource; }
        auto &GetTypeNameSourceStream() { return m_typeNamesSource; }

        auto &GetImageDataBlocks() { return m_imageDataBlocks; }
        auto &GetTypeNameDataBlocks() { return m_typeNameDataBlocks; }

        void PushImageDataBlock(std::string label, std::span<const u8> data)
        {
            size_t lzSize = lzcomp::Compress(m_lzcompBuffer, data);
            m_imageDataBlocks.Push(label, {m_lzcompBuffer.begin(), m_lzcompBuffer.begin() + lzSize});
        }
    };
}

namespace pokegold
{
    class Rom
    {
    private:
        inline static const auto TAG = "pokegold::Rom";

        inline static const std::string s_baseName = "base";
        inline static const std::string s_targetName = "target";

    private:
        services::AppConfigs &m_appConfigs = services::AppConfigs::Default();

        Data &m_data;

        base::MutableState<bool> m_romOpenedState = false;
        base::MutableState<bool> m_romDataChangedState = false;
        base::MutableState<std::filesystem::path> m_romFilePathState = base::GetNullPath();
        base::MutableState<std::filesystem::path> m_workspacePathState = base::GetNullPath();

        base::MutableProgressState m_openProgressState{2792};
        base::MutableProgressState m_buildProgressState{4823};

    public:
        Rom(Data &data) : m_data(data) {}

    public:
        base::State<bool> &Opened() { return m_romOpenedState; }
        base::State<bool> &DataChanged() { return m_romDataChangedState; }
        base::State<std::filesystem::path> &FilePath() { return m_romFilePathState; }

        base::ProgressState &OpenProgressState() { return m_openProgressState; }
        base::ProgressState &BuildProgressState() { return m_buildProgressState; }

        /**
         * @brief 롬 파일이 변경됨을 통지
         */
        void NotifyRomChanged() { m_romDataChangedState.Update(true); }

        /**
         * @brief 롬 파일이 저장됨을 통지
         */
        void NotifyRomSaved() { m_romDataChangedState.Update(false); }

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
        bool Open_ReadItems(Data &data);
        bool Open_ReadMoves(Data &data);
        bool Open_ReadPokemons(Data &data);
        bool Open_ReadTrainerGroups(Data &data);
        bool Open_ReadTypes(Data &data);

        bool Build_Startup(internal::RomBuildData &data);
        bool Build_ItemSources(internal::RomBuildData &data);
        bool Build_MoveSources(internal::RomBuildData &data);
        bool Build_PokemonSources(internal::RomBuildData &data);
        bool Build_TrainerGroupSources(internal::RomBuildData &data);
        bool Build_TypeSources(internal::RomBuildData &data);
        bool Build_Assemble(internal::RomBuildData &data);
    };
}
