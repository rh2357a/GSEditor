#ifndef _POKEGOLD_STRING_H_
#define _POKEGOLD_STRING_H_

#include <wx/wx.h>

#include <string>
#include <vector>
#include <filesystem>

namespace pokegold {

class string
{
private:
    inline static std::string s_unk_string = "<UNK_STRING>";
    inline static wxString s_unk_wxstring = "<UNK_STRING>";

private:
    std::vector<u8> m_bytes;
    std::string m_cached_str = s_unk_string;
    wxString m_cached_wxstr = s_unk_wxstring;

public:
    string() = default;
    string(const char *c_str) : string(std::string(c_str)) {}
    string(const std::string &str);
    string(std::vector<u8> bytes);
    string(std::initializer_list<u8> l) : string(std::vector<u8>(l)) {}
    ~string() = default;

public:
    static void init_charmap();
    static bool is_charmap_string(std::string_view str);

    std::string editor_str();
    wxString editor_wxstr();
    std::vector<u8> data() const { return m_bytes; };

    bool has_bad_code();

public:
    auto begin() { return m_bytes.begin(); }
    auto end() { return m_bytes.end(); }
    auto begin() const { return m_bytes.begin(); }
    auto end() const { return m_bytes.end(); }

    string operator+(const string &rhs) const;
    string &operator+=(const string &rhs);
    auto operator<=>(const string &rhs) const { return m_bytes <=> rhs.m_bytes; };
    u8 &operator[](size_t idx) { return m_bytes.at(idx); }
    const u8 &operator[](size_t idx) const { return m_bytes.at(idx); }

    size_t size() const { return m_bytes.size(); };
    bool empty() const { return m_bytes.empty(); };
};

} // namespace pokegold

#endif
