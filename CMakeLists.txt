#
# Gameboy Build
#
# @author Natesh Narain <nnaraindev@gmail.com>
#

cmake_minimum_required(VERSION 3.1)

project(gameboycore)

option(BUILD_TOOLS "Build debug tooling" OFF)
option(BUILD_DOCS "Build documentation" OFF)

set(CMAKE_MODULE_PATH ${CMAKE_PREFIX_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

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

# documentation
if(BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        configure_file(docs/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
        add_custom_target(docs
            ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
            COMMENT "Building documentation"
        )
    endif(DOXYGEN_FOUND)
endif(BUILD_DOCS)
