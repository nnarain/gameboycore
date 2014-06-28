

#include "double_add.h"

int addHLBC(struct Core* core)
{
	core->HL.val += core->BC.val;
	return 0;
}

int addHLDE(struct Core* core)
{
	core->HL.val += core->DE.val;
	return 0;
}

int addHLHL(struct Core* core)
{
	core->HL.val += core->HL.val;
	return 0;
}

int addHLSP(struct Core* core)
{
	core->HL.val += core->SP;
	return 0;
}

