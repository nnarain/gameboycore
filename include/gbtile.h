
#ifndef GBTILEMAP
#define GBTILEMAP

#include "gbcore.h"

#include <stdint.h>
#include <string.h>

#define TILE_SIZE 16 ///< 16 Bytes tile size
#define TILE_ROW_NUM 8

typedef struct{
	uint16_t rows[8];
	uint8_t colorIdx[64];
}GBTile;

void loadTile(GBCore*, GBTile*, int);

#endif
