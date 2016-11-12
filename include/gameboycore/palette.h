/**
	\author Natesh Narain
*/

#ifndef GAMEBOYCORE_PALETTE_H
#define GAMEBOYCORE_PALETTE_H

#include "gameboycore/pixel.h"

#include <array>
#include <cstdint>

namespace gb
{
	class Palette
	{
	public:
		static std::array<Pixel, 4> get(uint8_t reg)
		{
			// default color palette
			static const Pixel colors[] = {
				Pixel(255),
				Pixel(192),
				Pixel(96),
				Pixel(0)
			};

			std::array<Pixel, 4> palette;

			auto color3 = (reg & 0xC0) >> 6;
			auto color2 = (reg & 0x30) >> 4;
			auto color1 = (reg & 0x0C) >> 2;
			auto color0 = (reg & 0x03);

			palette[3] = colors[color3];
			palette[2] = colors[color2];
			palette[1] = colors[color1];
			palette[0] = colors[color0];

			return palette;
		}
	};
}

#endif // GAMEBOYCORE_PALETTE_H
