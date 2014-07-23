
#include "gbtile.h"

#include <stdio.h>

void loadTile(struct Core* core, struct Tile* tile, int num)
{
	// load tiles from memory
	memcpy( tile->rows, core->mem + CHARACTER_RAM_START + num, TILE_SIZE );

	// convert 16 bit pixel data to color indicies
	int i, bitIdx, k;
	k = 0;
	for(i = 0; i < TILE_ROW_NUM; i++){

		// 00100100 -> LSB
		// 01010101 -> MSB
		// ========
		// 02120302 -> DECIMAL ( Colors 0 - 3 )

		// separate the msb and lsb for the 16-bit number
		uint8_t lsb = (tile->rows[i] & 0xFF00) >> 8;
		uint8_t msb = (tile->rows[i] & 0x00FF ); 

		// add each indiviual bit
		for(bitIdx = 7; bitIdx >= 0; bitIdx--){

			// create a mask using the bit index
			uint8_t mask = ( 1 << bitIdx );

			// get individual bits from bytes and shift downwards to add them.
			// msb is shifted one position less so that it is the most sig bit of a 2 bit number
			uint8_t color = ( (msb & mask) >> bitIdx-1 ) + ((lsb & mask) >> bitIdx);
			tile->colorIdx[k] = color;

			k++;
		}

	}
}
