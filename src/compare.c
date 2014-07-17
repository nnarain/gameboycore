
#include "compare.h"

int cmpAA(struct Core* core)
{
	uint8_t r = core->AF.A - core->AF.A;
	bitset(core->AF.F, bv(FLAG_Z), r);

	return 0;
}
int cmpAB(struct Core* core)
{
	uint8_t r = core->AF.A - core->BC.B;
	bitset(core->AF.F, bv(FLAG_Z), r);

	return 0;
}
int cmpAC(struct Core* core)
{
	uint8_t r = core->AF.A - core->BC.C;
	bitset(core->AF.F, bv(FLAG_Z), r);

	return 0;
}
int cmpAD(struct Core* core)
{
	uint8_t r = core->AF.A - core->DE.D;
	bitset(core->AF.F, bv(FLAG_Z), r);

	return 0;
}
int cmpAE(struct Core* core)
{
	uint8_t r = core->AF.A - core->DE.E;
	bitset(core->AF.F, bv(FLAG_Z), r);

	return 0;
}
int cmpAH(struct Core* core)
{
	uint8_t r = core->AF.A - core->HL.H;
	bitset(core->AF.F, bv(FLAG_Z), r);

	return 0;
}
int cmpAL(struct Core* core)
{
	uint8_t r = core->AF.A - core->HL.L;
	bitset(core->AF.F, bv(FLAG_Z), r);

	return 0;
}
int cmpAHL(struct Core* core)
{
	uint8_t r = core->AF.A - core->mem[core->HL.val];
	bitset(core->AF.F, bv(FLAG_Z), r);

	return 0;
}

