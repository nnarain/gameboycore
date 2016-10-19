
#include "gameboy/tilemap.h"

namespace gb
{
	TileMap::TileMap(const TileRAM& tileram, MMU& mmu, const LCDController& lcd) :
		tileram_(tileram),
		mmu_(mmu),
		lcd_(lcd),
		scx_(mmu.get(memorymap::SCX_REGISTER)),
		scy_(mmu.get(memorymap::SCY_REGISTER))
	{
	}

	std::vector<Tile> TileMap::getMapData(TileRAM tileram, Map map) const
	{
		// simplify this!

		if (map == Map::BACKGROUND)
		{
			if (lcd_.getBackgroundMapLocation() == LCDController::BackgroundMapData::BG_DATA_1)
			{
				return getMapData(tileram, memorymap::BG_MAP_DATA_1_START, memorymap::BG_MAP_DATA_1_END);
			}
			else
			{
				return getMapData(tileram, memorymap::BG_MAP_DATA_2_START, memorymap::BG_MAP_DATA_2_END);
			}
		}
		else // map == WINDOW_OVERLAY
		{
			if (lcd_.getWindowOverlayLocation() == LCDController::BackgroundMapData::BG_DATA_1)
			{
				return getMapData(tileram, memorymap::BG_MAP_DATA_1_START, memorymap::BG_MAP_DATA_1_END);
			}
			else
			{
				return getMapData(tileram, memorymap::BG_MAP_DATA_2_START, memorymap::BG_MAP_DATA_2_END);
			}
		}
	}

	std::vector<Tile> TileMap::getMapData(TileRAM tileram, uint16_t start, uint16_t end) const
	{
		static constexpr auto tiles_per_row = 32;
		static constexpr auto tiles_per_col = 32;
		static constexpr auto tile_width    = 8;
		static constexpr auto tile_height   = 8;

		std::vector<Tile> tiles;

		auto start_row = scy_ / tile_height;
		auto start_col = scx_ / tile_width;

		for (auto row = start_row; row < start_row + 18; ++row)
		{
			for (auto col = start_col; col < start_col + 20; ++col)
			{
				auto tile_offset = start + (tiles_per_row * (row % tiles_per_row)) + (col % tiles_per_col);

				auto tilenum = mmu_.read(tile_offset);

				tiles.push_back(tileram_.getTile(tilenum));
			}
		}

		return tiles;
	}

	TileMap::~TileMap()
	{
	}
}
