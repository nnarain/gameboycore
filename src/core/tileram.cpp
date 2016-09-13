
#include "gameboy/tileram.h"
#include "gameboy/memorymap.h"

#include <iostream>

namespace gb
{
	TileRAM::TileRAM(MMU& mmu) :
		tile_ram_(mmu.getptr(0x8000))
	{
	}
	
	std::vector<Tile> TileRAM::getTiles()
	{
		std::vector<Tile> tiles;

		for (int i = 0; i < NUM_TILES; i++)
		{
			unsigned int offset = i * TILE_SIZE;
			uint8_t* current_tile_ptr = tile_ram_ + offset;

			Tile tile;
			int row = 0;
			
			for (int j = 0; j < TILE_SIZE; j += 2)
			{
				uint8_t lsb = current_tile_ptr[j + 0];
				uint8_t msb = current_tile_ptr[j + 1];

				setRow(tile, msb, lsb, row);
				row++;
			}

			tiles.push_back(tile);
		}

		/*
		int row = 0;
		for (int i = 0; i < 16; i += 2)
		{
		uint8_t lsb = tile_ram_[i + 0];
		uint8_t msb = tile_ram_[i + 1];

		setRow(tile, msb, lsb, row);
		row++;
		}
		*/

		return tiles;
	}

	void TileRAM::setRow(Tile& tile, uint8_t msb, uint8_t lsb, int row)
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

	TileRAM::~TileRAM()
	{
	}
}
