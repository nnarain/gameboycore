
#include "GBCore.h"
#include "increment.h"

int incA(struct Core* core)
{
	core->AF.A++;
	return 0;
}

int incB(struct Core* core)
{
	core->BC.B++;
	return 0;
}
int incC(struct Core* core)
{
	core->BC.C++;
	return 0;
}

int incD(struct Core* core)
{
	core->DE.D++;
	return 0;
}

int incE(struct Core* core)
{
	core->DE.E++;
	return 0;
}

int incH(struct Core* core)
{
	core->HL.H++;
	return 0;
}

int incL(struct Core* core)
{
	core->HL.L++;
	return 0;
}

int incHL(struct Core* core)
{
	core->HL.val++;
	return 0;
}
