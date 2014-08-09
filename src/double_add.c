

#include "double_add.h"

int addHLBC(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->HL.val, core->BC.val));
	bitset(core->AF.F, FLAG_C, fullcarry(core->HL.val, core->BC.val));

	core->HL.val += core->BC.val;
	return 1;
}

int addHLDE(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->HL.val, core->DE.val));
	bitset(core->AF.F, FLAG_C, fullcarry(core->HL.val, core->DE.val));

	core->HL.val += core->DE.val;
	return 1;
}

int addHLHL(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->HL.val, core->HL.val));
	bitset(core->AF.F, FLAG_C, fullcarry(core->HL.val, core->HL.val));

	core->HL.val += core->HL.val;
	return 1;
}

int addHLSP(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->HL.val, core->SP));
	bitset(core->AF.F, FLAG_C, fullcarry(core->HL.val, core->SP));

	core->HL.val += core->SP;
	return 1;
}

