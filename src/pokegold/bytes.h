#ifndef _POKEGOLD_BYTES_H_
#define _POKEGOLD_BYTES_H_

#include <string>
#include <vector>
#include <filesystem>

namespace pokegold {

class bytes
{
private:
    inline static std::string s_unk_string = "<UNK_STRING>";

private:
    std::vector<u8> m_bytes;
    std::string m_cached_str = s_unk_string;

public:
    bytes() = default;
    bytes(const char *c_str) : bytes(std::string(c_str)) {}
    bytes(const std::string &str);
    bytes(std::initializer_list<u8> l) : bytes(std::vector<u8>(l)) {}
    bytes(std::vector<u8> bytes);
    ~bytes() = default;

public:
    static void init_charmap();
    static bool is_charmap_string(const std::string &str);
    std::string string();

    static void setup_lzcomp_workdir(const std::filesystem::path &dir);
    static bool is_lz_compressed(const std::vector<u8> &bytes);
    static size_t scan_lz_size(const std::vector<u8> &bytes);
    bytes compressed() const;
    bytes decompressed() const;

public:
    operator std::string() { return string(); }
    operator std::vector<u8>() const { return m_bytes; };

    auto begin() { return m_bytes.begin(); }
    auto end() { return m_bytes.end(); }
    auto begin() const { return m_bytes.begin(); }
    auto end() const { return m_bytes.end(); }

    bytes operator+(const bytes &rhs) const;
    bytes &operator+=(const bytes &rhs);
    auto operator<=>(const bytes &rhs) const { return m_bytes <=> rhs.m_bytes; };
    u8 &operator[](size_t idx) { return m_bytes.at(idx); }
    const u8 &operator[](size_t idx) const { return m_bytes.at(idx); }

    size_t size() const { return m_bytes.size(); };
    bool empty() const { return m_bytes.empty(); };
};

} // namespace pokegold

#endif
