
#include "subtract.h"
#include "opts.h"

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
	core->AF.A -= core->mem[++core->PC];
	return 0;
}


int subcAA(struct Core* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->AF.A + carry(core->AF.F, FLAG_C));

	return 0;
}

int subcAB(struct Core* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->BC.B + carry(core->AF.F, FLAG_C));

	return 0;
}

int subcAC(struct Core* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->BC.C + carry(core->AF.F, FLAG_C));

	return 0;
}

int subcAD(struct Core* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->DE.D + carry(core->AF.F, FLAG_C));

	return 0;
}

int subcAE(struct Core* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->DE.E + carry(core->AF.F, FLAG_C));

	return 0;
}

int subcAH(struct Core* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->HL.H + carry(core->AF.F, FLAG_C));

	return 0;
}

int subcAL(struct Core* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->HL.L + carry(core->AF.F, FLAG_C));

	return 0;
}

int subcA_HL_(struct Core* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->mem[core->HL.val] + carry(core->AF.F, FLAG_C));

	return 0;
}

int subcAByte(struct Core* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->mem[++core->PC] + carry(core->AF.F, FLAG_C));

	return 0;
}
