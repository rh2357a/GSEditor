#pragma once

#include "base/types/types.h"

#include <wx/wx.h>

#include <span>
#include <string>

/**
 * @brief 문자열 관련 함수
 */
namespace base
{
    wxString ToWxString(std::span<const u8> bytes);

    std::string ToString(const std::wstring &wstr);
    std::wstring ToWString(const std::string &str);
    std::wstring ToWString(const UCHAR *c_str);
}

/**
 * @brief 문자열 유틸 함수
 */
namespace base
{
    /**
     * @brief 특정 문자열 치환
     *
     * @param s 원본 문자열
     * @param from 변경될 대상 문자열
     * @param to 변경된 문자열
     * @return std::string 치환 결과
     */
    std::string ReplaceAll(std::string s, const std::string &from, const std::string &to);

    /**
     * @brief 특정 문자를 기준으로 문자열을 분리
     *
     * @param str 원본 문자열
     * @param delimiter 기준이 될 문자값
     * @return std::vector<std::string> 분리된 문자열 벡터
     */
    std::vector<std::string> Split(const std::string &str, char delimiter);
}
