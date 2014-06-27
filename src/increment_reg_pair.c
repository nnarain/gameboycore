
#include "increment_reg_pair.h"


int incBC(struct Core* core)
{
	core->BC.val++;
	return 0;
}

int incDE(struct Core* core)
{
	core->DE.val++;
	return 0;
}

int incHL(struct Core* core)
{
	core->HL.val++;
	return 0;
}

int incSP(struct Core* core)
{
	core->SP++;
	return 0;
}