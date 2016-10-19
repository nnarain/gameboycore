find_package(SFML REQUIRED COMPONENTS system window graphics)

include_directories(
	${SFML_INCLUDE_DIR}
)

add_executable(dotrix
    emulator.cpp
	window.h
	screen_renderer.h
	texture_buffer.h
)
target_link_libraries(dotrix
    gbcore
	${SFML_LIBRARIES}
)

add_dependencies(dotrix version)

# install targets
install(
	TARGETS dotrix
	RUNTIME DESTINATION bin
	COMPONENT programs
)