add_executable(test_runner
    test_runner.cpp
)

set_target_properties(test_runner PROPERTIES
	COMPILE_FLAGS "-DGAMEBOYCORE_STATIC"
)

target_include_directories(test_runner PRIVATE
    ../../include/
)

target_link_libraries(test_runner
    gameboycore
)

# Add a custom target to run test ROMs
add_custom_target(run_test_roms
    COMMAND test_runner "${CMAKE_CURRENT_SOURCE_DIR}/test_roms/cpu_instrs/cpu_instrs.gb"
    COMMAND test_runner "${CMAKE_CURRENT_SOURCE_DIR}/test_roms/instr_timing/instr_timing.gb"
    COMMAND test_runner "${CMAKE_CURRENT_SOURCE_DIR}/test_roms/mem_timing/mem_timing.gb"
)