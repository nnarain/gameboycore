
#include "increment.h"
#include "opts.h"

int incA(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->AF.A++;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;
}

int incB(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->BC.B++;
	bitset(core->AF.F, FLAG_Z, !core->BC.B);
	return 1;
}
int incC(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->BC.C++;
	bitset(core->AF.F, FLAG_Z, !core->BC.C);
	return 1;
}

int incD(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->DE.D++;
	bitset(core->AF.F, FLAG_Z, !core->DE.D);
	return 1;
}

int incE(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->DE.E++;
	bitset(core->AF.F, FLAG_Z, !core->DE.E);
	return 1;
}

int incH(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->HL.H++;
	bitset(core->AF.F, FLAG_Z, !core->HL.H);
	return 1;
}

int incL(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->HL.L++;
	bitset(core->AF.F, FLAG_Z, !core->HL.L);
	return 1;
}

int incAddr(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->mem[core->HL.val]++;
	bitset(core->AF.F, FLAG_Z, !core->mem[core->HL.val]);
	return 1;
}