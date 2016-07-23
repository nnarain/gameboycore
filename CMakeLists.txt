#
# Gameboy Build
#
# @author Natesh Narain <nnaraindev@gmail.com>
#

cmake_minimum_required(VERSION 2.8)

project(gameboy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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
)

include_directories(
    include/
)

# Gameboy Core Library
add_library(gbcore
    ${GAMEBOYCORE}
)

# main emulator executable
add_executable(${PROJECT_NAME}
    src/gameboy/emulator.cpp
	${GAMEBOYCORE_HEADERS}
)
target_link_libraries(${PROJECT_NAME}
    gbcore
)

# ROM reader utility
add_executable(rominfo
    src/rominfo/rominfo.cpp
	${GAMEBOYCORE_HEADERS}
)
target_link_libraries(rominfo
    gbcore
)
