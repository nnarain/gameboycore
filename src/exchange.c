
#include "exchange.h"


int exSPHL(GBCore* core)
{
	uint8_t tmpH = core->HL.H;
	uint8_t tmpL = core->HL.L;

	core->HL.H = core->SP + 1;
	core->HL.L = core->SP;
	return 1;
}

int exDEHL(GBCore* core)
{

	uint16_t tmpHL = core->HL.val;

	core->HL.val = core->DE.val;
	core->DE.val = tmpHL;
	return 1;
}
