option(BUILD_TESTS "Build tests" ON)


# test endianness of system
include(TestBigEndian)

test_big_endian(IS_BIG_ENDIAN)

if(IS_BIG_ENDIAN)
    message("-- Setting __BIGENDIAN__")
    set(ENDIAN "__BIGENDIAN__")
else(IS_BIG_ENDIAN)
    message("-- Setting __LITTLEENDIAN__")
    set(ENDIAN "__LITTLEENDIAN__")
endif(IS_BIG_ENDIAN)

# Core sources for Gameboy emulation
set(GAMEBOYCORE_API_HEADERS
    include/gameboycore/gameboycore_api.h
    include/gameboycore/gameboycore.h
    include/gameboycore/cpu.h
    include/gameboycore/mmu.h
    include/gameboycore/gpu.h
    include/gameboycore/apu.h
    include/gameboycore/joypad.h
    include/gameboycore/link.h
    include/gameboycore/link_cable.h
    include/gameboycore/pixel.h
    include/gameboycore/sprite.h
    include/gameboycore/memorymap.h
)

set(GAMEBOYCORE_HEADERS
    ${GAMEBOYCORE_API_HEADERS}
    include/gameboycore/alu.h
    include/gameboycore/tileram.h
    include/gameboycore/tilemap.h
    include/gameboycore/oam.h
    include/gameboycore/tile.h
    include/gameboycore/timer.h
    include/gameboycore/interrupt_provider.h
    include/gameboycore/palette.h
    include/gameboycore/detail/audio/square_wave_channel.h
    include/gameboycore/detail/audio/wave_channel.h
    include/gameboycore/detail/audio/noise_channel.h
    include/gameboycore/channel.h
    include/gameboycore/memorymap.h
    include/gameboycore/mbc.h
    include/gameboycore/mbc1.h
    include/gameboycore/mbc2.h
    include/gameboycore/mbc3.h
    include/gameboycore/mbc5.h
    include/gameboycore/rtc.h
    include/gameboycore/cartinfo.h
    include/gameboycore/opcodeinfo.h
    include/gameboycore/opcode_cycles.h
    src/core/bitutil.h
    src/core/shiftrotate.h
)

set(GAMEBOYCORE
    src/core/gameboycore.cpp
    src/core/cpu.cpp
    src/core/mmu.cpp
    src/core/gpu.cpp
    src/core/apu.cpp
    src/core/joypad.cpp
    src/core/link.cpp
    src/core/link_cable.cpp
    src/core/mbc.cpp
    src/core/mbc1.cpp
    src/core/mbc2.cpp
    src/core/mbc3.cpp
    src/core/mbc5.cpp
    src/core/alu.cpp
    src/core/cartinfo.cpp
    src/core/shiftrotate.cpp
    src/core/opcodeinfo.cpp
    src/core/tileram.cpp
    src/core/tilemap.cpp
    src/core/oam.cpp
    src/core/timer.cpp
)

# compiler specific flags
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -Wno-format-security")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 -D_CRT_SECURE_NO_WARNINGS")
endif()

include(version-config)
generate_version_info()

include_directories(
    include/
    ${CMAKE_BINARY_DIR}
)

add_definitions(
    -D${ENDIAN}
)

# Gameboy Core Library
add_library(${PROJECT_NAME} SHARED
    ${GAMEBOYCORE}
    ${GAMEBOYCORE_HEADERS}
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_FLAGS "-DGAMEBOYCORE_EXPORT"
)

add_library(${PROJECT_NAME}-s STATIC
    ${GAMEBOYCORE}
    ${GAMEBOYCORE_HEADERS}
)
set_target_properties(${PROJECT_NAME}-s PROPERTIES
    COMPILE_FLAGS "-DGAMEBOYCORE_STATIC"
)

install(
    TARGETS ${PROJECT_NAME} ${PROJECT_NAME}-s
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    COMPONENT development
)

# install headers
install(
    FILES ${GAMEBOYCORE_API_HEADERS}
    DESTINATION include/gameboycore
    COMPONENT development
)
