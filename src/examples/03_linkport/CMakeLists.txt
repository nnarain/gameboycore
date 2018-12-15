add_executable(linkport_example
    src/main.cpp
)

target_link_libraries(linkport_example
    gameboycore
)

target_compile_definitions(linkport_example PRIVATE GAMEBOYCORE_STATIC=1)
