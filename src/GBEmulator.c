
#include "GBEmulator.h"
#include "instructionset.h"

int execute(struct Core* core, uint8_t optCode)
{
	if(optCode != 0xCB){
		instructionSet1[optCode].impl(core);
	}
	else{
		instructionSet2[optCode].impl(core);
	}

	return 0;
}

void bootCore(struct Core* core)
{
	
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




