
#include "gbapi.h"
#include "instructionset.h"
#include "opts.h"

#include <stdlib.h>
#include <time.h>

/**
	execute the next optcode on the core

	@param core

	@param optCode
*/
int execute(struct Core* core, uint8_t optCode)
{
	//uint8_t cycles;

	//clock_t tick = clock();

	if(optCode != 0xCB){
		//cycles = instructionSet1[optCode].cycles;
		instructionSet1[optCode].impl(core);
	}
	else{
		//cycles = instructionSet2[optCode].cycles;
		instructionSet2[core->mem[++core->PC]].impl(core);
	}
 
	//float elapseMillis = ( ((float)clock() - (float)tick) / (float)CLOCKS_PER_SEC ) * 1000.0f;

	//while(elapseMillis < (CLK_PERIOD * 1000.0f * cycles)){
	//	elapseMillis = ( ((float)clock() - (float)tick) / (float)CLOCKS_PER_SEC ) * 1000.0f;
	//}

	core->PC++;

	return 0;
}

/**
	@param core
*/
void initCore(struct Core* core)
{
	// Initialize all core members to 0
	core->AF.val = 0;
	core->BC.val = 0;
	core->DE.val = 0;
	core->HL.val = 0;
	core->SP     = HIGH_RAM_END;
	core->PC     = 0x00;
}

/**
	Get a pointer to rom at the specified address

	@param core

	@param addr
*/
uint8_t* getAddress(struct Core* core, uint16_t addr)
{
	return &core->mem[addr];
}

/**
	Initialize the rom banks of the core

	@param core
		Core to use

	@param nBanks
		Number of banks to allocate space for

*/
void initBanks(struct Core* core, int nBanks)
{
	core->banks = (uint8_t**) malloc( nBanks * sizeof(uint8_t*) );

	int i;
	for(i = 0; i < nBanks; i++){
		core->banks[i] = (uint8_t*) malloc( SIZE_BANK * sizeof(uint8_t) );
	}
}

/**
	Loads core banks with rom data.
*/
void loadBanks(struct Core* core, uint8_t** banks, int nBanks)
{
	int i;
	for(i = 0; i < nBanks; i++){
		core->banks[i] = banks[i];

		if(i < 2){
			int j;
			for(j = 0; j < SIZE_BANK; j++){
				core->mem[j + SIZE_BANK] = banks[i][j];
			}
		}
	}
}