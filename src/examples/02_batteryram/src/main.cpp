#include <gameboycore/gameboycore.h>

#include <iostream>
#include <string>
#include <functional>

using namespace gb;

int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        std::cerr << "Must provide path to a ROM file\n";
        return 1;
    }

    std::string filepath{argv[1]};

    // Create an instance of the gameboy emulator core
    GameboyCore core;

    // Open the ROM specified ROM file
    try
    {
        core.open(filepath);
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "Error loading ROM file: " << e.what() << "\n";
        return 1;
    }

    // Get battery RAM from the emulator
    // Battery RAM is persistent storage for the Gameboy (RAM at this location is always on because of a battery in the cartridge)
    // Battery RAM starts at address $A000
    auto batteryram = core.getBatteryRam();
    batteryram[0] = 0xFF;
    core.setBatteryRam(batteryram);

    std::cout << "$A000: " << std::hex << (int)core.readMemory(0xA000) << "\n";

    return 0;
}