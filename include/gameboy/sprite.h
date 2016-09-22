#ifndef GAMEBOY_SPRITE_H
#define GAMEBOY_SPRITE_H

#include <cstdint>

namespace gb
{
	struct Sprite
	{
		uint8_t y;
		uint8_t x;
		uint8_t tile;
		uint8_t attr;
	};
}

#endif // GAMEBOY_SPRITE_H