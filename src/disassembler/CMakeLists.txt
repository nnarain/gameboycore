add_executable(gbdisassembler
	disassembler.cpp
)
target_link_libraries(gbdisassembler
	gbcore
)

set_target_properties(gbdisassembler PROPERTIES
	COMPILE_FLAGS "-D_CRT_SECURE_NO_WARNINGS"
)