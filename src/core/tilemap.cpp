
#include "gameboy/tilemap.h"
#include "gameboy/oam.h"
#include "bitutil.h"

#include <algorithm>

namespace gb
{
	TileMap::TileMap(MMU& mmu) :
		tileram_(mmu),
		mmu_(mmu),
		scx_(mmu.get(memorymap::SCX_REGISTER)),
		scy_(mmu.get(memorymap::SCY_REGISTER))
	{
	}

	std::vector<Tile> TileMap::getMapData(TileRAM tileram, Map map) const
	{
		// simplify this!

		/*
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
		*/

		return{};
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

	TileMap::Line TileMap::getMapLine(Map map, int line)
	{
		uint8_t x_offset = (map == Map::BACKGROUND)
							? mmu_.read(memorymap::SCX_REGISTER)
							: mmu_.read(memorymap::WX_REGISTER);

		uint8_t y_offset = (map == Map::BACKGROUND)
							? mmu_.read(memorymap::SCY_REGISTER)
							: mmu_.read(memorymap::WY_REGISTER);

		return getTileLine(map, line, x_offset, y_offset);
	}

	TileMap::Line TileMap::getTileLine(Map map, int line, uint8_t x_offset, uint8_t y_offset)
	{
		static constexpr auto tiles_per_row = 32;
		static constexpr auto tiles_per_col = 32;
		static constexpr auto tile_width    = 8;
		static constexpr auto tile_height   = 8;

		auto start = getAddress(map);
		auto umode = (mmu_.read(memorymap::LCDC_REGISTER) & memorymap::LCDC::CHARACTER_DATA) != 0;

		TileMap::Line tileline;

		auto tile_row  = ((y_offset + line) / tile_height);
		auto start_col = x_offset / tile_width;
		auto pixel_row = line % tile_height;

		auto idx = 0;
		for (auto col = start_col; col < start_col + 20; ++col)
		{
			auto tile_offset = start + (tiles_per_row * (tile_row % tiles_per_row)) + (col % tiles_per_col);
			auto tilenum = mmu_.read(tile_offset);

			const auto row = tileram_.getRow(pixel_row, tilenum, umode);

			for (const auto pixel : row)
			{
				tileline[idx++] = pixel;
			}
		}

		return tileline;
	}

	void TileMap::drawSprites(std::array<Pixel, 160>& scanline, int line, const Pixel* palette)
	{
		OAM oam{ mmu_ };

		auto sprites = oam.getSprites();
		auto count = 0;

		for (const auto& sprite : sprites)
		{
			if (count > 10) break;

			auto x = sprite.x - 8;
			auto y = sprite.y - 16;

			// check for out of bounds coordinates
			if (x <= 0 || x >= 168) continue;
			if (y <= 0 || y >= 160) continue;

			// check if the sprite contains the line
			if (line >= y && line < y + sprite.height)
			{				
				// get the pixel row in tile
				auto row = line - y;

				if (sprite.isVerticallyFlipped())
					row = sprite.height - row;

				auto pixel_row = tileram_.getRow(row, sprite.tile, true);

				if (sprite.isHorizontallyFlipped())
					std::reverse(pixel_row.begin(), pixel_row.end());

				for (auto i = 0; i < 8 && x + i < 160; ++i)
				{
					if (sprite.hasPriority())
					{
						if(pixel_row[i] != 0)
							scanline[x + i] = palette[pixel_row[i]];
					}
				}

				count++;
			}
		}
	}

	uint16_t TileMap::getAddress(Map map)
	{
		auto lcdc = mmu_.read(memorymap::LCDC_REGISTER);

		if (map == Map::BACKGROUND)
		{
			return (IS_SET(lcdc, memorymap::LCDC::BG_CODE_AREA)) ? 0x9C00 : 0x9800;
		}
		else
		{
			return (IS_SET(lcdc, memorymap::LCDC::WINDOW_CODE_AREA)) ? 0x9C00 : 0x9800;
		}
	}

	TileMap::~TileMap()
	{
	}
}
