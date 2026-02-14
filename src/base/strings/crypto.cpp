#include "crypto.h"

#include <xxhash.h>

#include <iomanip>
#include <sstream>

std::string base::Hash(std::span<const u8> input)
{
    size_t length = input.size();
    XXH128_hash_t hash = XXH3_128bits(input.data(), length);

    std::ostringstream oss;
    oss << std::hex << std::setfill('0')
        << std::setw(16) << hash.high64
        << std::setw(16) << hash.low64;

    return oss.str();
}

std::string base::Hash(std::string_view input)
{
    size_t length = input.size();
    XXH128_hash_t hash = XXH3_128bits(input.data(), length);

    std::ostringstream oss;
    oss << std::hex << std::setfill('0')
        << std::setw(16) << hash.high64
        << std::setw(16) << hash.low64;

    return oss.str();
}
