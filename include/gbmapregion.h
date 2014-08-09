#ifndef GB_MAP_REGION
#define GB_MAP_REGION

#include "gbcore.h"

#include <stdint.h>
#include <stdlib.h>

typedef struct{
	uint8_t** ptr;
	uint16_t start;
	uint16_t end;
}GBMapRegion;

void getMemoryMapRegion(GBCore*, GBMapRegion*);

void releaseRegion(GBMapRegion*);

#endif
