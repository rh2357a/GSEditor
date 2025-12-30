#ifndef _UTILS_STRINGS_H_
#define _UTILS_STRINGS_H_

#include <minwindef.h>
#include <wx/wx.h>

#include <string>
#include <span>

namespace utils::strings {

/// @brief 문자열 변환
/// @param utf8_bytes UTF-8 바이트 배열
/// @return wx용 문자열
inline wxString to_wx_string(std::span<const u8> utf8_bytes)
{
    return wxString::FromUTF8(reinterpret_cast<const char *>(utf8_bytes.data()), utf8_bytes.size());
}

/// @brief wstr > str 변환
/// @param wstr
/// @return str
inline std::string to_string(const std::wstring &wstr)
{
    if (wstr.empty())
        return std::string();

    int size = ::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    if (size <= 0)
        return std::string();

    std::string str(size - 1, 0);
    ::WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size, NULL, NULL);

    return str;
}

/// @brief str > wstr 변환
/// @param str
/// @return wstr
inline std::wstring to_wstring(const std::string &str)
{
    if (str.empty())
        return std::wstring();

    int size = ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    if (size <= 0)
        return std::wstring();

    std::wstring wstr(size - 1, 0);
    ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size);

    return wstr;
}

inline std::wstring to_wstring(const UCHAR *c_str)
{
    std::wstring name;
    name.assign((WCHAR *)c_str);
    return name;
}

} // namespace utils::strings

#endif
