#
# Gameboy Build
#
# @author Natesh Narain <nnaraindev@gmail.com>
#

cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

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
	src/core/alu.cpp
    src/core/mmu.cpp
    src/core/cartinfo.cpp
	src/core/shiftrotate.cpp
	src/core/opcodeinfo.cpp
	src/core/lcd_controller.cpp
	src/core/tileram.cpp
	src/core/tilemap.cpp
	src/core/joypad.cpp
)
set(GAMEBOYCORE_HEADERS
	include/gameboy/gameboy.h
	include/gameboy/cpu.h
	include/gameboy/alu.h
	include/gameboy/mmu.h
	include/gameboy/lcd_controller.h
	include/gameboy/tileram.h
	include/gameboy/tilemap.h
	include/gameboy/tile.h
	include/gameboy/joypad.h
	include/gameboy/interrupt_provider.h

	include/gameboy/memorymap.h
	include/gameboy/mbc.h
	include/gameboy/cartinfo.h
	include/gameboy/opcodeinfo.h

	src/core/bitutil.h
	src/core/shiftrotate.h
)

# compiler specific flags
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -Wno-format-security")
elseif(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
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

add_subdirectory(src/gameboy)
add_subdirectory(src/disassembler)
add_subdirectory(src/rominfo)

enable_testing()
add_subdirectory(tests)
