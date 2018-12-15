add_executable(minimal_example
    src/main.cpp
)

target_link_libraries(minimal_example
    gameboycore
)

target_compile_definitions(minimal_example PRIVATE GAMEBOYCORE_STATIC=1)
