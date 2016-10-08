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
		enum class Map
		{
			BACKGROUND, WINDOW_OVERLAY
		};

	public:

		TileMap(const TileRAM& tileram, const MMU& mmu, const LCDController& lcd) : 
			tileram_(tileram),
			mmu_(mmu),
			lcd_(lcd)
		{
		}

		std::vector<Tile> getMapData(TileRAM tileram, Map map) const
		{
			// simplify this!

			if (map == Map::BACKGROUND)
			{
				if (lcd_.getBackgroundMapLocation() == LCDController::BackgroundMapData::BG_DATA_1)
				{
					return getMapData(tileram, memorymap::BG_MAP_DATA_1_START, memorymap::BG_MAP_DATA_1_END);//Iterator(memorymap::BG_MAP_DATA_1_START, memorymap::BG_MAP_DATA_1_END, tileram_, mmu_);
				}
				else
				{
					return getMapData(tileram, memorymap::BG_MAP_DATA_2_START, memorymap::BG_MAP_DATA_2_END);//Iterator(memorymap::BG_MAP_DATA_2_START, memorymap::BG_MAP_DATA_2_END, tileram_, mmu_);
				}
			}
			else // map == WINDOW_OVERLAY
			{
				if (lcd_.getWindowOverlayLocation() == LCDController::BackgroundMapData::BG_DATA_1)
				{
					return getMapData(tileram, memorymap::BG_MAP_DATA_1_START, memorymap::BG_MAP_DATA_1_END);//Iterator(memorymap::BG_MAP_DATA_1_START, memorymap::BG_MAP_DATA_1_END, tileram_, mmu_);
				}
				else
				{
					return getMapData(tileram, memorymap::BG_MAP_DATA_2_START, memorymap::BG_MAP_DATA_2_END); //Iterator(memorymap::BG_MAP_DATA_2_START, memorymap::BG_MAP_DATA_2_END, tileram_, mmu_);
				}
			}
		}

		std::vector<Tile> getMapData(TileRAM tileram, uint16_t start, uint16_t end) const
		{
			std::vector<Tile> tiles;

			for (auto addr = start; addr <= end; ++addr)
			{
				// read the tile number from memory
				auto tilenum = mmu_.read(addr);

				// fetch from tile ram and push onto vector
				tiles.push_back(tileram.getTile(tilenum));
			}

			return tiles;
		}

		~TileMap()
		{
		}

	private:
		TileRAM tileram_;
		const MMU& mmu_;
		const LCDController lcd_;
	};
}

#endif // GAMEBOY_TILEMAP_H
