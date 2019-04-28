set(ROMINFO_HEADERS
    include/cartridge_header.hpp
    include/rominfo.hpp
)

set(ROMINFO_SOURCES
    src/rominfo.cpp
    src/rom_parser.cpp
)

add_executable(rominfo
    ${ROMINFO_HEADERS}
    ${ROMINFO_SOURCES}
)

target_compile_features(rominfo PRIVATE cxx_std_14)
target_include_directories(rominfo PRIVATE
    include/
)
