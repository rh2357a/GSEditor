#ifndef _LIB_LZCOMP_H_
#define _LIB_LZCOMP_H_

#include <span>

namespace lzcomp {

size_t scan_lz_size(std::span<const u8> src);

size_t compress(std::span<u8> dst, std::span<const u8> src);
size_t uncompress(std::span<u8> dst, std::span<const u8> src, size_t src_offset, size_t src_size);

} // namespace lzcomp

#endif
