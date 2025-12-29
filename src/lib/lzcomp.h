#ifndef _LIB_LZCOMP_H_
#define _LIB_LZCOMP_H_

#include <vector>

namespace lzcomp {

size_t scan_lz_size(const std::vector<u8> &src);

size_t compress(std::vector<u8> &dst, const std::vector<u8> &src);
size_t uncompress(std::vector<u8> &dst, const std::vector<u8> &src, size_t src_offset, size_t src_size);

} // namespace lzcomp

#endif
