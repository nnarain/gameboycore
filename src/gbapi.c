#define DEBUG

#include "gbapi.h"
#include "instructionset.h"

#include <stdlib.h>

<<<<<<< HEAD
#define D
#ifdef D
#include <stdio.h>
#endif

=======
#ifdef __unix__
#include <sys/mman.h>
#endif

void step(struct Core* core)
{
	execute(core, core->mem[core->PC]);
}

/**
	execute the next optcode on the core

	@param core

	@param optCode
*/
int execute(struct Core* core, uint8_t optCode)
{

	if(optCode != 0xCB){
		instructionSet1[optCode].impl(core);
	}
	else{
		instructionSet2[core->mem[++core->PC]].impl(core);
	}

	core->PC++;

	return 0;
}

void swap(struct Core* core, int bankNum)
{
#ifdef DEBUG
	printf("swap\n");
#endif
	int i;

	for(i = 0; i < SIZE_BANK; i++){
		core->mem[i + SWITCHABLE_ROM_BANK_START] = core->mbc.banks[bankNum][i]; 
	}
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

	// load the first to rom banks
	int i;
	for(i = 0; i < SIZE_BANK * 2; i++){
		core->mem[i] = (i < 0x4FFF) ? core->mbc.banks[0][i] : core->mbc.banks[1][i];
	}
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


void releaseBanks(struct MBC* mbc)
{
	int i = 0;
	for(i = 0; i < mbc->nBanks; i++){
		free(mbc->banks[i]);
	}
	free(mbc->banks);
}