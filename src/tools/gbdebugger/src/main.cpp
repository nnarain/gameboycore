/**
 * GameboyCore Debugger
 * 
 * An emulator UI and debugging tool
 * 
*/

#include "ui/user_interface.hpp"
#include "debugger/gameboycore_debugger.hpp"

#include <gameboycore/gameboycore.h>

#include <cxxopts.hpp>

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    using namespace gb;

    // Setup command line options
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
        return EXIT_FAILURE;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "ROM file is invalid: " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    try
    {
        // Setup the program with a GameboyCore instance, a debugger interface and the UI to display it
        GameboyCore core;
        core.open(rom_file);

        GameboyCoreDebugger debugger{ core };
        UserInterface ui{ core, debugger };

        ui.run();
    }
    catch (const std::runtime_error & e)
    {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
