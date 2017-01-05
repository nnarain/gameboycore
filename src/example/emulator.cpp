
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>
#include <stdexcept>

#include <gameboycore/gameboycore.h>
#include <gameboycore/link_cable.h>

#include "window.h"

#include "version.h"

using namespace gb;


static bool loadGB(GameboyCore& gameboy, const std::string& filename);
static std::vector<uint8_t> loadFile(const std::string& file);
static void saveRam(const std::string& file_name, const std::vector<uint8_t>& battery_ram);
static std::string saveFileName(const std::string& rom_filename);

int main(int argc, char * argv[])
{

	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " <romfile>" << std::endl;
		return 1;
	}

	if (std::string(argv[1]) == "-v")
	{
		std::cout << version::get() << std::endl;
	}

	std::string filename(argv[1]);

	GameboyCore gameboy1;

	if (loadGB(gameboy1, filename))
	{
		try
		{
			// setup render window
			std::string title = "Example " + version::get();

			Window window1(gameboy1, title);
			window1.start();

			gameboy1.setDebugMode(false);

			while (window1.isOpen())
			{
				gameboy1.update(512);
				window1.update();
			}
		}
		catch (std::runtime_error& e)
		{
			std::cerr << e.what() << std::endl;
			return 1;
		}

		// Exiting save battery RAM

		// get battery ram from memory
		std::vector<uint8_t> battery_ram = gameboy1.getMMU()->getBatteryRam();

		saveRam(saveFileName(filename), battery_ram);
	}
	else
	{
		std::cout << "-- Unable to load rom file: " << argv[1] << std::endl;
	}

	return 0;
}

bool loadGB(GameboyCore& gameboy, const std::string& filename)
{
	std::vector<uint8_t> rom = loadFile(filename);
	std::vector<uint8_t> ram = loadFile(saveFileName(filename));

	if (rom.size() > 0)
	{
		gameboy.loadROM(&rom[0], rom.size());

		if (ram.size() > 0)
		{
			gameboy.getMMU()->setBatteryRam(ram);
		}

		return true;
	}

	return false;
}

std::vector<uint8_t> loadFile(const std::string& file_name)
{
	std::vector<uint8_t> data;

	std::ifstream file(file_name, std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		auto length = file.tellg();
		data.resize((unsigned int)length);

		file.seekg(0, std::ios::beg);
		file.read((char*)&data[0], length);
	}

	return data;
}

void saveRam(const std::string& file_name, const std::vector<uint8_t>& battery_ram)
{
	std::ofstream file(file_name, std::ios::binary);
	file.write((char*)&battery_ram[0], battery_ram.size());
}

std::string saveFileName(const std::string& rom_filename)
{
	return rom_filename.substr(0, rom_filename.rfind('.')) + ".sav";
}