
#include "logic.h"

int AandA(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A &= core->AF.A;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AandB(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A &= core->BC.B;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AandC(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A &= core->BC.C;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AandD(GBCore* core)
{
	core->AF.A &= core->DE.D;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AandE(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A &= core->DE.E;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AandH(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A &= core->HL.H;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AandL(GBCore* core)
{
	core->AF.A &= core->HL.L;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int Aand_HL_(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A &= core->mem[core->HL.val];
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AandByte(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A &= core->mem[++core->PC];
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AxorA(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A ^= core->AF.A;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AxorB(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A ^= core->BC.B;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AxorC(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A ^= core->BC.C;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AxorD(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A ^= core->DE.D;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AxorE(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A ^= core->DE.E;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AxorH(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A ^= core->HL.H;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AxorL(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A ^= core->HL.L;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int Axor_HL_(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A ^= core->mem[core->HL.val];
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AxorByte(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A ^= core->mem[++core->PC];
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}


int AorA(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A |= core->AF.A;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AorB(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A |= core->BC.B;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AorC(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A |= core->BC.C;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AorD(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A |= core->DE.D;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AorE(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A |= core->DE.E;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AorH(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A |= core->HL.H;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AorL(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A |= core->HL.L;
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int Aor_HL_(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A |= core->mem[core->HL.val];
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}

int AorByte(GBCore* core)
{
	clearbit(core->AF.F, FLAG_C);
	core->AF.A |= core->mem[++core->PC];
	bitset(core->AF.F, FLAG_Z, !core->AF.A);
	return 1;	
}








