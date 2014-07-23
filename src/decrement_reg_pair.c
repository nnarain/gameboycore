
#include "decrement_reg_pair.h"


void decBC(GBCore* core)
{
	core->BC.val--;
}

void decDE(GBCore* core)
{
	core->DE.val--;
}

void decHL(GBCore* core)
{
	core->HL.val--;
}

void decSP(GBCore* core)
{
	core->SP--;
}