
#include "gbparser.h"

/**
	Extract information from the rom file and populate GBROMData structure.

	@param data
		structure to store data in

	@param file
		file to parse
*/
void gbparse(GBMemoryBankController* mbc, FILE* file)
{
	int i;

	// get rom title
	//fseek(file, GAME_TITLE_START, SEEK_SET);
	//fread(data->title, GAME_TITLE_END - GAME_TITLE_START, sizeof(char), file);

	// get cart type
	fseek(file, CART_TYPE, SEEK_SET);
	fread(&mbc->cartType, 1, sizeof(uint8_t), file);

	// get number of banks
	fseek(file, 0, SEEK_END);
	size_t fileSize = ftell(file);

	mbc->nBanks = fileSize / (SIZE_BANK);

	// retrieve rom banks
	mbc->banks = (uint8_t**) malloc( mbc->nBanks * sizeof(uint8_t*) );

	fseek(file, 0, SEEK_SET);
	for(i = 0; i < mbc->nBanks; i++){
		mbc->banks[i] = (uint8_t*) malloc( SIZE_BANK * sizeof(uint8_t) );
		fread(mbc->banks[i], SIZE_BANK, sizeof(uint8_t), file);
	}

}

//void releaseROMData(struct GBROMData* data)
//{
//	free(data->banks);
//}