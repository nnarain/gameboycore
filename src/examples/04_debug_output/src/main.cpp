#include <gameboycore/gameboycore.h>

#include <iostream>
#include <functional>

using namespace gb;

void instructionCallback(const Instruction& instruction, const uint16_t addr)
{
    std::cout << addr << ": " << disassemble(instruction) << "\n";
}

int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Must provide path to a ROM file\n";
        return 1;
    }

    std::string filepath{ argv[1] };

    GameboyCore core;

    // Open the ROM specified ROM file
    try
    {
        core.open(filepath);

        core.setDebugMode(true);
        core.setInstructionCallback(instructionCallback);
    }
    catch (const std::runtime_error & e)
    {
        std::cerr << "Error loading ROM file: " << e.what() << "\n";
        return 1;
    }

    core.emulateFrame();

    return 0;
}