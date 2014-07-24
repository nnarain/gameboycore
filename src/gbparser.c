
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

	// get cart type
	fseek(file, CART_TYPE, SEEK_SET);
	fread(&mbc->cartType, 1, sizeof(uint8_t), file);

	// get ram size
	fseek(file, CART_RAM_SIZE, SEEK_SET);
	fread(&mbc->xramSize, 1, sizeof(uint8_t), file);

	// init XRAM Banks
	int numRamBanks;
	switch(mbc->xramSize){
		case XRAM_NONE:
			numRamBanks = 0;
			break;
		case XRAM_2KB:
			numRamBanks = 1;
			break;
		case XRAM_8KB:
			numRamBanks = 1;
			break;
		case XRAM_32KB:
			numRamBanks = 4;
			break;
	}

	mbc->xRAMBanks = (uint8_t**) malloc( numRamBanks * sizeof(uint8_t*) );

	for(i = 0; i < numRamBanks; i++){
		mbc->xRAMBanks[i] = (uint8_t*) malloc(SIZE_BANK * sizeof(uint8_t));
	}

	// get number of rom banks
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