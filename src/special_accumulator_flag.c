

#include "GBCore.h"
#include "special_accumulator_flag.h"
#include "opts.h"

int notA(struct Core* core)
{
	core->AF.A = ~core->AF.A;
	return 0;
}

int SCF(struct Core* core)
{
	setbit(core->AF.F, FLAG_C);
	return 0;
}

int CCF(struct Core* core)
{
	clearbit(core->AF.F, FLAG_C);
	return 0;
}