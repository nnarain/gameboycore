
#include "increment.h"

void incA(GBCore* core)
{
	core->AF.A++;
}

void incB(GBCore* core)
{
	core->BC.B++;
}
void incC(GBCore* core)
{
	core->BC.C++;
}

void incD(GBCore* core)
{
	core->DE.D++;
}

void incE(GBCore* core)
{
	core->DE.E++;
}

void incH(GBCore* core)
{
	core->HL.H++;
}

void incL(GBCore* core)
{
	core->HL.L++;
}

void incAddr(GBCore* core)
{
	core->mem[core->HL.val]++;
}