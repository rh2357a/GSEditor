#pragma once

#include <wx/wx.h>

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

namespace ui
{
    /**
     * @brief 파일 선택창 열기
     *
     * @param parent 부모 윈도우
     * @param title 제목
     * @param filter 파일 형식 목록
     * @return 선택한 파일의 경로를 반환
     * @return std::nullopt 선택 취소
     */
    std::optional<std::filesystem::path> ShowOpenFileDialog(wxWindow *parent, const std::string &title, const std::vector<std::string> &filter);

    /**
     * @brief 파일 저장 선택창 열기
     *
     * @param parent 부모 윈도우
     * @param title 제목
     * @param filter 파일 형식 목록
     * @return 파일을 저장할 경로를 반환
     * @return std::nullopt 선택 취소
     */
    std::optional<std::filesystem::path> ShowSaveFileDialog(wxWindow *parent, const std::string &title, const std::vector<std::string> &filter);
}
