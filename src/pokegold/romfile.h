#ifndef _POKEGOLD_ROMFILE_H_
#define _POKEGOLD_ROMFILE_H_

#include "pokegold/address.h"
#include "pokegold/bytes.h"

#include <cstdint>
#include <filesystem>
#include <vector>
#include <functional>

namespace pokegold {

class romfile
{
private:
    std::filesystem::path m_path;
    std::vector<uint8_t> m_bytes;

public:
    romfile() = default;
    romfile(std::filesystem::path filepath);

public:
    const std::vector<uint8_t> &data() const { return m_bytes; }

public:
    void read_bytes(std::vector<uint8_t> &bytes, size_t addr, size_t len);
    uint8_t get_byte(size_t addr);
    bytes get_bytes(size_t addr, size_t len);
    bytes get_bytes_until(size_t addr, std::function<bool(size_t, uint8_t)> predicate, bool include_end = false);

public:
    void set_byte(size_t addr, uint8_t byte);
    void set_bytes(size_t addr, const std::vector<uint8_t> &bytes);
    void fill_bytes(uint8_t byte, size_t addr, size_t len);
};

} // namespace pokegold

#endif
