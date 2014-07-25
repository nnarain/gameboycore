
#include "increment_reg_pair.h"


int incBC(GBCore* core)
{
	core->BC.val++;
	return 1;
}

int incDE(GBCore* core)
{
	core->DE.val++;
	return 1;
}

int incHL(GBCore* core)
{
	core->HL.val++;
	return 1;
}

int incSP(GBCore* core)
{
	core->SP++;
	return 1;
}