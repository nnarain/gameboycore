
#include "compare.h"

int cmpAA(GBCore* core)
{
	uint8_t r = core->AF.A - core->AF.A;
	bitset(core->AF.F, FLAG_Z, !r);

	return 1;
}
int cmpAB(GBCore* core)
{
	uint8_t r = core->AF.A - core->BC.B;
	bitset(core->AF.F, FLAG_Z, !r);

	return 1;
}
int cmpAC(GBCore* core)
{
	uint8_t r = core->AF.A - core->BC.C;
	bitset(core->AF.F, FLAG_Z, !r);

	return 1;
}
int cmpAD(GBCore* core)
{
	uint8_t r = core->AF.A - core->DE.D;
	bitset(core->AF.F, FLAG_Z, !r);

	return 1;
}
int cmpAE(GBCore* core)
{
	uint8_t r = core->AF.A - core->DE.E;
	bitset(core->AF.F, FLAG_Z, !r);

	return 1;
}
int cmpAH(GBCore* core)
{
	uint8_t r = core->AF.A - core->HL.H;
	bitset(core->AF.F, FLAG_Z, !r);

	return 1;
}
int cmpAL(GBCore* core)
{
	uint8_t r = core->AF.A - core->HL.L;
	bitset(core->AF.F, FLAG_Z, !r);

	return 1;
}
int cmpAHL(GBCore* core)
{
	uint8_t r = core->AF.A - core->mem[core->HL.val];
	bitset(core->AF.F, FLAG_Z, !r);

	return 1;
}

int cmpByte(GBCore* core)
{
	uint8_t r = core->AF.A - core->mem[++core->PC];
	bitset(core->AF.F, FLAG_Z, !r);

	return 1;
}