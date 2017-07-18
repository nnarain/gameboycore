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
	include/gameboycore/noise.h
	include/gameboycore/channel.h
	include/gameboycore/memorymap.h
	include/gameboycore/mbc.h
	include/gameboycore/mbc1.h
	include/gameboycore/mbc2.h
	include/gameboycore/mbc3.h
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

# example
if(NOT DEFINED BUILD_EXAMPLE)
	set(BUILD_EXAMPLE "ON")
endif(NOT DEFINED BUILD_EXAMPLE)

if(BUILD_EXAMPLE STREQUAL "ON")
	add_subdirectory(src/example)
endif(BUILD_EXAMPLE STREQUAL "ON")

# Tests
if(NOT DEFINED BUILD_TESTS)
	set(BUILD_TESTS "ON")
endif(NOT DEFINED BUILD_TESTS)

if(BUILD_TESTS STREQUAL "ON")
	enable_testing()
	add_subdirectory(tests)
endif(BUILD_TESTS STREQUAL "ON")

# install core
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

# Installation
include(get-version-config)
get_version()

# if on windows package as zip, otherwise use defaults
if(WIN32)
    set(CPACK_GENERATOR "ZIP")
endif(WIN32)

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

# documentation
if(NOT DEFINED BUILD_DOCS)
	set(BUILD_DOCS "OFF")
endif(NOT DEFINED BUILD_DOCS)

if(BUILD_DOCS STREQUAL "ON")
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        configure_file(docs/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
        add_custom_target(docs
            ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
            COMMENT "Building documentation"
        )
    endif(DOXYGEN_FOUND)
endif(BUILD_DOCS STREQUAL "ON")
