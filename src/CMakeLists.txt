option(BUILD_TOOLS "Build debug tooling" OFF)
option(BUILD_EXAMPLES "Build example programs" OFF)

add_subdirectory(gameboycore)

if (BUILD_TOOLS)
    add_subdirectory(tools)
endif(BUILD_TOOLS)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif(BUILD_EXAMPLES)
