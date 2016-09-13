
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/


#ifndef GAMEBOY_DISPLAY_H
#define GAMEBOY_DISPLAY_H

#include "gameboy/mmu.h"

#include <cstdint>
#include <vector>

namespace gb
{
	struct Tile
	{
		uint8_t color[64];
	};

	class TileRAM
	{
	public:
		static const unsigned int NUM_TILES = 192;
		static const unsigned int TILE_SIZE = 16;

	public:
		TileRAM(MMU& mmu);
		~TileRAM();

		std::vector<Tile> getTiles();

	private:
		void setRow(Tile& tile, uint8_t msb, uint8_t lsb, int row);

	private:
		uint8_t* tile_ram_;
	};

}

#endif // GAMEBOY_DISPLAY_H
