
#include "logic.h"

int AandA(GBCore* core)
{
	core->AF.A &= core->AF.A;
	return 1;	
}

int AandB(GBCore* core)
{
	core->AF.A &= core->BC.B;
	return 1;	
}

int AandC(GBCore* core)
{
	core->AF.A &= core->BC.C;
	return 1;	
}

int AandD(GBCore* core)
{
	core->AF.A &= core->DE.D;
	return 1;	
}

int AandE(GBCore* core)
{
	core->AF.A &= core->DE.E;
	return 1;	
}

int AandH(GBCore* core)
{
	core->AF.A &= core->HL.H;
	return 1;	
}

int AandL(GBCore* core)
{
	core->AF.A &= core->HL.L;
	return 1;	
}

int Aand_HL_(GBCore* core)
{
	core->AF.A &= core->mem[core->HL.val];
	return 1;	
}

int AandByte(GBCore* core)
{
	core->AF.A &= core->mem[++core->PC];
	return 1;	
}

int AxorA(GBCore* core)
{
	core->AF.A ^= core->AF.A;
	return 1;	
}

int AxorB(GBCore* core)
{
	core->AF.A ^= core->BC.B;
	return 1;	
}

int AxorC(GBCore* core)
{
	core->AF.A ^= core->BC.C;
	return 1;	
}

int AxorD(GBCore* core)
{
	core->AF.A ^= core->DE.D;
	return 1;	
}

int AxorE(GBCore* core)
{
	core->AF.A ^= core->DE.E;
	return 1;	
}

int AxorH(GBCore* core)
{
	core->AF.A ^= core->HL.H;
	return 1;	
}

int AxorL(GBCore* core)
{
	core->AF.A ^= core->HL.L;
	return 1;	
}

int Axor_HL_(GBCore* core)
{
	core->AF.A ^= core->mem[core->HL.val];
	return 1;	
}

int AxorByte(GBCore* core)
{
	core->AF.A ^= core->mem[++core->PC];
	return 1;	
}


int AorA(GBCore* core)
{
	core->AF.A |= core->AF.A;
	return 1;	
}

int AorB(GBCore* core)
{
	core->AF.A |= core->BC.B;
	return 1;	
}

int AorC(GBCore* core)
{
	core->AF.A |= core->BC.C;
	return 1;	
}

int AorD(GBCore* core)
{
	core->AF.A |= core->DE.D;
	return 1;	
}

int AorE(GBCore* core)
{
	core->AF.A |= core->DE.E;
	return 1;	
}

int AorH(GBCore* core)
{
	core->AF.A |= core->HL.H;
	return 1;	
}

int AorL(GBCore* core)
{
	core->AF.A |= core->HL.L;
	return 1;	
}

int Aor_HL_(GBCore* core)
{
	core->AF.A |= core->mem[core->HL.val];
	return 1;	
}

int AorByte(GBCore* core)
{
	core->AF.A |= core->mem[++core->PC];
	return 1;	
}








