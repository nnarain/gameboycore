/**
 * GameboyCore Debugger
 * 
 * An emulator UI and debugging tool
 * 
*/

#include <cxxopts.hpp>
#include <string>
#include <iostream>

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
    }
    catch (const cxxopts::OptionException& e)
    {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
