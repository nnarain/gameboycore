
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/


#ifndef GAMEBOY_DISPLAY_H
#define GAMEBOY_DISPLAY_H

#include "gameboy/mmu.h"

#include <cstdint>

namespace gb
{
	struct Tile
	{
		uint8_t color[64];
	};

	class Display
	{
	public:
		Display(MMU& mmu);
		~Display();

		void printTileRAM();

	private:
		void setRow(Tile& tile, uint8_t msb, uint8_t lsb, int row);

	private:
		uint8_t* vram_;
	};

}

#endif // GAMEBOY_DISPLAY_H
