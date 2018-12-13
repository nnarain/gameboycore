find_package(GTest)

if(UNIX)
    find_package(Threads REQUIRED)
endif(UNIX)

if(GTEST_FOUND)
    message("-- Adding tests")

    # Setup coverage reporting
    if (WITH_COVERAGE)
        include(CodeCoverage)
        setup_target_for_coverage(${PROJECT_NAME}_coverage gameboy_tests coverage)
    endif()

    macro(add_gtest name)
        add_executable(${name} ${ARGN})
        target_compile_definitions(${name} PRIVATE GAMEBOYCORE_STATIC=1)
        target_link_libraries(${name} gameboycore ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

        add_test(${name} ${name})
    endmacro(add_gtest)

    # TODO: Target include and export targets..
    include_directories(
        ../include/
        ../src/
        include/
        ${GTEST_INCLUDE_DIRS}
    )

    # add gtests
    add_gtest(gameboy_tests
        # source
        test_helper.cpp
        test_entry.cpp
        test_api.cpp
        test_mmu.cpp
        test_alu.cpp
        test_gpu.cpp
        test_load_instructions.cpp
        test_arithmetic_instructions.cpp
        test_inc_dec_instructions.cpp
        test_stack_instructions.cpp
        test_jump_instructions.cpp
        test_call_instructions.cpp
        test_shift_rotate_instructions.cpp
        test_bit_instructions.cpp
        test_misc.cpp
        test_invalid_opcodes.cpp
        test_joypad.cpp
        test_low_power_mode.cpp
        
        test_mbc1.cpp
        
        # headers
        include/test_helper.h
        include/util/codegenerator.h
    )

    # make check target to run gtests manually
    add_custom_target(check COMMAND gameboy_tests)

endif(GTEST_FOUND)

add_subdirectory(test_runner)

find_package(benchmark QUIET)

if (benchmark_FOUND)
    add_executable(gameboycore_benchmark
        bench_frame.cpp
    )
    target_link_libraries(gameboycore_benchmark PRIVATE
        benchmark::benchmark benchmark::benchmark_main
        gameboycore
    )

    set_target_properties(gameboycore_benchmark PROPERTIES
        COMPILE_FLAGS "-DGAMEBOYCORE_STATIC"
    )

    add_custom_target(bench
        COMMAND gameboycore_benchmark
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    )
endif(benchmark_FOUND)
