

#include "special_accumulator_flag.h"
#include "opts.h"

void notA(GBCore* core)
{
	core->AF.A = ~core->AF.A;
}

void SCF(GBCore* core)
{
	setbit(core->AF.F, FLAG_C);
}

void CCF(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
}