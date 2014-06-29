
#include "add.h"
#include "opts.h"

int addAA(struct Core* core)
{
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->AF.A));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->AF.A));
	core->AF.A += core->AF.A;
	return 0;
}

int addAB(struct Core* core)
{
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->BC.B));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->BC.B));
	core->AF.A += core->BC.B;
	return 0;
}

int addAC(struct Core* core)
{
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->BC.C));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->BC.C));
	core->AF.A += core->BC.C;
	return 0;
}

int addAD(struct Core* core)
{
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->DE.D));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->DE.D));
	core->AF.A += core->DE.D;
	return 0;
}

int addAE(struct Core* core)
{
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->DE.E));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->DE.E));
	core->AF.A += core->DE.E;
	return 0;
}

int addAH(struct Core* core)
{
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->HL.H));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->HL.H));
	core->AF.A += core->HL.H;
	return 0;
}

int addAL(struct Core* core)
{
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->HL.L));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->HL.L));
	core->AF.A += core->HL.L;
	return 0;
}

int addAHL(struct Core* core)
{
	const uint8_t byte = core->mem[core->HL.val];
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, byte));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, byte));
	core->AF.A += byte;
	return 0;
}

int addAByte(struct Core* core)
{
	const uint8_t byte = core->mem[++core->PC];
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, byte));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, byte));
	core->AF.A += byte;
	return 0;
}

