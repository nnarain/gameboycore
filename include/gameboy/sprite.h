
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOY_SPRITE_H
#define GAMEBOY_SPRITE_H

#include <cstdint>

namespace gb
{
	/**
		Sprite object that are stored in OAM
	*/
	class Sprite
	{
	public:
		uint8_t y;
		uint8_t x;
		uint8_t tile;
		uint8_t attr;

		constexpr bool isHorizontallyFlipped() const
		{
			return (attr & (1 << 5)) != 0;
		}

		constexpr bool isVerticallyFlipped() const
		{
			return (attr & (1 << 6)) != 0;
		}

		constexpr bool hasPriority() const
		{
			return (attr & (1 << 7)) == 0;
		}
	};
}

#endif // GAMEBOY_SPRITE_H