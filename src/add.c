
#include "add.h"
#include "opts.h"

int addAA(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->AF.A));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->AF.A));
core->AF.A += core->AF.A;
	return 1;
}

int addAB(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->BC.B));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->BC.B));
core->AF.A += core->BC.B;
	return 1;
}

int addAC(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->BC.C));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->BC.C));
core->AF.A += core->BC.C;
	return 1;
}

int addAD(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->DE.D));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->DE.D));
core->AF.A += core->DE.D;
	return 1;
}

int addAE(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->DE.E));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->DE.E));
core->AF.A += core->DE.E;
	return 1;
}

int addAH(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->HL.H));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->HL.H));
core->AF.A += core->HL.H;
	return 1;
}

int addAL(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->HL.L));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->HL.L));
core->AF.A += core->HL.L;
	return 1;
}

int addAHL(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	const uint8_t byte = core->mem[core->HL.val];
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, byte));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, byte));
core->AF.A += byte;
	return 1;
}

int addAByte(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	const uint8_t byte = core->mem[++core->PC];
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, byte));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, byte));
core->AF.A += byte;
	return 1;
}

int addcAA(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->AF.A));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->AF.A));

	core->AF.A += (core->AF.A + carry(core->AF.F, FLAG_C));
	return 1;
}

int addcAB(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->BC.B));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->BC.B));

	core->AF.A += (core->BC.B + carry(core->AF.F, FLAG_C));
	return 1;
}

int addcAC(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->BC.C));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->BC.C));

	core->AF.A += (core->BC.C + carry(core->AF.F, FLAG_C));
	return 1;
}

int addcAD(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->DE.D));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->DE.D));

	core->AF.A += (core->DE.D + carry(core->AF.F, FLAG_C));
	return 1;
}

int addcAE(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->DE.E));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->DE.E));

	core->AF.A += (core->DE.E + carry(core->AF.F, FLAG_C));
	return 1;
}

int addcAH(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->HL.H));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->HL.H));

	core->AF.A += (core->HL.H + carry(core->AF.F, FLAG_C));
	return 1;
}

int addcAL(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->HL.L));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->HL.L));

	core->AF.A += (core->HL.L + carry(core->AF.F, FLAG_C));
	return 1;
}

int addcAAddr(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	uint8_t byte = core->mem[getNextWord(&core->PC, core->mem)];

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, byte));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, byte));

	core->AF.A += (byte + carry(core->AF.F, FLAG_C));
	return 1;
}

int addcAByte(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	uint8_t byte = core->mem[++core->PC];

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, byte));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, byte));

	core->AF.A += (byte + carry(core->AF.F, FLAG_C));
	return 1;
}