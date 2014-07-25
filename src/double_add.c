

#include "double_add.h"

int addHLBC(GBCore* core)
{
	core->HL.val += core->BC.val;
	return 1;
}

int addHLDE(GBCore* core)
{
	core->HL.val += core->DE.val;
	return 1;
}

int addHLHL(GBCore* core)
{
	core->HL.val += core->HL.val;
	return 1;
}

int addHLSP(GBCore* core)
{
	core->HL.val += core->SP;
	return 1;
}

