
#include "gameboy/tileram.h"
#include "gameboy/memorymap.h"
#include "gameboy/lcd_controller.h"

#include <stdexcept>

namespace gb
{
	TileRAM::TileRAM(MMU& mmu, const LCDController& lcd) : 
		tile_ram_(mmu.getptr(0x8000)), 
		mmu_(mmu),
		lcd_(lcd)
	{
	}
	
	Tile TileRAM::getTile(uint8_t tilenum) const
	{
		uint16_t tile_addr;
		if (lcd_.getCharacterDataMode() == LCDController::CharacterDataMode::UNSIGNED)
		{
			tile_addr = getTileAddress<uint8_t>(0x8000, tilenum);
		}
		else
		{
			tile_addr = getTileAddress<int8_t>(0x9000, tilenum);
		}

		uint8_t* tile_ptr = mmu_.getptr(tile_addr);

		Tile tile;
		int row = 0;

		for (int i = 0; i < TILE_SIZE; i += 2)
		{
			uint8_t lsb = tile_ptr[i + 0];
			uint8_t msb = tile_ptr[i + 1];

			setRow(tile, msb, lsb, row);
			row++;
		}

		return tile;
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

		return tiles;
	}

	void TileRAM::setRow(Tile& tile, uint8_t msb, uint8_t lsb, int row) const
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
