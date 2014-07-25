

#include "special_accumulator_flag.h"
#include "opts.h"

int notA(GBCore* core)
{
	core->AF.A = ~core->AF.A;
}

int SCF(GBCore* core)
{
	setbit(core->AF.F, FLAG_C);
}

int CCF(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
}