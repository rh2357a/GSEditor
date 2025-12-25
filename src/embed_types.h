#ifndef _EMBED_TYPES_H_
#define _EMBED_TYPES_H_

#include <wx/mstream.h>
#include <wx/wx.h>

#include <vector>
#include <span>

#define EMBED_BINARY(name, filename)   \
    namespace embed {                  \
    extern const std::vector<u8> name; \
    }

#define EMBED_WX_BITMAP(name, type, filename)                     \
    namespace embed {                                             \
    extern const std::vector<u8> name;                            \
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
    const std::vector<u8> name = [] {                                       \
        return std::vector<u8>(                                             \
            reinterpret_cast<const u8 *>(incbin_##name##_start),            \
            reinterpret_cast<const u8 *>(incbin_##name##_end));             \
    }();                                                                    \
    }

#endif
