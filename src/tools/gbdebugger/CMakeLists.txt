find_package(OpenGL REQUIRED)
find_package(SFML REQUIRED COMPONENTS system window graphics audio)
find_package(cxxopts REQUIRED)
find_package(Threads REQUIRED)
find_package(fmt CONFIG REQUIRED)

set(UI_HEADERS
    include/ui/audio_stream.hpp
    include/ui/frame_buffer.hpp
    include/ui/user_interface.hpp
    include/ui/views/view.hpp
    include/ui/views/default_view.hpp
    include/ui/views/memory_view.hpp
)

set(UI_SOURCES
    src/ui/audio_stream.cpp
    src/ui/user_interface.cpp
    src/ui/views/default_view.cpp
    src/ui/views/memory_view.cpp
)

set(DEBUGGER_HEADERS
    include/debugger/debugger_interface.hpp
    include/debugger/gameboycore_debugger.hpp
    include/debugger/disassembly_generator.hpp
    include/debugger/annotations.hpp
)

set(DEBUGGER_SOURCES
    src/debugger/gameboycore_debugger.cpp
    src/debugger/disassembly_generator.cpp
    src/debugger/annotations.cpp
)

set(GBDEBUGGER_HEADERS
    ${UI_HEADERS}
    ${DEBUGGER_HEADERS}
)

set(GBDEBUGGER_SOURCES
    src/main.cpp
    
    ${UI_SOURCES}
    ${DEBUGGER_SOURCES}
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
    fmt::fmt

    ${CMAKE_THREAD_LIBS_INIT}
)

target_compile_features(gbdebugger PUBLIC cxx_std_14)
target_compile_definitions(gbdebugger PRIVATE GAMEBOYCORE_STATIC=1)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(gbdebugger PRIVATE -Wall -Werror)
elseif(MSVC)
    target_compile_options(gbdebugger PRIVATE /W3)
endif()
