
#include "add.h"
#include "opts.h"

void addAA(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);
	
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->AF.A));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->AF.A));
core->AF.A += core->AF.A;
}

void addAB(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->BC.B));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->BC.B));
core->AF.A += core->BC.B;
}

void addAC(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->BC.C));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->BC.C));
core->AF.A += core->BC.C;
}

void addAD(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->DE.D));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->DE.D));
core->AF.A += core->DE.D;
}

void addAE(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->DE.E));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->DE.E));
core->AF.A += core->DE.E;
}

void addAH(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->HL.H));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->HL.H));
core->AF.A += core->HL.H;
}

void addAL(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->HL.L));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, core->HL.L));
core->AF.A += core->HL.L;
}

void addAHL(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	const uint8_t byte = core->mem[core->HL.val];
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, byte));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, byte));
core->AF.A += byte;
}

void addAByte(GBCore* core)
{
	clearbit(core->AF.F, FLAG_S);

	const uint8_t byte = core->mem[++core->PC];
	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, byte));
	bitset(core->AF.F, FLAG_C, fullcarry(core->AF.A, byte));
core->AF.A += byte;
}

void addcAA(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->AF.A));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->AF.A));

	core->AF.A += (core->AF.A + carry(core->AF.F, FLAG_C));
}

void addcAB(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->BC.B));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->BC.B));

	core->AF.A += (core->BC.B + carry(core->AF.F, FLAG_C));
}

void addcAC(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->BC.C));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->BC.C));

	core->AF.A += (core->BC.C + carry(core->AF.F, FLAG_C));
}

void addcAD(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->DE.D));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->DE.D));

	core->AF.A += (core->DE.D + carry(core->AF.F, FLAG_C));
}

void addcAE(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->DE.E));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->DE.E));

	core->AF.A += (core->DE.E + carry(core->AF.F, FLAG_C));
}

void addcAH(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->HL.H));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->HL.H));

	core->AF.A += (core->HL.H + carry(core->AF.F, FLAG_C));
}

void addcAL(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, core->HL.L));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, core->HL.L));

	core->AF.A += (core->HL.L + carry(core->AF.F, FLAG_C));
}

void addcAAddr(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	uint8_t byte = core->mem[getNextWord(&core->PC, core->mem)];

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, byte));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, byte));

	core->AF.A += (byte + carry(core->AF.F, FLAG_C));
}

void addcAByte(GBCore* core){
	clearbit(core->AF.F, FLAG_S);

	uint8_t byte = core->mem[++core->PC];

	bitset(core->AF.F, FLAG_H, halfcarry(core->AF.A, byte));
	bitset(core->AF.F, FLAG_H, fullcarry(core->AF.A, byte));

	core->AF.A += (byte + carry(core->AF.F, FLAG_C));
}