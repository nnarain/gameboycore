
#include "gbparser.h"

/**
	Extract information from the rom file and populate GBROMData structure.

	@param data
		structure to store data in

	@param file
		file to parse
*/
void gbparse(struct GBROMData* data, FILE* file)
{
	int i;

	// get rom title
	fseek(file, GAME_TITLE_START, SEEK_SET);
	fread(data->title, GAME_TITLE_END - GAME_TITLE_START, sizeof(char), file);

	// get cart type
	fseek(file, CART_TYPE, SEEK_SET);
	fread(&data->cartType, 1, sizeof(uint8_t), file);

	// get number of banks
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);

	data->nBanks = fileSize / (SIZE_BANK);

	// retrieve rom banks
	data->banks = (uint8_t**) malloc( data->nBanks * sizeof(uint8_t*) );

	fseek(file, 0, SEEK_SET);
	for(i = 0; i < data->nBanks; i++){
		data->banks[i] = (uint8_t*) malloc( SIZE_BANK * sizeof(uint8_t) );
		fread(data->banks[i], SIZE_BANK, sizeof(uint8_t), file);
	}

}

void releaseROMData(struct GBROMData* data)
{
	free(data->banks);
}