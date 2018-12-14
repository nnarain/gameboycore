#ifndef GAMEBOYCORE_DEBUGGER_H
#define GAMEBOYCORE_DEBUGGER_H

#include "user_interface.hpp"

#include <gameboycore/gameboycore.h>

#include <string>
#include <vector>

class GameboyCoreDebugger
{
public:
    /**
     * @param rom_file ROM file to run
    */
    GameboyCoreDebugger(const std::string& rom_file);
    ~GameboyCoreDebugger() = default;

    /**
     * Run the debugger.
    */
    void run();

private:
    void initializeCore(const std::string& filename);

    UserInterface ui_;
    gb::GameboyCore core_;
};

#endif