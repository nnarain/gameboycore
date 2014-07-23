

#include "stack.h"


void pushAF(GBCore* core)
{
	core->mem[core->SP-2] = core->AF.F;
	core->mem[core->SP-1] = core->AF.A;
	core->SP -= 2;
}

void pushBC(GBCore* core)
{
	core->mem[core->SP-2] = core->BC.C;
	core->mem[core->SP-1] = core->BC.B;
	core->SP -= 2;
}

void pushDE(GBCore* core)
{
	core->mem[core->SP-2] = core->DE.E;
	core->mem[core->SP-1] = core->DE.D;
	core->SP -= 2;
}

void pushHL(GBCore* core)
{
	core->mem[core->SP-2] = core->HL.L;
	core->mem[core->SP-1] = core->HL.H;
}

void popAF(GBCore* core)
{
	core->AF.A = core->mem[core->SP+1];
	core->AF.F = core->mem[core->SP];
	core->SP += 2;
}

void popBC(GBCore* core)
{
	core->BC.B = core->mem[core->SP+1];
	core->BC.C = core->mem[core->SP];
	core->SP += 2;
}

void popDE(GBCore* core)
{
	core->DE.D = core->mem[core->SP+1];
	core->DE.E = core->mem[core->SP];
	core->SP += 2;
}

void popHL(GBCore* core)
{
	core->HL.H = core->mem[core->SP+1];
	core->HL.L = core->mem[core->SP];
	core->SP += 2;
}

