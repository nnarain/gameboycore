#include "gameboycore_debugger.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <thread>

GameboyCoreDebugger::GameboyCoreDebugger(const std::string& rom_file)
{
    initializeCore(loadRom(rom_file));
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

void GameboyCoreDebugger::initializeCore(std::vector<char>& rom)
{
    // Load the ROM file into the core
    core_.loadROM((uint8_t*)&rom[0], rom.size());
    // initialize user interface
    ui_.initialize(core_);
}

std::vector<char> GameboyCoreDebugger::loadRom(const std::string& filename)
{
    namespace fs = std::filesystem;

    fs::path filepath{ filename };
    auto filesize = (std::size_t)fs::file_size(filepath);

    std::vector<char> rom;
    rom.resize(filesize);

    std::ifstream file{ filepath, std::ios::binary };
    file.read(&rom[0], rom.size());

    return rom;
}