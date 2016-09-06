
#include "shiftrotate.h"
#include "bitutil.h"

#define C_BIT 4
#define C_MASK (1 << C_BIT)

namespace gb
{
	uint8_t rotateLeft(uint8_t val, uint8_t& flags)
	{
		uint8_t r = 0;

		uint8_t bit7 = (IS_BIT_SET(val, 7)) ? 1 : 0;

		r = (val << 1) | bit7;

		flags = 0; // clear N, Z and H
		flags |= (bit7 << C_BIT);

		return r;
	}

	uint8_t rotateRight(uint8_t val, uint8_t& flags)
	{
		uint8_t r = 0;

		uint8_t bit0 = (IS_BIT_SET(val, 0)) ? 1 : 0;

		r = (val >> 1) | (bit0 << 7);

		flags = 0; // clear N, Z and H
		flags |= (bit0 << C_BIT);

		return r;
	}
	
}
