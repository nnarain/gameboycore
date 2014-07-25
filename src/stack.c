

#include "stack.h"


int pushAF(GBCore* core)
{
	core->mem[core->SP-2] = core->AF.F;
	core->mem[core->SP-1] = core->AF.A;
	core->SP -= 2;
	return 1;
}

int pushBC(GBCore* core)
{
	core->mem[core->SP-2] = core->BC.C;
	core->mem[core->SP-1] = core->BC.B;
	core->SP -= 2;
	return 1;
}

int pushDE(GBCore* core)
{
	core->mem[core->SP-2] = core->DE.E;
	core->mem[core->SP-1] = core->DE.D;
	core->SP -= 2;
	return 1;
}

int pushHL(GBCore* core)
{
	core->mem[core->SP-2] = core->HL.L;
	core->mem[core->SP-1] = core->HL.H;
	return 1;
}

int popAF(GBCore* core)
{
	core->AF.A = core->mem[core->SP+1];
	core->AF.F = core->mem[core->SP];
	core->SP += 2;
	return 1;
}

int popBC(GBCore* core)
{
	core->BC.B = core->mem[core->SP+1];
	core->BC.C = core->mem[core->SP];
	core->SP += 2;
	return 1;
}

int popDE(GBCore* core)
{
	core->DE.D = core->mem[core->SP+1];
	core->DE.E = core->mem[core->SP];
	core->SP += 2;
	return 1;
}

int popHL(GBCore* core)
{
	core->HL.H = core->mem[core->SP+1];
	core->HL.L = core->mem[core->SP];
	core->SP += 2;
	return 1;
}

