
#include "gameboycore/tilemap.h"
#include "gameboycore/oam.h"
#include "gameboycore/palette.h"

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

	TileMap::Line TileMap::getBackground(int line)
	{
		static constexpr auto tiles_per_row = 32;
		static constexpr auto tiles_per_col = 32;
		static constexpr auto tile_width    = 8;
		static constexpr auto tile_height   = 8;

		auto start = getAddress(Map::BACKGROUND);
		auto umode = (mmu_.read(memorymap::LCDC_REGISTER) & memorymap::LCDC::CHARACTER_DATA) != 0;

		TileMap::Line tileline;

		auto scx = mmu_.read(memorymap::SCX_REGISTER);
		auto scy = mmu_.read(memorymap::SCY_REGISTER);


		auto tile_row  = ((scy + line) / tile_height);
		auto start_tile_col = scx / tile_width;
		auto pixel_row = (scy + line) % tile_height;

		auto idx = 0;
		for (auto tile_col = start_tile_col; tile_col < start_tile_col + 21; ++tile_col)
		{
			auto tile_offset = start + (tiles_per_row * (tile_row % tiles_per_row)) + (tile_col % tiles_per_col);
			auto tilenum = mmu_.read(tile_offset);

			const auto row = tileram_.getRow(pixel_row, tilenum, umode);

			auto pixel_col = tile_col * tile_width;

			for (auto i = 0u; i < row.size(); ++i)
			{
				// TODO: this can be improved
				if(pixel_col >= scx && pixel_col <= scx + 160 && idx < 160)
					tileline[idx++] = row[i];
				pixel_col++;
			}
		}

		return tileline;
	}

	TileMap::Line TileMap::getWindowOverlay(int line)
	{
		static constexpr auto tiles_per_row = 32;
		static constexpr auto tiles_per_col = 32;
		static constexpr auto tile_width = 8;
		static constexpr auto tile_height = 8;

		TileMap::Line tileline{};

		auto wy = mmu_.read(memorymap::WY_REGISTER);
		auto umode = (mmu_.read(memorymap::LCDC_REGISTER) & memorymap::LCDC::CHARACTER_DATA) != 0;

		auto window_row = line - wy;
		auto tile_row = window_row / tile_height;
		auto idx = 0;

		auto start = getAddress(Map::WINDOW_OVERLAY);

		for (auto tile_col = 0; tile_col < 20; ++tile_col)
		{
			auto tile_offset = start + ((tiles_per_row * tile_row) + tile_col);
			auto tilenum = mmu_.read(tile_offset);

			const auto pixel_row = tileram_.getRow(line % tile_height, tilenum, umode);

			for (const auto pixel : pixel_row)
			{
				tileline[idx++] = pixel;
			}
		}

		return tileline;
	}

	void TileMap::drawSprites(std::array<Pixel, 160>& scanline, std::array<uint8_t, 160>& color_line, int line)
	{
		OAM oam{ mmu_ };
		
		auto palette0 = Palette::get(mmu_.read(memorymap::OBP0_REGISTER));
		auto palette1 = Palette::get(mmu_.read(memorymap::OBP1_REGISTER));

		auto sprites = oam.getSprites();
		auto count = 0;

		for (const auto& sprite : sprites)
		{
			if (count > 10) break;


			// check for out of bounds coordinates
			if (sprite.x == 0 || sprite.x >= 168) continue;
			if (sprite.y == 0 || sprite.y >= 160) continue;

			auto x = sprite.x - 8;
			auto y = sprite.y - 16;

			// check if the sprite contains the line
			if (line >= y && line < y + sprite.height)
			{				
				// get the pixel row in tile
				auto row = line - y;

				if (sprite.isVerticallyFlipped())
					row = sprite.height - row - 1;

				auto pixel_row = tileram_.getRow(row, sprite.tile, true);

				if (sprite.isHorizontallyFlipped())
					std::reverse(pixel_row.begin(), pixel_row.end());

				// get color palette for this sprite
				const auto& palette = (sprite.paletteOBP0() == 0) ? palette0 : palette1;

				for (auto i = 0; i < 8; ++i)
				{
					if ((x + i) < 0 || (x + i) >= 160) continue;

					if (sprite.hasPriority())
					{
						if(pixel_row[i] != 0)
							scanline[x + i] = palette[pixel_row[i]];
					}
					else
					{
						// if priority is to th background the sprite is behind colors 1-3
						if (color_line[x + i] == 0 && pixel_row[i] != 0)
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
