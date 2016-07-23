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

include_directories(
    include/
)

# main emulator executable
add_executable(${PROJECT_NAME}
    src/gameboy/main.cpp
    ${GAMEBOYCORE}
)

# ROM reader utility
add_executable(rominfo
    src/rominfo/rominfo.cpp
    ${GAMEBOYCORE}
)

# Gameboy Core Library
add_library(gbcore
    ${GAMEBOYCORE}
)
