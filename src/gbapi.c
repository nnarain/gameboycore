#define DEBUG

#include "gbapi.h"
#include "instructionset.h"

#include <stdlib.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#ifdef __unix__
#include <sys/mman.h>
#endif

void step(GBCore* core)
{
	int cycles;

	do{
		cycles += execute(core, core->mem[core->PC]);
	}while(cycles < EXECUTE_CYCLES);
}

/**
	execute the next optcode on the core

	@param core

	@param optCode
*/
int execute(GBCore* core, uint8_t optCode)
{

	uint8_t cycles;

	if(optCode != 0xCB){
		cycles = instructionSet1[optCode].cycles;
		instructionSet1[optCode].impl(core);
	}
	else{
		cycles = instructionSet2[optCode].cycles;
		instructionSet2[core->mem[++core->PC]].impl(core);
	}

	core->PC++;

	return cycles;
}

void swap(GBCore* core, int bankNum)
{
#ifdef DEBUG
	//printf("\nswap\n");
#endif

	core->mbc.currentBank = bankNum;

	int i;

	for(i = 0; i < SIZE_BANK; i++){
		core->mem[i + SWITCHABLE_ROM_BANK_START] = core->mbc.banks[bankNum][i]; 
	}

	//core->PC = 0; // wheres the program counter after swap?
}

uint8_t readMem(GBCore* core, uint16_t addr)
{
	return core->mem[addr];
}
void writeMem(GBCore* core, uint16_t addr, uint8_t b)
{

}

/**
	@param core
*/
void initCore(GBCore* core)
{
	// Initialize all core members to 0
	core->AF.val = 0;
	core->BC.val = 0;
	core->DE.val = 0;
	core->HL.val = 0;
	core->SP     = HIGH_RAM_END;
	core->PC     = 0x00;
	core->mbc.currentBank = 0;

	// load the first 2 rom banks into the memory map
	int i;
	for(i = 0; i <= (SIZE_BANK * 2)+1; i++){
		core->mem[i] = (i <= 0x3FFF) ? core->mbc.banks[0][i] : core->mbc.banks[1][i];
	}
}

/**
	Get a pointer to rom at the specified address

	@param core

	@param addr
*/
uint8_t* getAddress(GBCore* core, uint16_t addr)
{
	return &core->mem[addr];
}


void releaseBanks(GBMemoryBankController* mbc)
{
	int i = 0;
	for(i = 0; i < mbc->nBanks; i++){
		free(mbc->banks[i]);
	}
	free(mbc->banks);
}