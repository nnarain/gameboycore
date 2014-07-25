
#include "decrement.h"
#include "opts.h"


void decA(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->AF.A--;
	bitset(core->AF.F, FLAG_Z, core->AF.A);
}

void decB(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->BC.B--;
	bitset(core->AF.F, FLAG_Z, core->BC.B);
}

void decC(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->BC.C--;
	bitset(core->AF.F, FLAG_Z, core->BC.C);
}

void decD(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->DE.D--;
	bitset(core->AF.F, FLAG_Z, core->DE.D);
}

void decE(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->DE.E--;
	bitset(core->AF.F, FLAG_Z, core->DE.E);
}

void decH(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->HL.H--;
	bitset(core->AF.F, FLAG_Z, core->HL.H);
}

void decL(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->HL.L--;
	bitset(core->AF.F, FLAG_Z, core->HL.L);
}


