add_executable(batteryram_example
    src/main.cpp
)

target_link_libraries(batteryram_example
    gameboycore
)

target_compile_definitions(batteryram_example PRIVATE GAMEBOYCORE_STATIC=1)
