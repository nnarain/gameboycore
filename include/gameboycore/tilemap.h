/*
	\file tilemap.h
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Sept 15 2016
*/

#ifndef GAMEBOYCORE_TILEMAP_H
#define GAMEBOYCORE_TILEMAP_H

#include "gameboycore/tileram.h"
#include "gameboycore/pixel.h"
#include "gameboycore/sprite.h"
#include "gameboycore/memorymap.h"

#include <vector>
#include <array>
#include <cstdint>

namespace gb
{
	namespace detail
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
				BACKGROUND = (1 << 3),
				WINDOW_OVERLAY = (1 << 6)
			};

			using Line = std::array<uint8_t, 160>;

		public:

			TileMap(MMU& mmu);
			~TileMap();

			Line getBackground(int line);
			Line getWindowOverlay(int line);

			void drawSprites(std::array<Pixel, 160>& scanline, std::array<uint8_t, 160>& color_line, int line, bool cgb_enable, std::array<std::array<gb::Pixel,4>,8>& cgb_palette);

			std::vector<Sprite> getSpriteCache() const;
			std::vector<uint8_t> getTileMap(Map map) const;

		private:
			uint16_t getAddress(Map map) const;

		private:
			detail::TileRAM tileram_;
			MMU& mmu_;
			uint8_t& scx_;
			uint8_t& scy_;

			std::vector<gb::Sprite> sprite_cache_;
		};
	}
}

#endif // GAMEBOYCORE_TILEMAP_H
