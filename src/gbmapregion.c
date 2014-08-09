
#include "gbmapregion.h"

void getMemoryMapRegion(GBCore* core, GBMapRegion* region)
{
	
	int size = region->end - region->start;

	if(size < 1) return; // return if size is too small

	// allocate pointer for the size of the region
	region->ptr = (uint8_t**) calloc( size, sizeof(uint8_t*) );

	//
	int i;
	for(i = 0; i < size; i++){
		region->ptr[i] = ((core->mem + region->start) + i);
	}

}

void releaseRegion(GBMapRegion* r)
{
	free(r->ptr);
}
