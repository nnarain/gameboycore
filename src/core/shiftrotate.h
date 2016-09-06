
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef SHIFT_ROTATE_H
#define SHIFT_ROTATE_H

#include <stdint.h>

namespace gb
{
	/**
		Rotate bits left and set carry flags
	*/
	uint8_t rotateLeft(uint8_t val, uint8_t& flags);

	/**
		Rotate bits left through the carry flag
	*/
	uint8_t rotateLeftCarry(uint8_t val, uint8_t& flags);

	/**
		Rotate bits right adn set carry flag
	*/
	uint8_t rotateRight(uint8_t val, uint8_t& flags);

	/**
		Rotate bits right through carry flag
	*/
	uint8_t rotateRightCarry(uint8_t val, uint8_t& flags);
}

#endif