
#include "GBCore.h"
#include "decrement.h"


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


