
#include "decrement_reg_pair.h"


int decBC(GBCore* core)
{
	core->BC.val--;
	return 1;
}

int decDE(GBCore* core)
{
	core->DE.val--;
	return 1;
}

int decHL(GBCore* core)
{
	core->HL.val--;
	return 1;
}

int decSP(GBCore* core)
{
	core->SP--;
	return 1;
}