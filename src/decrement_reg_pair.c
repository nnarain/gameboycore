
#include "GBCore.h"
#include "decrement_reg_pair.h"


int decBC(struct Core* core)
{
	core->BC.val--;
	return 0;
}

int decDE(struct Core* core)
{
	core->DE.val--;
	return 0;
}

int decHL(struct Core* core)
{
	core->HL.val--;
	return 0;
}

int decSP(struct Core* core)
{
	core->SP--;
	return 0;
}