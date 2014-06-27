
#include "subtract.h"

int subAA(struct Core* core)
{
	core->AF.A -= core->AF.A;
	return 0;
}

int subAB(struct Core* core)
{
	core->AF.A -= core->BC.B;
	return 0;
}

int subAC(struct Core* core)
{
	core->AF.A -= core->BC.C;
	return 0;
}

int subAD(struct Core* core)
{
	core->AF.A -= core->DE.D;
	return 0;
}

int subAE(struct Core* core)
{
	core->AF.A -= core->DE.E;
	return 0;
}

int subAH(struct Core* core)
{
	core->AF.A -= core->HL.H;
	return 0;
}

int subAL(struct Core* core)
{
	core->AF.A -= core->HL.L;
	return 0;
}

int subAHL(struct Core* core)
{
	core->AF.A -= core->HL.val;
	return 0;
}

int subAByte(struct Core* core)
{
	core->AF.A -= core->rom[++core->PC];
	return 0;
}

