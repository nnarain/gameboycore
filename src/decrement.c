
#include "decrement.h"
#include "opts.h"


int decA(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->AF.A--;
	bitset(core->AF.F, FLAG_Z, core->AF.A);
	return 1;
}

int decB(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->BC.B--;
	bitset(core->AF.F, FLAG_Z, core->BC.B);
	return 1;
}

int decC(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->BC.C--;
	bitset(core->AF.F, FLAG_Z, core->BC.C);
	return 1;
}

int decD(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->DE.D--;
	bitset(core->AF.F, FLAG_Z, core->DE.D);
	return 1;
}

int decE(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->DE.E--;
	bitset(core->AF.F, FLAG_Z, core->DE.E);
	return 1;
}

int decH(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->HL.H--;
	bitset(core->AF.F, FLAG_Z, core->HL.H);
	return 1;
}

int decL(GBCore* core)
{
	setbit(core->AF.F, FLAG_S);
	core->HL.L--;
	bitset(core->AF.F, FLAG_Z, core->HL.L);
	return 1;
}


