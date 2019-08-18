add_executable(debug_output
    src/main.cpp
)

target_link_libraries(debug_output
    gameboycore
)

target_compile_definitions(debug_output PRIVATE GAMEBOYCORE_STATIC=1)
