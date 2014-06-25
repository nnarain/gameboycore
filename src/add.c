
#include "GBCore.h"
#include "add.h"

int addAA(struct Core* core)
{
	core->AF.A += core->AF.A;
	return 0;
}

int addAB(struct Core* core)
{
	core->AF.A += core->BC.B;
	return 0;
}

int addAC(struct Core* core)
{
	core->AF.A += core->BC.C;
	return 0;
}

int addAD(struct Core* core)
{
	core->AF.A += core->DE.D;
	return 0;
}

int addAE(struct Core* core)
{
	core->AF.A += core->DE.E;
	return 0;
}

int addAH(struct Core* core)
{
	core->AF.A += core->HL.H;
	return 0;
}

int addAL(struct Core* core)
{
	core->AF.A += core->HL.L;
	return 0;
}

int addAHL(struct Core* core)
{
	core->AF.A += core->HL.val;
	return 0;
}

int addAByte(struct Core* core)
{
	core->AF.A += core->rom[++core->PC];
	return 0;
}

