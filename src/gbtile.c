
#include "gbtile.h"

#include <stdio.h>

void loadTile(struct Core* core, struct Tile* tile, int num)
{
	// load tiles from memory
	memcpy( tile->rows, core->mem + CHARACTER_RAM_START + num, TILE_SIZE );

	// convert 16 bit pixel data to color indicies
	int i, j, k;
	k = 0;
	for(i = 0; i < TILE_ROW_NUM; i++){

		// 00100100 -> LSB
		// 01010101 -> MSB
		// ========
		// 02120302 -> DECIMAL ( Colors 0 - 3 )

		uint8_t lsb = (uint8_t) (tile->rows[i] & 0xFF00) >> 0xFF;
		uint8_t msb = (uint8_t) (tile->rows[i] & 0x00FF ); 

		for(j = 7; j >= 0; j--){

			uint8_t idx = ( msb << 1 ) + lsb;
			tile->colorIdx[k] = idx;

			k++;
		}

	}
}
