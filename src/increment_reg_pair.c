
#include "increment_reg_pair.h"


void incBC(GBCore* core)
{
	core->BC.val++;
}

void incDE(GBCore* core)
{
	core->DE.val++;
}

void incHL(GBCore* core)
{
	core->HL.val++;
}

void incSP(GBCore* core)
{
	core->SP++;
}