

#include "mbc.h"


void mbcStart(GBMemoryBankController* mbc, uint8_t** map, uint16_t addr, uint8_t b)
{
	switch(addr & 0xF000){

		// $0000 -> $1FFF
		// RAM Enable Register
		case 0x0000:
		case 0x1000:
			mbc->xramOn = (b == XRAM_ENABLE) ? 1 : 0;
			break;

		// $2000 -> $3FFF
		// ROM Bank Number
		case 0x2000:
		case 0x3000:
			break;

		// $4000 -> $5FFF
		// RAM Bank Number
		case 0x4000:
		case 0x5000:
			break;

		// $6000 -> $7FFF
		// ROM / RAM Mode Select
		case 0x6000:
		case 0x7000:
			break;

	}
}