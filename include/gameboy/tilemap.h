/*
	@author Natesh Narain <nnaraindev@gmail.com>
	@date Spet 15, 2016
*/

#ifndef GAMEBOY_TILEMAP_H
#define GAMEBOY_TILEMAP_H

#include "gameboy/tileram.h"
#include "gameboy/pixel.h"
#include "gameboy/memorymap.h"

#include <array>
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
			BACKGROUND     = (1<<3),
			WINDOW_OVERLAY = (1<<6)
		};

		using Line = std::array<uint8_t, 160>;

	public:

		TileMap(MMU& mmu);
		~TileMap();

		Line getMapLine(Map map, int line);
		Line getTileLine(Map map, int line, uint8_t x_offset, uint8_t y_offset);

		void drawSprites(std::array<Pixel, 160>& scanline, std::array<uint8_t, 160>& color_line, int line);

	private:
		uint16_t getAddress(Map map);

	private:
		TileRAM tileram_;
		MMU& mmu_;

		uint8_t& scx_;
		uint8_t& scy_;
	};
}

#endif // GAMEBOY_TILEMAP_H
