# Generate version.h using data from git repository
#
# @author Natesh Narain
# @date Oct 15 2016
#

find_package(Git)

function(generate_version_info)

	FILE(WRITE ${CMAKE_BINARY_DIR}/version.h.in
	"\#include <string>\n"
	"\#define VERSION \"@VERSION@\"\n"

	"namespace version{\n"
	"static std::string get(){\n"
	"	std::string version(VERSION);\n"
	"	return version;\n"
	"}\n"
	"}\n"
	)

	FILE(WRITE ${CMAKE_BINARY_DIR}/version.cmake
	"
	EXECUTE_PROCESS(
		 COMMAND ${GIT_EXECUTABLE} rev-list --tags --max-count=1
		 OUTPUT_VARIABLE COMMIT_HASH
		 OUTPUT_STRIP_TRAILING_WHITESPACE
	 )
	EXECUTE_PROCESS(
	     COMMAND ${GIT_EXECUTABLE} describe --tags \${COMMIT_HASH}
	     OUTPUT_VARIABLE VERSION
	     OUTPUT_STRIP_TRAILING_WHITESPACE
	 )
	 CONFIGURE_FILE(\${SRC} \${DST})
	")

	ADD_CUSTOM_TARGET(
	    version
	    ${CMAKE_COMMAND} -D SRC=${CMAKE_BINARY_DIR}/version.h.in
	                     -D DST=${CMAKE_BINARY_DIR}/version.h
	                     -P ${CMAKE_BINARY_DIR}/version.cmake
	)

endfunction(generate_version_info)
