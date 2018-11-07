option(WITH_DEBUGGER "Debugging Tool" ON)

if (WITH_DEBUGGER)
    add_subdirectory(gbdebugger)
endif()
