find_package(SFML REQUIRED COMPONENTS system window graphics)

add_executable(${PROJECT_NAME}
    emulator.cpp
	window.h
)
target_link_libraries(${PROJECT_NAME}
    gbcore
	${SFML_LIBRARIES}
)