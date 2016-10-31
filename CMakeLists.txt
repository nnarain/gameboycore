#
# Gameboy Build
#
# @author Natesh Narain <nnaraindev@gmail.com>
#

cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
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
	src/core/gpu.cpp
    src/core/cartinfo.cpp
	src/core/shiftrotate.cpp
	src/core/opcodeinfo.cpp
	src/core/tileram.cpp
	src/core/tilemap.cpp
	src/core/joypad.cpp
	src/core/oam.cpp
	src/core/timer.cpp
)
set(GAMEBOYCORE_HEADERS
	include/gameboy/gameboy.h
	include/gameboy/cpu.h
	include/gameboy/alu.h
	include/gameboy/mmu.h
	include/gameboy/gpu.h
	include/gameboy/tileram.h
	include/gameboy/tilemap.h
	include/gameboy/oam.h
	include/gameboy/tile.h
	include/gameboy/joypad.h
	include/gameboy/timer.h
	include/gameboy/interrupt_provider.h
	include/gameboy/pixel.h
	include/gameboy/sprite.h
	include/gameboy/palette.h

	include/gameboy/memorymap.h
	include/gameboy/mbc.h
	include/gameboy/mbc1.h
	include/gameboy/cartinfo.h
	include/gameboy/opcodeinfo.h
	include/gameboy/opcode_cycles.h

	src/core/bitutil.h
	src/core/shiftrotate.h
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
add_library(gbcore
    ${GAMEBOYCORE}
	${GAMEBOYCORE_HEADERS}
)

add_subdirectory(src/gameboy)

enable_testing()
add_subdirectory(tests)

# install core
install(
	TARGETS gbcore
	ARCHIVE DESTINATION lib
	COMPONENT development
)

# install headers
install(
	DIRECTORY include
	DESTINATION .
	COMPONENT development
)

# Installation
include(get-version-config)
get_version()

set(CPACK_PACKAGE_NAME "dotrix")
set(CPACK_PACKAGE_VENDOR "nnarain")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Gameboy emulator and library")
set(CPACK_PACKAGE_VERSION "${VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "dotrix")

set(CPACK_COMPONENT_DEVELOPMENT_DISPLAY_NAME "Development")
set(CPACK_COMPONENT_PROGRAMS_DISPLAY_NAME "Programs")

include(CPack)

