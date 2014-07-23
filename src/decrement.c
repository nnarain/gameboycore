
#include "decrement.h"


void decA(GBCore* core)
{
	core->AF.A--;
}

void decB(GBCore* core)
{
	core->BC.B--;
}

void decC(GBCore* core)
{
	core->BC.C--;
}

void decD(GBCore* core)
{
	core->DE.D--;
}

void decE(GBCore* core)
{
	core->DE.E--;
}

void decH(GBCore* core)
{
	core->HL.H--;
}

void decL(GBCore* core)
{
	core->HL.L--;
}


