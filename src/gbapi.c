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
	int inc;

	if(optCode != 0xCB){
		cycles = instructionSet1[optCode].cycles;
		inc = instructionSet1[optCode].impl(core);
	}
	else{
		cycles = instructionSet2[optCode].cycles;
		inc = instructionSet2[core->mem[++core->PC]].impl(core);
	}

	core->PC += inc;

	return cycles;
}

uint8_t readMem(GBCore* core, uint16_t addr)
{
	return core->mem[addr];
}
void writeMem(GBCore* core, uint16_t addr, uint8_t b)
{
	// Detect write to ROM attempt
	if(addr <= 0x7FFF){
		// This is where the MBC kicks in
		mbcStart(&core->mbc, core->mem, addr, b);
	}
	else{
		// In RAM
		core->mem[addr] = b;
	}
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
	core->PC     = PROGRAM_START;
	core->mbc.romBankIdx = 0;

#ifdef DEBUG
	//printf("nBanks: %d",core->mbc.nBanks);
#endif

	// copy first 2 ROM banks into memory
	memcpy(core->mem, core->mbc.banks[0], SIZE_BANK);
	memcpy(core->mem + SIZE_BANK + 1, core->mbc.banks[1], SIZE_BANK);

	// load the first 2 rom banks into the memory map
	//int i;
	//for(i = 0; i <= (SIZE_BANK * 2)+1; i++){
	//	core->mem[i] = (i <= 0x3FFF) ? core->mbc.banks[0][i] : core->mbc.banks[1][i];
	//}
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