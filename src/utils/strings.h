#ifndef _UTILS_STRINGS_H_
#define _UTILS_STRINGS_H_

#include <wx/wx.h>

#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

namespace gs::utils::strings {

/// @brief 문자열 해시 계산
/// @param input 문자열
/// @return 문자열 형식 해시
inline std::string hash(const std::string &input)
{
	constexpr size_t salt = 20251117;

	std::hash<std::string> hasher;
	size_t hash1 = hasher(input) ^ (salt << 1);
	size_t hash2 = hasher(input + std::to_string(salt)) ^ (salt << 1);

	std::stringstream ss;
	ss << std::hex
	   << std::setw(sizeof(size_t) * 2) << std::setfill('0') << hash1
	   << std::setw(sizeof(size_t) * 2) << std::setfill('0') << hash2;

	return ss.str();
}

/// @brief 문자열 변환
/// @param utf8_bytes UTF-8 바이트 배열
/// @return wx용 문자열
inline wxString to_string(const std::vector<uint8_t> &utf8_bytes)
{
	return wxString::FromUTF8(reinterpret_cast<const char *>(utf8_bytes.data()), utf8_bytes.size());
}

} // namespace gs::utils::strings

#endif
