#
# Gameboy Build
#
# @author Natesh Narain <nnaraindev@gmail.com>
#

cmake_minimum_required(VERSION 2.8)

project(gameboy)

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
set(GAMEBOYCORE
    src/core/gameboy.cpp
    src/core/cpu.cpp
    src/core/mmu.cpp
    src/core/cartinfo.cpp
)
set(GAMEBOYCORE_HEADERS
	include/gameboy/gameboy.h
	include/gameboy/cpu.h
	include/gameboy/mmu.h

	include/gameboy/memorymap.h
	include/gameboy/mbc.h
	include/gameboy/cartinfo.h
	
	src/core/bitutil.h
)

# set flags for g++/gcc compiler
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

include_directories(
    include/
)

add_definitions(
    -D${ENDIAN}
)

# Gameboy Core Library
add_library(gbcore
    ${GAMEBOYCORE}
	${GAMEBOYCORE_HEADERS}
)

# main emulator executable
add_executable(${PROJECT_NAME}
    src/gameboy/emulator.cpp
)
target_link_libraries(${PROJECT_NAME}
    gbcore
)

# ROM reader utility
add_executable(rominfo
    src/rominfo/rominfo.cpp
)
target_link_libraries(rominfo
    gbcore
)

enable_testing()
add_subdirectory(tests)
