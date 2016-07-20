#
# Gameboy Build
#
# @author Natesh Narain <nnaraindev@gmail.com>
#

cmake_minimum_required(VERSION 2.8)

project(gameboy)

# Core sources for Gameboy emulation
set(GAMEBOYCORE

)

include_directories(
    include/
)

# main emulator executable
add_executable(${PROJECT_NAME}
    src/gameboy/gameboy.cpp
    ${GAMEBOYCORE}
)

# ROM reader utility
add_executable(rominfo
    src/rominfo/rominfo.cpp
)

# Gameboy Core Library
# add_library(gbcore
#     ${GAMEBOYCORE}
# )
