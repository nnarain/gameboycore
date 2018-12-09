option(BUILD_TESTS "Build tests" ON)
option(WITH_COVERAGE "Build with coverage info" OFF)


########################################################################################################################
### GameboyCore                                                                                                      ###
########################################################################################################################
include(TestBigEndian)

test_big_endian(IS_BIG_ENDIAN)

if(IS_BIG_ENDIAN)
    set(ENDIAN "__BIGENDIAN__")
else(IS_BIG_ENDIAN)
    set(ENDIAN "__LITTLEENDIAN__")
endif(IS_BIG_ENDIAN)

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

# Gameboy Core Library
add_library(gameboycore
    ${GAMEBOYCORE}
    ${GAMEBOYCORE_HEADERS}
)
add_library(gameboycore::gameboycore ALIAS gameboycore)

target_compile_features(gameboycore PUBLIC cxx_std_11)

# TODO: Move detail headers elsewhere?
target_include_directories(gameboycore PUBLIC
    include/
)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(gameboycore PRIVATE -Wall -Wextra)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(gameboycore PRIVATE /W3)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(gameboycore PRIVATE -Wall -Wextra)
endif()

target_compile_definitions(gameboycore PRIVATE GAMEBOYCORE_STATIC=1 ${ENDIAN}=1 _CRT_SECURE_NO_WARNINGS=1)

########################################################################################################################
### Tests                                                                                                            ###
########################################################################################################################

if (BUILD_TESTS)
    # Setup coverage reporting
    if (WITH_COVERAGE)
        if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
            target_compile_options(gameboycore PRIVATE -fprofile-arcs -ftest-coverage)
            target_link_libraries(gameboycore gcov)
        else()
            message(WARNING "Code coverage is not supported for ${CMAKE_CXX_COMPILER_ID}")
        endif()
    endif()

    add_subdirectory(tests)
endif(BUILD_TESTS)

########################################################################################################################
### Installation                                                                                                     ###
########################################################################################################################

install(
    TARGETS gameboycore
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
