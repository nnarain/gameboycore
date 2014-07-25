
#include "increment.h"
#include "opts.h"

void incA(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->AF.A++;
}

void incB(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->BC.B++;
}
void incC(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->BC.C++;
}

void incD(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->DE.D++;
}

void incE(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->DE.E++;
}

void incH(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->HL.H++;
}

void incL(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->HL.L++;
}

void incAddr(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	core->mem[core->HL.val]++;
}