
find_package(CxxTest REQUIRED)

message("-- adding unit tests")

include_directories(
    ${CXXTEST_INCLUDE_DIRS}
    ../include/
)

# test load instructions
cxxtest_add_test(test_load_instructions test_load_instructions.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/test_load_instructions.h
)
