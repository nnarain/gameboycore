
#include "gameboy/display.h"
#include "gameboy/memorymap.h"

#include <iostream>

namespace gb
{
	Display::Display(MMU& mmu) :
		vram_(mmu.getptr(0x8000))
	{
	}
	
	void Display::printTileRAM()
	{
		Tile tile;

		int row = 0;
		for (int i = 0; i < 16; i += 2)
		{
			uint8_t lsb = vram_[i + 0];
			uint8_t msb = vram_[i + 1];

			setRow(tile, msb, lsb, row);
			row++;
		}

		int pixel = 0;
		for (int i = 0; i < 8; ++i)
		{
			std::printf("\t");
			for (int j = 0; j < 8; ++j)
			{
				if (tile.color[pixel] == 3)
				{
					std::printf("x");
				}
				else if (tile.color[pixel] == 0)
				{
					std::printf(" ");
				}
				pixel++;
			}
			std::printf("\n");
		}
		std::printf("\n");
	}

	void Display::setRow(Tile& tile, uint8_t msb, uint8_t lsb, int row)
	{
		int offset = row * 8;

		int pixel = 0;
		for (int i = 7; i >= 0; i--)
		{
			uint8_t mask = (1 << i);
			uint8_t color = (((msb & mask) >> i) << 1) | ((lsb & mask) >> i);

			tile.color[offset + pixel] = color;
			pixel++;
		}
	}

	Display::~Display()
	{
	}
}
