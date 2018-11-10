/**
 * GameboyCore Debugger
 * 
 * An emulator UI and debugging tool
 * 
*/

#include "gameboycore_debugger.hpp"

#include <cxxopts.hpp>

#include <filesystem>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    cxxopts::Options options("GameboyCore Debugger", "Run and Debug Gameboy ROMs");
    options.add_options()
        ("f,file", "ROM file to run", cxxopts::value<std::string>());

    std::string rom_file{};

    try
    {
        auto args = options.parse(argc, argv);

        rom_file = args["file"].as<std::string>();

        std::filesystem::path filepath{ rom_file };
        if (!std::filesystem::exists(filepath) || std::filesystem::is_directory(filepath))
        {
            throw std::runtime_error("ROM file does not exist");
        }
    }
    catch (const cxxopts::OptionException& e)
    {
        std::cerr << "Unable to parse command line options: " << e.what() << "\n";
        return 1;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "ROM file is invalid: " << e.what() << "\n";
        return 1;
    }

    // Initialize the GameboyCore Debugger
    GameboyCoreDebugger debugger{ rom_file };
    debugger.run();

    return 0;
}
