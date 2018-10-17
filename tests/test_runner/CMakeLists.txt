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
    gameboycore-s
)