
#include "GBCore.h"
#include "GBEmulator.h"



int execute(Core* core, uint8_t optCode)
{
	gb::Instruction instruction = instructionSet1[optCode];

	instruction.impl(core);

	return 0;
}

int genericTransfer(uint8_t* to, uint8_t* from)
{
	*to = *from;
	return 0;
}

/* Core Functions */

int NOP(Core* core)
{
	return 0;
}




