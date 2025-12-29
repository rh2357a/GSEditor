#ifndef _POKEGOLD_ROMFILE_H_
#define _POKEGOLD_ROMFILE_H_

#include "pokegold/address.h"
#include "pokegold/bytes.h"

#include <filesystem>
#include <vector>
#include <functional>

namespace pokegold {

class romfile
{
private:
    std::filesystem::path m_path;
    std::filesystem::path m_build_data_path;
    std::vector<u8> m_bytes;

public:
    romfile() = default;
    romfile(std::filesystem::path filepath);

public:
    const std::filesystem::path &rom_path() const { return m_path; }
    const std::filesystem::path &build_data_path() const { return m_build_data_path; }
    const std::vector<u8> &data() const { return m_bytes; }

public:
    u8 get_byte(size_t addr);
    bytes get_bytes(size_t addr, size_t len);
    bytes get_bytes_until(size_t addr, std::function<bool(size_t, u8)> predicate, bool include_end = false);

public:
    size_t read_lz_decompressed(std::vector<u8> &dst, size_t offset, size_t size);

public:
    void set_byte(size_t addr, u8 byte);
    void set_bytes(size_t addr, const std::vector<u8> &bytes);
    void fill_bytes(u8 byte, size_t addr, size_t len);
};

} // namespace pokegold

#endif
