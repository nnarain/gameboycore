
#include <iostream>
#include <fstream>

#include "romparser.h"

int main(int argc, char * argv[])
{
	if (argc < 2) 
	{
		std::cout << "Usage: " << argv[0] << " <rom file>" << std::endl;
		return 1;
	}

	// load rom image
	std::ifstream rom_image(argv[1]);

	if (rom_image.is_open())
	{
		RomParser parser;
		parser.parse(rom_image);
	}
	else
	{
		std::cout << "-- Could not open ROM file: " << argv[1] << std::endl;
	}

    return 0;
}
