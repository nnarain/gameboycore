/**
 * GameboyCore Debugger
 * 
 * An emulator UI and debugging tool
 * 
*/

#include "gameboycore_debugger.hpp"

#include <cxxopts.hpp>

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    cxxopts::Options options("GameboyCore Debugger", "Run and Debug Gameboy ROMs");
    options.add_options()
        ("f,file", "ROM file to run", cxxopts::value<std::string>());

    std::string rom_file{};

    try
    {
        const auto args = options.parse(argc, argv);

        rom_file = args["file"].as<std::string>();
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
    try
    {
        GameboyCoreDebugger debugger{ rom_file };
        debugger.run();
    }
    catch (const std::runtime_error & e)
    {
        std::cerr << e.what() << "\n";
    }

    return 0;
}
