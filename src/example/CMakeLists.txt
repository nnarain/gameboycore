find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED COMPONENTS system window graphics audio)

get_filename_component(SFML_PATH ${SFML_INCLUDE_DIR} DIRECTORY)

include_directories(
	${CMAKE_CURRENT_LIST_DIR}
	${SFML_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
)

set(EXAMPLE_HEADERS
	audio.h
	imconfig.h
	imgui.h
	imconfig-SFML.h
	imgui-SFML.h
	imgui_internal.h
	stb_rect_pack.h
	stb_textedit.h
	stb_truetype.h
	window.h
	screen_renderer.h
	texture_buffer.h
)

set(EXAMPLE_SOURCES
	emulator.cpp
	imgui.cpp
	imgui_draw.cpp
	imgui-SFML.cpp
)

add_executable(example
	${EXAMPLE_HEADERS}
	${EXAMPLE_SOURCES}
)

set_target_properties(example PROPERTIES
	COMPILE_FLAGS "-DGAMEBOYCORE_STATIC"
)
target_link_libraries(example
    gameboycore-s
	${SFML_LIBRARIES}
	${OPENGL_gl_LIBRARY}
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