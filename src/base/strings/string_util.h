#pragma once

#include "base/types/types.h"

#include <wx/wx.h>

#include <span>
#include <string>

// 문자열 변환 함수
namespace base
{
    wxString ToWxString(std::span<const u8> bytes);

    std::string ToString(const std::wstring &wstr);
    std::wstring ToWString(const std::string &str);
    std::wstring ToWString(const UCHAR *c_str);
}

// 문자열 유틸
namespace base
{
    /// @brief 문자열 치환
    /// @param s 원본 문자열
    /// @param from 찾을 문자열
    /// @param to 변경 문자열
    /// @return 변경된 문자열
    std::string ReplaceAll(std::string s, const std::string &from, const std::string &to);

    /// @brief 문자열 분리
    /// @param s 원본 문자열
    /// @param delimiter 분리 문자
    /// @return 분리된 문자열 벡터
    std::vector<std::string> Split(const std::string &str, char delimiter);
}
