#
# Gameboy Build
#
# @author Natesh Narain <nnaraindev@gmail.com>
#

cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(gameboycore)

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
	
)

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
	${GAMEBOYCORE_API_HEADERS}
	include/gameboycore/gameboy.h
	include/gameboycore/cpu.h
	include/gameboycore/alu.h
	include/gameboycore/mmu.h
	include/gameboycore/gpu.h
	include/gameboycore/apu.h
	include/gameboycore/tileram.h
	include/gameboycore/tilemap.h
	include/gameboycore/oam.h
	include/gameboycore/tile.h
	include/gameboycore/joypad.h
	include/gameboycore/timer.h
	include/gameboycore/interrupt_provider.h
	include/gameboycore/pixel.h
	include/gameboycore/sprite.h
	include/gameboycore/palette.h
	include/gameboycore/sound.h
	include/gameboycore/noise.h
	include/gameboycore/wave.h
	include/gameboycore/channel.h

	include/gameboycore/memorymap.h
	include/gameboycore/mbc.h
	include/gameboycore/mbc1.h
	include/gameboycore/cartinfo.h
	include/gameboycore/opcodeinfo.h
	include/gameboycore/opcode_cycles.h

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
add_library(gbcore SHARED
    ${GAMEBOYCORE}
	${GAMEBOYCORE_HEADERS}
)

if(NOT NO_GUI)
	add_subdirectory(src/example)
endif(NOT NO_GUI)

enable_testing()
add_subdirectory(tests)

# install core
install(
	TARGETS gbcore
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

# Installation
include(get-version-config)
get_version()

set(CPACK_PACKAGE_NAME "gameboycore")
set(CPACK_PACKAGE_VENDOR "nnarain")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Gameboy emulator and library")
set(CPACK_PACKAGE_VERSION "${VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "gameboycore")

set(CPACK_COMPONENT_DEVELOPMENT_DISPLAY_NAME "Development")
set(CPACK_COMPONENT_PROGRAMS_DISPLAY_NAME "Programs")

include(CPack)

