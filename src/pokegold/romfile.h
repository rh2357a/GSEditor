#ifndef _POKEGOLD_ROMFILE_H_
#define _POKEGOLD_ROMFILE_H_

#include <filesystem>
#include <vector>
#include <span>
#include <functional>

namespace pokegold::romfile {

inline bool is_opened = false;
inline std::filesystem::path path, save_path, build_data_path;
inline std::filesystem::path workspace_path;
inline std::vector<u8> data;

} // namespace pokegold::romfile

namespace pokegold::romfile {

void open(const std::filesystem::path &filepath);
void close();

} // namespace pokegold::romfile

namespace pokegold::romfile {

u8 get_byte(size_t addr);
std::vector<u8> get_bytes(size_t addr, size_t len);
std::vector<u8> get_bytes_until(size_t addr, std::function<bool(size_t, u8)> predicate, bool include_end = false);

size_t calc_lz_size(size_t offset, size_t buffer_size);
size_t read_lz_decompressed(std::span<u8> dst, size_t offset, size_t size);

void set_byte(size_t addr, u8 byte);
void set_bytes(size_t addr, const std::vector<u8> &bytes);
void fill_bytes(u8 byte, size_t addr, size_t len);

} // namespace pokegold::romfile

#endif
