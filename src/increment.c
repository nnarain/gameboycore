
#include "increment.h"
#include "opts.h"

int incA(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->AF.A++;
	return 1;
}

int incB(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->BC.B++;
	return 1;
}
int incC(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->BC.C++;
	return 1;
}

int incD(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->DE.D++;
	return 1;
}

int incE(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->DE.E++;
	return 1;
}

int incH(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->HL.H++;
	return 1;
}

int incL(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->HL.L++;
	return 1;
}

int incAddr(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->mem[core->HL.val]++;
	return 1;
}