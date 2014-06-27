
#include "opts.h"

inline uint16_t getNextWord(uint16_t* PC, uint8_t mem[])
{
	uint8_t x = mem[++(*PC)];
	uint8_t y = mem[++(*PC)];
	return bytecat(y,x); // in the Z80, 2nd byte is most significant
}