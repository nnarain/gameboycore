
#include "GBEmulator.h"
#include "instructionset.h"

#include <time.h>

#ifdef DEBUG
#include <stdio.h>
#endif

int execute(struct Core* core, uint8_t optCode)
{
	uint8_t cycles;

	clock_t tick = clock();

	if(optCode != 0xCB){
		cycles = instructionSet1[optCode].cycles;
		instructionSet1[optCode].impl(core);
	}
	else{
		cycles = instructionSet2[optCode].cycles;
		instructionSet2[core->rom[++core->PC]].impl(core);
	}
 
	float elapseMillis = ( ((float)clock() - (float)tick) / (float)CLOCKS_PER_SEC ) * 1000.0f;

	while(elapseMillis < (CLK_PERIOD * 1000.0f * cycles)){
		elapseMillis = ( ((float)clock() - (float)tick) / (float)CLOCKS_PER_SEC ) * 1000.0f;
#ifdef DEBUG
		
#endif	
	}

	return 0;
}

void bootCore(struct Core* core)
{
	// Initialize all core members to 0
	core->AF.val = 0;
	core->BC.val = 0;
	core->DE.val = 0;
	core->HL.val = 0;
	core->SP     = WORK_RAM_BANK_0_END;
	core->PC     = 0x00;
}

uint8_t* getAddress(struct Core* core, uint16_t addr)
{
	return &core->rom[addr];
}

int genericTransfer(uint8_t* to, uint8_t* from)
{
	*to = *from;
	return 0;
}

/* Core Functions */

int NOP(struct Core* core)
{
	return 0;
}

int decA(struct Core* core)
{
	core->AF.A--;
	return 0;
}

int decB(struct Core* core)
{
	core->BC.B--;
	return 0;
}

int decC(struct Core* core)
{
	core->BC.B--;
	return 0;
}

int decD(struct Core* core)
{
	core->DE.D--;
	return 0;
}

int decE(struct Core* core)
{
	core->DE.E--;
	return 0;
}

int decH(struct Core* core)
{
	core->HL.H--;
	return 0;
}

int decL(struct Core* core)
{
	core->HL.L--;
	return 0;
}

int decHL(struct Core* core)
{
	core->HL.val--;
	return 0;
}