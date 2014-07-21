

#ifndef GB_PALETTE
#define GB_PALETTE

#include <stdint.h>

struct GBColor{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

struct GBPalette{
	struct GBColor colors[4];
};

void paletteInitDefault(struct GBPalette*);

#endif
