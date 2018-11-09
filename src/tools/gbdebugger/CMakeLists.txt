find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED COMPONENTS system window graphics audio)
find_package(cxxopts REQUIRED)

set(GBDEBUGGER_HEADERS
    include/gameboycore_debugger.hpp
    include/user_interface.hpp
    include/frame_buffer.hpp
)

set(GBDEBUGGER_SOURCES
    src/main.cpp
    src/gameboycore_debugger.cpp
    src/user_interface.cpp
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
    gameboycore

    imgui
    ${SFML_LIBRARIES}
    ${OPENGL_gl_LIBRARY}

    cxxopts::cxxopts
)

target_compile_features(gbdebugger PUBLIC cxx_std_17)
target_compile_definitions(gbdebugger PRIVATE GAMEBOYCORE_STATIC=1)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(gbdebugger PRIVATE -Wall -Werror)
elseif(MSVC)
    target_compile_options(gbdebugger PRIVATE /W3)
endif()
