/*
	@author Natesh Narain <nnaraindev@gmail.com>
	@date Spet 15, 2016
*/

#ifndef GAMEBOY_TILEMAP_H
#define GAMEBOY_TILEMAP_H

#include "gameboy/tileram.h"
#include "gameboy/lcd_controller.h"
#include "gameboy/memorymap.h"

#include <cstdint>

namespace gb
{
	/**
		\brief Class that knows how to render background map data
	*/
	class TileMap
	{
	public:
		/* Map types */
		enum class Map
		{
			BACKGROUND, WINDOW_OVERLAY
		};

	public:

		TileMap(const TileRAM& tileram, MMU& mmu, const LCDController& lcd);
		~TileMap();

		std::vector<Tile> getMapData(TileRAM tileram, Map map) const;
		std::vector<Tile> getMapData(TileRAM tileram, uint16_t start, uint16_t end) const;

	private:
		TileRAM tileram_;
		const MMU& mmu_;
		const LCDController lcd_;

		uint8_t& scx_;
		uint8_t& scy_;
	};
}

#endif // GAMEBOY_TILEMAP_H
