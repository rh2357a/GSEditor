set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# cmrc
# https://github.com/vector-of-bool/cmrc
# 952ffddba731fc110bd50409e8d2b8a06abbd237
# MIT license
block()
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmrc")
    include(CMakeRC)
endblock()

# wxWidgets
# https://github.com/wxWidgets/wxWidgets
# v3.3.3 (670835aec7e54b9e9d5a50d6a1aea1e8ba0bcdb2)
# LGPL-2.0-or-later WITH WxWindows-exception-3.1
block()
    set(wxBUILD_SHARED OFF CACHE BOOL "" FORCE)
    set(wxUSE_UNICODE ON CACHE BOOL "" FORCE)
    set(wxUSE_HTML ON CACHE BOOL "" FORCE)
    set(wxUSE_STC OFF CACHE BOOL "" FORCE)
    set(wxUSE_XRC OFF CACHE BOOL "" FORCE)
    set(wxUSE_WEBVIEW OFF CACHE BOOL "" FORCE)
    set(wxUSE_MEDIACTRL OFF CACHE BOOL "" FORCE)
    set(wxUSE_AUI OFF CACHE BOOL "" FORCE)
    set(wxUSE_RIBBON OFF CACHE BOOL "" FORCE)
    add_subdirectory(wxWidgets)
endblock()

# xxHash
# https://github.com/Cyan4973/xxHash
# v0.8.3 (e626a72bc2321cd320e953a0ccf1584cad60f363)
# BSD 2-Clause License
block()
    add_subdirectory(xxHash/cmake_unofficial)
endblock()

# lodepng
# https://github.com/lvandeve/lodepng
# 22561883dd63fd1850f18e1f6adac321e4f609b0
# Zlib license
block()
    add_library(lodepng STATIC "${CMAKE_CURRENT_SOURCE_DIR}/lodepng/lodepng.cpp")
    target_include_directories(lodepng PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lodepng")
endblock()

# lzcomp
# https://github.com/aaaaaa123456789/lzcomp
# 4983f5b1c052bb34b0cc096556bdcb2432cdafef
# Unlicense
block()
    file(GLOB_RECURSE LZCOMP_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/lzcomp/*.c")
    add_library(lzcomp STATIC ${LZCOMP_SOURCES})
    target_include_directories(lzcomp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lzcomp")
endblock()

# xdelta
# https://github.com/marco-calautti/xdelta
# ab959ecd9a471a0dec5babc3de9d1e27ca25ffa8
# Apache License 2.0
block()
    set(XD3_BUILD_AS_EXE OFF CACHE BOOL "" FORCE)
    add_subdirectory(xdelta)
endblock()

# utfcpp
# https://github.com/nemtrif/utfcpp
# 819011bb01628fe1aa2f1da9f2c842a48fd5680b
# BSL-1.0 license
block()
    add_subdirectory(utfcpp)
endblock()
