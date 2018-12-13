add_executable(test_runner
    test_runner.cpp
)

target_compile_definitions(test_runner PRIVATE -DGAMEBOYCORE_STATIC=1)
target_link_libraries(test_runner gameboycore)

add_executable(test_runner2
    test_runner2.cpp
)

target_compile_definitions(test_runner2 PRIVATE -DGAMEBOYCORE_STATIC=1)
target_link_libraries(test_runner2 gameboycore)

# Add a custom target to run test ROMs
add_custom_target(run_test_roms
    COMMAND test_runner "${CMAKE_CURRENT_SOURCE_DIR}/test_roms/cpu_instrs/cpu_instrs.gb"
    COMMAND test_runner "${CMAKE_CURRENT_SOURCE_DIR}/test_roms/instr_timing/instr_timing.gb"
    COMMAND test_runner "${CMAKE_CURRENT_SOURCE_DIR}/test_roms/mem_timing/mem_timing.gb"
    COMMAND test_runner2 "${CMAKE_CURRENT_SOURCE_DIR}/test_roms/dmg_sound/dmg_sound.gb"
    COMMAND test_runner2 "${CMAKE_CURRENT_SOURCE_DIR}/test_roms/cgb_sound/cgb_sound.gb"
    COMMAND test_runner2 "${CMAKE_CURRENT_SOURCE_DIR}/test_roms/mem_timing-2/mem_timing.gb"
    COMMAND test_runner2 "${CMAKE_CURRENT_SOURCE_DIR}/test_roms/oam_bug/oam_bug.gb"
)