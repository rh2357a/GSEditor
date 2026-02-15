#include "string_util.h"

#include <sstream>
#include <string>

wxString base::ToWxString(std::span<const u8> bytes)
{
    return wxString::FromUTF8(reinterpret_cast<const char *>(bytes.data()), bytes.size());
}

std::string base::ToString(const std::wstring &wstr)
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

std::wstring base::ToWString(const std::string &str)
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

std::wstring base::ToWString(const UCHAR *c_str)
{
    std::wstring name;
    name.assign((WCHAR *)c_str);
    return name;
}

std::string base::ReplaceAll(std::string s, const std::string &from, const std::string &to)
{
    if (from.empty())
        return s;

    size_t pos = 0;
    while ((pos = s.find(from, pos)) != std::string::npos)
    {
        s.replace(pos, from.length(), to);
        pos += to.length();
    }

    return s;
}

std::vector<std::string> base::Split(const std::string &str, char delimiter)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string item;

    while (std::getline(ss, item, delimiter))
        result.push_back(item);

    return result;
}
