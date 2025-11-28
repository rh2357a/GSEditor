#ifndef _EMBED_TYPES_H_
#define _EMBED_TYPES_H_

#include <wx/mstream.h>
#include <wx/wx.h>

#include <cstdint>
#include <vector>
#include <span>

#define EMBED_BINARY(name, filename)        \
    namespace embed {                       \
    extern const std::vector<uint8_t> name; \
    }

#define EMBED_WX_BITMAP(name, type, filename)                     \
    namespace embed {                                             \
    extern const std::vector<uint8_t> name;                       \
    inline wxBitmap &name##_to_wx_bitmap()                        \
    {                                                             \
        static wxMemoryInputStream mis(name.data(), name.size()); \
        static wxImage image(mis, type);                          \
        static wxBitmap bmp(image);                               \
        return bmp;                                               \
    }                                                             \
    }

#define INCBIN(name, filename)                                              \
    __asm__(".section .rdata, \"dr\"\n"                                     \
            ".global incbin_" #name "_start\n"                              \
            ".balign 16\n"                                                  \
            "incbin_" #name "_start:\n"                                     \
            ".incbin \"" filename "\"\n"                                    \
            ".global incbin_" #name "_end\n"                                \
            ".balign 1\n"                                                   \
            "incbin_" #name "_end:\n"                                       \
            ".byte 0\n");                                                   \
    extern __attribute__((aligned(16))) const char incbin_##name##_start[]; \
    extern const char incbin_##name##_end[];                                \
    namespace embed {                                                       \
    const std::vector<uint8_t> name = [] {                                  \
        return std::vector<uint8_t>(                                        \
            reinterpret_cast<const uint8_t *>(incbin_##name##_start),       \
            reinterpret_cast<const uint8_t *>(incbin_##name##_end));        \
    }();                                                                    \
    }

#endif
