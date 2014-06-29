

#include "stack.h"


int pushAF(struct Core* core)
{
	core->mem[core->SP-2] = core->AF.F;
	core->mem[core->SP-1] = core->AF.A;
	core->SP -= 2;
	return 0;
}

int pushBC(struct Core* core)
{
	core->mem[core->SP-2] = core->BC.C;
	core->mem[core->SP-1] = core->BC.B;
	core->SP -= 2;
	return 0;
}

int pushDE(struct Core* core)
{
	core->mem[core->SP-2] = core->DE.E;
	core->mem[core->SP-1] = core->DE.D;
	core->SP -= 2;
	return 0;
}

int pushHL(struct Core* core)
{
	core->mem[core->SP-2] = core->HL.L;
	core->mem[core->SP-1] = core->HL.H;
	return 0;
}

int popAF(struct Core* core)
{
	core->AF.A = core->mem[core->SP+1];
	core->AF.F = core->mem[core->SP];
	core->SP += 2;
	return 0;
}

int popBC(struct Core* core)
{
	core->BC.B = core->mem[core->SP+1];
	core->BC.C = core->mem[core->SP];
	core->SP += 2;
	return 0;
}

int popDE(struct Core* core)
{
	core->DE.D = core->mem[core->SP+1];
	core->DE.E = core->mem[core->SP];
	core->SP += 2;
	return 0;
}

int popHL(struct Core* core)
{
	core->HL.H = core->mem[core->SP+1];
	core->HL.L = core->mem[core->SP];
	core->SP += 2;
	return 0;
}

