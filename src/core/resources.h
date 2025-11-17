#ifndef _CORE_RESOURCES_H_
#define _CORE_RESOURCES_H_

#include <cstdint>
#include <vector>

#define DEFINE_INCBIN(name)                 \
	namespace gs::core::res {               \
	extern const std::vector<uint8_t> name; \
	}

#define INCBIN(name, file)                                                  \
	__asm__(".section .rdata, \"dr\"\n"                                     \
			".global incbin_" #name "_start\n"                              \
			".balign 16\n"                                                  \
			"incbin_" #name "_start:\n"                                     \
			".incbin \"" file "\"\n"                                        \
			".global incbin_" #name "_end\n"                                \
			".balign 1\n"                                                   \
			"incbin_" #name "_end:\n"                                       \
			".byte 0\n");                                                   \
	extern __attribute__((aligned(16))) const char incbin_##name##_start[]; \
	extern const char incbin_##name##_end[];                                \
	namespace gs::core::res {                                               \
	const std::vector<uint8_t> name = [] {                                  \
		return std::vector<uint8_t>(                                        \
			reinterpret_cast<const uint8_t *>(incbin_##name##_start),       \
			reinterpret_cast<const uint8_t *>(incbin_##name##_end));        \
	}();                                                                    \
	}

DEFINE_INCBIN(app_ico);
DEFINE_INCBIN(app_version_html);

#endif
