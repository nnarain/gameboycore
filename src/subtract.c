
#include "subtract.h"
#include "opts.h"

void subAA(GBCore* core)
{
	core->AF.A -= core->AF.A;
	bitset(core->AF.F, FLAG_Z, core->AF.A);
}

void subAB(GBCore* core)
{
	core->AF.A -= core->BC.B;
	bitset(core->AF.F, FLAG_Z, core->AF.A);
}

void subAC(GBCore* core)
{
	core->AF.A -= core->BC.C;
	bitset(core->AF.F, FLAG_Z, core->AF.A);
}

void subAD(GBCore* core)
{
	core->AF.A -= core->DE.D;
	bitset(core->AF.F, FLAG_Z, core->AF.A);
}

void subAE(GBCore* core)
{
	core->AF.A -= core->DE.E;
	bitset(core->AF.F, FLAG_Z, core->AF.A);
}

void subAH(GBCore* core)
{
	core->AF.A -= core->HL.H;
	bitset(core->AF.F, FLAG_Z, core->AF.A);
}

void subAL(GBCore* core)
{
	core->AF.A -= core->HL.L;
	bitset(core->AF.F, FLAG_Z, core->AF.A);
}

void subAHL(GBCore* core)
{
	core->AF.A -= core->HL.val;
	bitset(core->AF.F, FLAG_Z, core->AF.A);
}

void subAByte(GBCore* core)
{
	core->AF.A -= core->mem[++core->PC];
	bitset(core->AF.F, FLAG_Z, core->AF.A);
}


void subcAA(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->AF.A + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, core->AF.A);

}

void subcAB(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->BC.B + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, core->AF.A);

}

void subcAC(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->BC.C + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, core->AF.A);

}

void subcAD(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->DE.D + carry(core->AF.F, FLAG_C));

}

void subcAE(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->DE.E + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, core->AF.A);

}

void subcAH(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->HL.H + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, core->AF.A);

}

void subcAL(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->HL.L + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, core->AF.A);

}

void subcA_HL_(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->mem[core->HL.val] + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, core->AF.A);

}

void subcAByte(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->mem[++core->PC] + carry(core->AF.F, FLAG_C));
	bitset(core->AF.F, FLAG_Z, core->AF.A);

}
