option(BUILD_TOOLS "Build debug tooling" OFF)

add_subdirectory(gameboycore)

if (BUILD_TOOLS)
    add_subdirectory(tools)
endif(BUILD_TOOLS)
