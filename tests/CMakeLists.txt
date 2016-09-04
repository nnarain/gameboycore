
find_package(GTest)

if(UNIX)
	find_package(Threads REQUIRED)
endif(UNIX)

if(GTEST_FOUND)
	message("-- adding tests")

	macro(add_gtest name)
		add_executable(${name} ${ARGN})
		target_link_libraries(${name} gbcore ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
		add_test(${name} ${name})
	endmacro(add_gtest)

	include_directories(
		../include/
		include/
		${GTEST_INCLUDE_DIRS}
	)

	# add gtests
	add_gtest(gameboy_tests
		test_entry.cpp
		test_mmu.cpp
		test_load_instructions.cpp
		test_inc_dec_instructions.cpp
		test_stack_instructions.cpp
		test_jump_instructions.cpp
	)

	# make check target to run gtests manually
	add_custom_target(check COMMAND gameboy_tests)

endif(GTEST_FOUND)
