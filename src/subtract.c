
#include "subtract.h"
#include "opts.h"

int subAA(GBCore* core)
{
	core->AF.A -= core->AF.A;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;
}

int subAB(GBCore* core)
{
	core->AF.A -= core->BC.B;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;
}

int subAC(GBCore* core)
{
	core->AF.A -= core->BC.C;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);

	return 1;
}

int subAD(GBCore* core)
{
	core->AF.A -= core->DE.D;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;
}

int subAE(GBCore* core)
{
	core->AF.A -= core->DE.E;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;
}

int subAH(GBCore* core)
{
	core->AF.A -= core->HL.H;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;
}

int subAL(GBCore* core)
{
	core->AF.A -= core->HL.L;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;
}

int subAHL(GBCore* core)
{
	core->AF.A -= core->HL.val;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;
}

int subAByte(GBCore* core)
{
	core->AF.A -= core->mem[++core->PC];
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;
}


int subcAA(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->AF.A + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, !core->AF.A);

	return 1;
}

int subcAB(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->BC.B + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, !core->AF.A);

	return 1;
}

int subcAC(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->BC.C + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, !core->AF.A);

	return 1;
}

int subcAD(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->DE.D + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, !core->AF.A);

	return 1;
}

int subcAE(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->DE.E + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, !core->AF.A);

	return 1;
}

int subcAH(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->HL.H + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, !core->AF.A);

	return 1;
}

int subcAL(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->HL.L + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, !core->AF.A);

	return 1;
}

int subcA_HL_(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->mem[core->HL.val] + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, !core->AF.A);

	return 1;
}

int subcAByte(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->mem[++core->PC] + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, !core->AF.A);

	return 1;
}
