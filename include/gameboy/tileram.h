
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/


#ifndef GAMEBOY_DISPLAY_H
#define GAMEBOY_DISPLAY_H

#include "gameboy/mmu.h"
#include "gameboy/tile.h"
#include "gameboy/sprite.h"
#include "gameboy/lcd_controller.h"

#include <cstdint>
#include <vector>

namespace gb
{
	/**
		\brief Class that knows how to read Tile RAM in the Gameboy memory map
	*/
	class TileRAM
	{
	public:
		static const unsigned int NUM_TILES = 192;
		static const unsigned int TILE_SIZE = 16;

	public:
		TileRAM(MMU& mmu, const LCDController& lcd);
		~TileRAM();

		Tile getTile(uint8_t tilenum) const;
		Tile getSpriteTile(const Sprite& sprite) const;
		std::vector<Tile> getTiles();

		template<typename T>
		uint16_t getTileAddress(int32_t base_addr, uint8_t tilenum) const
		{
			return (uint16_t)(base_addr + ((T)tilenum * TILE_SIZE));
		}

	private:
		void setRow(Tile& tile, uint8_t msb, uint8_t lsb, int row) const;

		Tile flipV(const Tile& old) const;
		Tile flipH(const Tile& old) const;

	private:
		uint8_t* tile_ram_;
		MMU& mmu_;
		const LCDController& lcd_;
	};

}

#endif // GAMEBOY_DISPLAY_H
