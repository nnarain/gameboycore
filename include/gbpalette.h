

#ifndef GB_PALETTE
#define GB_PALETTE

#include <stdint.h>

typedef struct{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
}GBColor;

typedef struct{
	GBColor colors[4];
}GBPalette;

void paletteInitDefault(GBPalette*);

#endif
