
find_package(CxxTest)

if(CXXTEST_FOUND)
	message("-- adding unit tests")

	include_directories(
		${CXXTEST_INCLUDE_DIRS}
		../include/
		include/
	)

	# test load instructions
	cxxtest_add_test(test_load_instructions test_load_instructions.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/test_load_instructions.h
	)
	target_link_libraries(test_load_instructions
		gbcore
	)
endif(CXXTEST_FOUND)
