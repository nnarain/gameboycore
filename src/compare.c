
#include "compare.h"

void cmpAA(GBCore* core)
{
	uint8_t r = core->AF.A - core->AF.A;
	bitset(core->AF.F, bv(FLAG_Z), r);

}
void cmpAB(GBCore* core)
{
	uint8_t r = core->AF.A - core->BC.B;
	bitset(core->AF.F, bv(FLAG_Z), r);

}
void cmpAC(GBCore* core)
{
	uint8_t r = core->AF.A - core->BC.C;
	bitset(core->AF.F, bv(FLAG_Z), r);

}
void cmpAD(GBCore* core)
{
	uint8_t r = core->AF.A - core->DE.D;
	bitset(core->AF.F, bv(FLAG_Z), r);

}
void cmpAE(GBCore* core)
{
	uint8_t r = core->AF.A - core->DE.E;
	bitset(core->AF.F, bv(FLAG_Z), r);

}
void cmpAH(GBCore* core)
{
	uint8_t r = core->AF.A - core->HL.H;
	bitset(core->AF.F, bv(FLAG_Z), r);

}
void cmpAL(GBCore* core)
{
	uint8_t r = core->AF.A - core->HL.L;
	bitset(core->AF.F, bv(FLAG_Z), r);

}
void cmpAHL(GBCore* core)
{
	uint8_t r = core->AF.A - core->mem[core->HL.val];
	bitset(core->AF.F, bv(FLAG_Z), r);

}

void cmpByte(GBCore* core)
{
	uint8_t r = core->AF.A - core->mem[++core->PC];
	bitset(core->AF.F, bv(FLAG_Z), r);

}