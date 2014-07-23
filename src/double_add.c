

#include "double_add.h"

void addHLBC(GBCore* core)
{
	core->HL.val += core->BC.val;
}

void addHLDE(GBCore* core)
{
	core->HL.val += core->DE.val;
}

void addHLHL(GBCore* core)
{
	core->HL.val += core->HL.val;
}

void addHLSP(GBCore* core)
{
	core->HL.val += core->SP;
}

