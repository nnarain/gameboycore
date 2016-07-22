
/**
	\file rominfo.cpp
	\brief Print information about the Gameboy ROM file

	\author Natesh Narain <nnaraindev@gmail.com>
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>

#include "gameboy/cartinfo.h"

static std::string ramSizeToString(uint8_t);
static std::string romSizeToString(uint8_t);
static std::string typeToString(uint8_t);

int main(int argc, char * argv[])
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " <rom file>" << std::endl;
		return 1;
	}

	// open binary rom image and seek to end
	std::ifstream rom_image(argv[1], std::ios::binary | std::ios::ate);

	if (rom_image.is_open())
	{
		// load rom image into memory
		std::vector<uint8_t> buffer;
		size_t length = rom_image.tellg();
		buffer.resize(length);

		rom_image.seekg(0, std::ios::beg);
		rom_image.read((char*)&buffer[0], length);

		// parse the gameboy rom image
		gb::RomParser parser;
		gb::CartInfo info = parser.parse(&buffer[0]);

		std::cout << "-- Game Title: " << info.game_title << std::endl;
		std::cout << "-- Cart Type : " << typeToString(info.type) << std::endl;
		std::cout << "-- RAM Size  : " << ramSizeToString(info.ram_size) << std::endl;
		std::cout << "-- ROM Size  : " << romSizeToString(info.rom_size) << std::endl;
	}
	else
	{
		std::cout << "-- Could not open ROM file: " << argv[1] << std::endl;
	}

    return 0;
}

static std::string ramSizeToString(uint8_t value)
{
	static std::string ram_sizes[] = {
		"None",
		"2 kB",
		"8 kB",
		"32 kB"
	};

	if(value >= 4)
	{
		return std::string("Invalid RAM type");
	}

	return ram_sizes[value];
}

static std::string romSizeToString(uint8_t value)
{
	static std::string rom_sizes1[] = {
		"32 kB (no banking)",
		"64 kB (4 banks)",
		"128 kB (8 banks)",
		"256 kB (16 banks)",
		"512 kB (32 banks)",
		"1 Mb (64 banks)",
		"2 Mb (128 banks)",
		"4 Mb (256 banks)"
	};

	static std::string rom_sizes2[] = {
		"1.1 Mb (72 banks)",
		"1.2 Mb (80 banks)",
		"1.5 Mb (96 banks)"
	};

	if(value <= 0x07)
	{
		return rom_sizes1[value];
	}
	else if(value >= 0x52 && value <= 0x54)
	{
		return rom_sizes2[value - 0x52];
	}
	else
	{
		return std::string("Invalid ROM type");
	}

	return std::string();
}

static std::string typeToString(uint8_t value)
{
	static std::string types[] = {
		"ROM Only",
		"MBC1",
		"MBC1 + RAM",
		"MBC1 + RAM + BAT",
		"Invalid",
		"MBC2",
		"MBC2 + BAT",
		"Invalid",
		"ROM + RAM",
		"ROM + RAM + BAT",
		"Invalid",
		"Invalid",
		"Invalid",
		"Invalid",
		"Invalid",
		"MBC3 + Timer + BAT",
		"MBC3 + RAM + Timer + BAT",
		"MBC3",
		"MBC3 + RAM",
		"MBC3 + RAM + BAT",
		"Invalid",
		"MBC4",
		"MBC4 + RAM",
		"MBC4 + RAM + BAT",
		"Invalid",
		"MBC5",
		"MBC5 + RAM",
		"MBC5 + RAM + BAT"
	};

	return types[value];
}
