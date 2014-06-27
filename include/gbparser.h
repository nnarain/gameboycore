
#ifndef GB_PARSER
#define GB_PARSER

#include "gbcore.h"
#include <stdio.h>
#include <stdint.h>

//! structure to contain rom meta data
struct GBROMData{
	char title[GAME_TITLE_END - GAME_TITLE_START];
	uint8_t cartType;
	size_t nBanks;
	uint8_t** banks;
};

void gbparse(struct GBROMData* data, FILE* file);

#endif

