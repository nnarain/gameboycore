
#include "gameboy/tilemap.h"

namespace gb
{
	TileMap::TileMap(const TileRAM& tileram, const MMU& mmu, const LCDController& lcd) :
		tileram_(tileram),
		mmu_(mmu),
		lcd_(lcd)
	{
	}

	std::vector<Tile> TileMap::getMapData(TileRAM tileram, Map map) const
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

	std::vector<Tile> TileMap::getMapData(TileRAM tileram, uint16_t start, uint16_t end) const
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

	TileMap::~TileMap()
	{
	}
}
