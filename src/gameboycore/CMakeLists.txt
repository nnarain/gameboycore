option(BUILD_TESTS "Build tests" ON)
option(WITH_COVERAGE "Build with coverage info" OFF)

########################################################################################################################
### CMake Policy                                                                                                     ###
########################################################################################################################
cmake_policy(SET CMP0054 OLD)


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
    include/gameboycore/time.h
    include/gameboycore/instruction.h
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
    include/gameboycore/detail/rtc/rtc.h
    include/gameboycore/cartinfo.h
    include/gameboycore/opcodeinfo.h
    include/gameboycore/opcode_cycles.h
    src/bitutil.h
    src/shiftrotate.h
)

set(GAMEBOYCORE
    src/gameboycore.cpp
    src/cpu.cpp
    src/mmu.cpp
    src/gpu.cpp
    src/apu.cpp
    src/joypad.cpp
    src/link.cpp
    src/link_cable.cpp
    src/mbc.cpp
    src/mbc1.cpp
    src/mbc2.cpp
    src/mbc3.cpp
    src/mbc5.cpp
    src/alu.cpp
    src/cartinfo.cpp
    src/shiftrotate.cpp
    src/opcodeinfo.cpp
    src/tileram.cpp
    src/tilemap.cpp
    src/oam.cpp
    src/timer.cpp
    src/instruction.cpp
)

# Gameboy Core Library
add_library(gameboycore
    ${GAMEBOYCORE}
    ${GAMEBOYCORE_HEADERS}
)
add_library(gameboycore::gameboycore ALIAS gameboycore)

target_compile_features(gameboycore PUBLIC cxx_std_11)

target_include_directories(gameboycore
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(gameboycore PRIVATE -Wall -Wextra)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(gameboycore PRIVATE /W4)
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
