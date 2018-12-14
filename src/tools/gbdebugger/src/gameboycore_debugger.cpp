#include "gameboycore_debugger.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <thread>

GameboyCoreDebugger::GameboyCoreDebugger(const std::string& rom_file)
{
    initializeCore(rom_file);
}

void GameboyCoreDebugger::run()
{
    using namespace std::chrono_literals;

    while (ui_.isRunning())
    {
        // Emulate a frames worth of data
        core_.emulateFrame();
        // Update emulator output
        ui_.update();

        // Loop at 60Hz
        std::this_thread::sleep_for(16ms);
    }
}

void GameboyCoreDebugger::initializeCore(const std::string& filename)
{
    // Load the ROM file into the core
    core_.open(filename);
    // initialize user interface
    ui_.initialize(core_);
}
