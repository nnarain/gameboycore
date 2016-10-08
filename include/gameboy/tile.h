#ifndef GAMEBOY_TILE_H
#define GAMEBOY_TILE_H

#include <cstdint>

namespace gb
{
	struct Tile
	{
		uint8_t color[64];
	};
}

#endif // !GAMEBOY_TILE_H
