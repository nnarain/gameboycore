
#include "gbapi.h"
#include "instructionset.h"

#include <stdlib.h>

#define D
#ifdef D
#include <stdio.h>
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
	//uint8_t cycles;

	//clock_t tick = clock();

#ifdef D
	if(core->PC == 0x0150 || core->PC == 0x016e) printf("%X\n", optCode);
#endif

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


void releaseBanks(struct MBC* mbc)
{
	free(mbc);
}