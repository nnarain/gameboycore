
find_package(Git)

macro(get_version)

	EXECUTE_PROCESS(
		COMMAND ${GIT_EXECUTABLE} rev-list --tags --max-count=1
		OUTPUT_VARIABLE COMMIT_HASH
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	EXECUTE_PROCESS(
		COMMAND ${GIT_EXECUTABLE} describe --tags ${COMMIT_HASH}
		OUTPUT_VARIABLE VERSION
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	
	string(REGEX REPLACE "^([0-9]+)\\.[0-9]+\\.[0-9]+" "\\1" VERSION_MAJOR "${VERSION}")
	string(REGEX REPLACE "^[0-9]+\\.([0-9])+\\.[0-9]+" "\\1" VERSION_MINOR "${VERSION}")
	string(REGEX REPLACE "^[0-9]+\\.[0-9]+\\.([0-9]+)" "\\1" VERSION_PATCH "${VERSION}")
	
endmacro(get_version)
