/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Oct 23 2016
*/

#ifndef GAMEBOY_PIXEL_H
#define GAMEBOY_PIXEL_H

#include <cstdint>

namespace gb
{
	struct Pixel
	{
		Pixel() : 
			r(0), g(0), b(0)
		{
		}

		Pixel(uint8_t r, uint8_t g, uint8_t b) :
			r(r), g(g), b(b)
		{
		}

		Pixel(uint8_t v) : r(v), g(v), b(v)
		{
		}

		uint8_t r;
		uint8_t g;
		uint8_t b;
	};
}

#endif // GAMEBOY_PIXEL_H

