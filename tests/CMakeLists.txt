
find_package(GTest)

if(GTEST_FOUND)
	message("-- adding tests")

	macro(add_gtest name test_file)
		add_executable(${name} ${test_file})
		target_link_libraries(${name} gbcore ${GTEST_BOTH_LIBRARIES})
		add_test(${name} ${name})
	endmacro(add_gtest)
	
	include_directories(
		../include/
		include/
		${GTEST_INCLUDE_DIRS}
	)
	
	# load instructions test
	add_gtest(loadinstructions_test test_load_instructions.cpp)
	
	
	
endif(GTEST_FOUND)
