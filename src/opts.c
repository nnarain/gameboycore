
#include "opts.h"

inline uint16_t getNextWord(uint16_t* PC, uint8_t mem[])
{
	//uint8_t x = mem[++(*PC)];
	//uint8_t y = mem[++(*PC)];
	uint8_t x = mem[*PC+1];
	uint8_t y = mem[*PC+2];
	*PC += 2;
	return bytecat(y,x); // in the Z80, 2nd byte is most significant
}