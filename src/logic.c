
#include "logic.h"

void AandA(GBCore* core)
{
	core->AF.A &= core->AF.A;
	
}

void AandB(GBCore* core)
{
	core->AF.A &= core->BC.B;
	
}

void AandC(GBCore* core)
{
	core->AF.A &= core->BC.C;
	
}

void AandD(GBCore* core)
{
	core->AF.A &= core->DE.D;
	
}

void AandE(GBCore* core)
{
	core->AF.A &= core->DE.E;
	
}

void AandH(GBCore* core)
{
	core->AF.A &= core->HL.H;
	
}

void AandL(GBCore* core)
{
	core->AF.A &= core->HL.L;
	
}

void Aand_HL_(GBCore* core)
{
	core->AF.A &= core->mem[core->HL.val];
	
}

void AandByte(GBCore* core)
{
	core->AF.A &= core->mem[++core->PC];
	
}

void AxorA(GBCore* core)
{
	core->AF.A ^= core->AF.A;
	
}

void AxorB(GBCore* core)
{
	core->AF.A ^= core->BC.B;
	
}

void AxorC(GBCore* core)
{
	core->AF.A ^= core->BC.C;
	
}

void AxorD(GBCore* core)
{
	core->AF.A ^= core->DE.D;
	
}

void AxorE(GBCore* core)
{
	core->AF.A ^= core->DE.E;
	
}

void AxorH(GBCore* core)
{
	core->AF.A ^= core->HL.H;
	
}

void AxorL(GBCore* core)
{
	core->AF.A ^= core->HL.L;
	
}

void Axor_HL_(GBCore* core)
{
	core->AF.A ^= core->mem[core->HL.val];
	
}

void AxorByte(GBCore* core)
{
	core->AF.A ^= core->mem[++core->PC];
	
}


void AorA(GBCore* core)
{
	core->AF.A |= core->AF.A;
	
}

void AorB(GBCore* core)
{
	core->AF.A |= core->BC.B;
	
}

void AorC(GBCore* core)
{
	core->AF.A |= core->BC.C;
	
}

void AorD(GBCore* core)
{
	core->AF.A |= core->DE.D;
	
}

void AorE(GBCore* core)
{
	core->AF.A |= core->DE.E;
	
}

void AorH(GBCore* core)
{
	core->AF.A |= core->HL.H;
	
}

void AorL(GBCore* core)
{
	core->AF.A |= core->HL.L;
	
}

void Aor_HL_(GBCore* core)
{
	core->AF.A |= core->mem[core->HL.val];
	
}

void AorByte(GBCore* core)
{
	core->AF.A |= core->mem[++core->PC];
	
}








