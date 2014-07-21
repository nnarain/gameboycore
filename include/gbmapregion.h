#ifndef GB_MAP_REGION
#define GB_MAP_REGION

#include "gbcore.h"

#include <stdint.h>
#include <stdlib.h>

struct GBMapRegion{
	uint8_t** ptr;
	uint16_t start;
	uint16_t end;
};

void getMemoryMapRegion(struct Core*, struct GBMapRegion*);

void releaseRegion(struct GBMapRegion*);

#endif
