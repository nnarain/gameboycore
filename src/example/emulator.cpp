
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <functional>
#include <stdexcept>

#include <gameboycore/gameboy.h>

#include "window.h"

#include "version.h"

using namespace gb;

static bool loadGB(const std::string&, std::vector<uint8_t>&);

int main(int argc, char * argv[])
{

    if(argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <romfile>" << std::endl;
        return 1;
    }

	if (std::string(argv[1]) == "-v")
	{
		std::cout << version::get() << std::endl;
	}

    std::vector<uint8_t> rom;
    if(loadGB(std::string(argv[1]), rom))
    {
		try
		{
			Gameboy gameboy;
			gameboy.loadROM(&rom[0], rom.size());

			// after loading ROM into Gameboy, release loaded image
			rom.clear();

			// setup render window
			std::string title = "Dotrix-" + version::get() + " [Beta]";

			Window window(gameboy, title);
			window.start();

			// start emulating
			gameboy.setStepCount(512);
			gameboy.setDebugMode(false);

			while (window.isOpen())
			{
				gameboy.update();
				window.update();
			}
		}
		catch (std::runtime_error& e)
		{
			std::cerr << e.what() << std::endl;
			return 1;
		}
    }
    else
    {
        std::cout << "-- Unable to load rom file: " << argv[1] << std::endl;
    }

    return 0;
}

bool loadGB(const std::string& file_name, std::vector<uint8_t>& buffer)
{
    std::ifstream file(file_name, std::ios::binary | std::ios::ate);
    if(file.is_open())
    {
        size_t length = (size_t)file.tellg();
        buffer.resize(length);

        file.seekg(0, std::ios::beg);
        file.read((char*)&buffer[0], length);

        return true;
    }
    else
    {
        return false;
    }
}
