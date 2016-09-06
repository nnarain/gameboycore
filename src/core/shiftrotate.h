
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef SHIFT_ROTATE_H
#define SHIFT_ROTATE_H

#include <stdint.h>

namespace gb
{
	uint8_t rotateLeft(uint8_t val, uint8_t& flags);

	uint8_t rotateRight(uint8_t val, uint8_t& flags);
}

#endif