#ifndef _LIB_LZCOMP_H_
#define _LIB_LZCOMP_H_

#include <vector>

namespace lzcomp {

size_t scan_lz_size(const std::vector<u8> &src);

std::vector<u8> compress(const std::vector<u8> &src);
std::vector<u8> uncompress(const std::vector<u8> &src);

} // namespace lzcomp

#endif
