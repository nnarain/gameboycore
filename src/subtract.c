
#include "subtract.h"
#include "opts.h"

void subAA(GBCore* core)
{
	core->AF.A -= core->AF.A;
}

void subAB(GBCore* core)
{
	core->AF.A -= core->BC.B;
}

void subAC(GBCore* core)
{
	core->AF.A -= core->BC.C;
}

void subAD(GBCore* core)
{
	core->AF.A -= core->DE.D;
}

void subAE(GBCore* core)
{
	core->AF.A -= core->DE.E;
}

void subAH(GBCore* core)
{
	core->AF.A -= core->HL.H;
}

void subAL(GBCore* core)
{
	core->AF.A -= core->HL.L;
}

void subAHL(GBCore* core)
{
	core->AF.A -= core->HL.val;
}

void subAByte(GBCore* core)
{
	core->AF.A -= core->mem[++core->PC];
}


void subcAA(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->AF.A + carry(core->AF.F, FLAG_C));

}

void subcAB(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->BC.B + carry(core->AF.F, FLAG_C));

}

void subcAC(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->BC.C + carry(core->AF.F, FLAG_C));

}

void subcAD(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->DE.D + carry(core->AF.F, FLAG_C));

}

void subcAE(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->DE.E + carry(core->AF.F, FLAG_C));

}

void subcAH(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->HL.H + carry(core->AF.F, FLAG_C));

}

void subcAL(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->HL.L + carry(core->AF.F, FLAG_C));

}

void subcA_HL_(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->mem[core->HL.val] + carry(core->AF.F, FLAG_C));

}

void subcAByte(GBCore* core){

	setbit(core->AF.F, FLAG_S);

	core->AF.A -= (core->mem[++core->PC] + carry(core->AF.F, FLAG_C));

}
