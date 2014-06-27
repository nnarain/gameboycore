
#include "logic.h"

int AandA(struct Core* core)
{
	core->AF.A &= core->AF.A;
	return 0;
}

int AandB(struct Core* core)
{
	core->AF.A &= core->BC.B;
	return 0;
}

int AandC(struct Core* core)
{
	core->AF.A &= core->BC.C;
	return 0;
}

int AandD(struct Core* core)
{
	core->AF.A &= core->DE.D;
	return 0;
}

int AandE(struct Core* core)
{
	core->AF.A &= core->DE.E;
	return 0;
}

int AandH(struct Core* core)
{
	core->AF.A &= core->HL.H;
	return 0;
}

int AandL(struct Core* core)
{
	core->AF.A &= core->HL.L;
	return 0;
}

int Aand_HL_(struct Core* core)
{
	core->AF.A &= core->mem[core->HL.val];
	return 0;
}

int AandByte(struct Core* core)
{
	core->AF.A &= core->mem[++core->PC];
	return 0;
}

int AxorA(struct Core* core)
{
	core->AF.A ^= core->AF.A;
	return 0;
}

int AxorB(struct Core* core)
{
	core->AF.A ^= core->BC.B;
	return 0;
}

int AxorC(struct Core* core)
{
	core->AF.A ^= core->BC.C;
	return 0;
}

int AxorD(struct Core* core)
{
	core->AF.A ^= core->DE.D;
	return 0;
}

int AxorE(struct Core* core)
{
	core->AF.A ^= core->DE.E;
	return 0;
}

int AxorH(struct Core* core)
{
	core->AF.A ^= core->HL.H;
	return 0;
}

int AxorL(struct Core* core)
{
	core->AF.A ^= core->HL.L;
	return 0;
}

int Axor_HL_(struct Core* core)
{
	core->AF.A ^= core->mem[core->HL.val];
	return 0;
}

int AxorByte(struct Core* core)
{
	core->AF.A ^= core->mem[++core->PC];
	return 0;
}


int AorA(struct Core* core)
{
	core->AF.A |= core->AF.A;
	return 0;
}

int AorB(struct Core* core)
{
	core->AF.A |= core->BC.B;
	return 0;
}

int AorC(struct Core* core)
{
	core->AF.A |= core->BC.C;
	return 0;
}

int AorD(struct Core* core)
{
	core->AF.A |= core->DE.D;
	return 0;
}

int AorE(struct Core* core)
{
	core->AF.A |= core->DE.E;
	return 0;
}

int AorH(struct Core* core)
{
	core->AF.A |= core->HL.H;
	return 0;
}

int AorL(struct Core* core)
{
	core->AF.A |= core->HL.L;
	return 0;
}

int Aor_HL_(struct Core* core)
{
	core->AF.A |= core->mem[core->HL.val];
	return 0;
}

int AorByte(struct Core* core)
{
	core->AF.A |= core->mem[++core->PC];
	return 0;
}








