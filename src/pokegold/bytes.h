#ifndef _POKEGOLD_BYTES_H_
#define _POKEGOLD_BYTES_H_

#include <cstdint>
#include <string>
#include <vector>

namespace pokegold {

class bytes
{
private:
    inline static std::string s_unk_string = "<UNK_STRING>";

private:
    std::vector<uint8_t> m_bytes;
    std::string m_cached_str = s_unk_string;

public:
    bytes() = default;
    bytes(const char *c_str) : bytes(std::string(c_str)) {}
    bytes(const std::string &str);
    bytes(std::initializer_list<uint8_t> l) : bytes(std::vector<uint8_t>(l)) {}
    bytes(std::vector<uint8_t> bytes);
    ~bytes() = default;

public:
    static void init_charmap();
    static bool is_charmap_string(const std::string &str);
    std::string string();

    static bool is_lz_compressed(const std::vector<uint8_t> &bytes);
    static size_t scan_lz_size(const std::vector<uint8_t> &bytes);
    bytes compressed() const;
    bytes decompressed() const;

public:
    operator std::string() { return string(); }
    operator std::vector<uint8_t>() const { return m_bytes; };

    auto begin() { return m_bytes.begin(); }
    auto end() { return m_bytes.end(); }
    auto begin() const { return m_bytes.begin(); }
    auto end() const { return m_bytes.end(); }

    bytes operator+(const bytes &rhs) const;
    bytes &operator+=(const bytes &rhs);
    auto operator<=>(const bytes &rhs) const { return m_bytes <=> rhs.m_bytes; };
    uint8_t &operator[](size_t idx) { return m_bytes.at(idx); }
    const uint8_t &operator[](size_t idx) const { return m_bytes.at(idx); }

    size_t size() const { return m_bytes.size(); };
    bool empty() const { return m_bytes.empty(); };
};

} // namespace pokegold

#endif
