option(WITH_DEBUGGER "Debugging tool" ON)
option(WITH_ROMINFO  "ROM info tool" ON)

if (WITH_DEBUGGER)
    add_subdirectory(gbdebugger)
endif()

if (WITH_ROMINFO)
    add_subdirectory(rominfo)
endif()
