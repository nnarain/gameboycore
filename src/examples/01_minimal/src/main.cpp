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

    // Set callbacks for video and audio
    core.setScanlineCallback([](const GPU::Scanline& scanline, int line){
        std::cout << "Line " << line << "\n";
    });
    core.setAudioSampleCallback([](int16_t l, int16_t r){
        std::cout << "L: " << l << " " << "R: " << r << "\n";
    });

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

    // Run the emulator
    core.emulateFrame();

    return 0;
}