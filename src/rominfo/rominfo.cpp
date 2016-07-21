
#include <iostream>
#include <fstream>
#include <vector>

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
		rom_image.read(&buffer[0], length);

		//
	}
	else
	{
		std::cout << "-- Could not open ROM file: " << argv[1] << std::endl;
	}

    return 0;
}
