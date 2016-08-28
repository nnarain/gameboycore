
find_package(CxxTest REQUIRED)

message("-- adding unit tests")

set(ROM_DIR "${CMAKE_SOURCE_DIR}/tests/asm/")

include_directories(
    ${CXXTEST_INCLUDE_DIRS}
    ../include/
)

add_definitions(
	-DROM_DIR="${ROM_DIR}"
)

# test load instructions
cxxtest_add_test(test_load_instructions test_load_instructions.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/test_load_instructions.h
)
