#
# Gameboy Build
#
# @author Natesh Narain <nnaraindev@gmail.com>
#

cmake_minimum_required(VERSION 3.0)

project(gameboycore)

option(BUILD_DOCS "Build documentation" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

add_subdirectory(src)

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
