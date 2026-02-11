#pragma once

#include "base/types/types.h"

#include <wx/wx.h>

#include <string>
#include <span>

namespace pokegold
{
    class String
    {
    private:
        inline static std::string s_unkString = "<UNK_STRING>";
        inline static wxString s_unkWxString = "<UNK_STRING>";

    private:
        std::vector<u8> m_bytes;
        std::string m_cachedStr = s_unkString;
        wxString m_cachedWxStr = s_unkWxString;

    public:
        String() = default;
        String(const char *c_str) : String(std::string(c_str)) {}
        String(const std::string &str);
        String(std::span<const u8> bytes);
        ~String() = default;

    public:
        static void InitializeCharmap();
        static bool IsCharmapString(std::string_view str);

        std::string ToEditorString();
        wxString ToEditorWxString();

        const std::vector<u8> &GetData() const { return m_bytes; };

        bool HasBadData() const;
    };
}
