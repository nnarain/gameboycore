find_package(SFML REQUIRED COMPONENTS system window graphics audio)

get_filename_component(SFML_PATH ${SFML_INCLUDE_DIR} DIRECTORY)

include_directories(
	${SFML_INCLUDE_DIR}
)

add_executable(example
    emulator.cpp
	window.h
	screen_renderer.h
	texture_buffer.h
	audio.h
)
target_link_libraries(example
    gbcore
	${SFML_LIBRARIES}
)

add_dependencies(example version)

# install targets
install(
	TARGETS example
	RUNTIME DESTINATION bin
	COMPONENT programs
)

# install sfml libraries
if(WIN32)
	install(
		FILES
			${SFML_PATH}/bin/openal32.dll
			${SFML_PATH}/bin/sfml-audio-d-2.dll
			${SFML_PATH}/bin/sfml-graphics-d-2.dll
			${SFML_PATH}/bin/sfml-network-d-2.dll
			${SFML_PATH}/bin/sfml-system-d-2.dll
			${SFML_PATH}/bin/sfml-window-d-2.dll
		DESTINATION bin
		COMPONENT programs
	)
endif(WIN32)