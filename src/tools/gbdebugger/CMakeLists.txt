find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED COMPONENTS system window graphics audio)

set(GBDEBUGGER_HEADERS

)

set(GBDEBUGGER_SOURCES
    src/main.cpp
)

add_subdirectory(src/external)

add_executable(gbdebugger
    ${GBDEBUGGER_HEADERS}
    ${GBDEBUGGER_SOURCES}
)

target_include_directories(gbdebugger PRIVATE
    include/
    ${SFML_INCLUDE_DIR}
)

target_link_libraries(gbdebugger
    imgui
    ${SFML_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
)

target_compile_features(gbdebugger PUBLIC cxx_std_17)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(gbdebugger PRIVATE -Wall -Werror)
elseif(MSVC)
    target_compile_options(gbdebugger PRIVATE /W3 /WX)
endif()
