
#include "load.h"

void ldAA(GBCore* core)
{
	core->AF.A = core->AF.A;
	
}

void ldAB(GBCore* core)
{
	core->AF.A = core->BC.B;
	
}

void ldAC(GBCore* core)
{
	core->AF.A = core->BC.C;
	
}

void ldAD(GBCore* core)
{
	core->AF.A = core->DE.D;
	
}

void ldAE(GBCore* core)
{
	core->AF.A = core->BC.B;
	
}

void ldAH(GBCore* core)
{
	core->AF.A = core->HL.H;
	
}

void ldAL(GBCore* core)
{
	core->AF.A = core->HL.L;
	
}

void ldAHL(GBCore* core)
{
	core->AF.A = core->mem[core->HL.val];
	
}

void ldABC(GBCore* core)
{
	core->AF.A = core->mem[core->BC.val];
	
}

void ldADE(GBCore* core)
{
	core->AF.A = core->mem[core->DE.val];
	
}

void ldAWord(GBCore* core)
{
	core->AF.A = core->mem[getNextWord(&core->PC, core->mem)];
	
}

void ldBA(GBCore* core)
{
	core->BC.B = core->AF.A;
	
}

void ldBB(GBCore* core)
{
	core->BC.B = core->BC.B;
	
}

void ldBC(GBCore* core)
{
	core->BC.B = core->BC.C;
	
}

void ldBD(GBCore* core)
{
	core->BC.B = core->DE.D;
	
}

void ldBE(GBCore* core)
{
	core->BC.B = core->DE.D;
	
}

void ldBH(GBCore* core)
{
	core->BC.B = core->HL.H;
	
}

void ldBL(GBCore* core)
{
	core->BC.B = core->HL.L;
	
}

void ldBHL(GBCore* core)
{
	core->BC.B = core->mem[core->HL.val];
	
}

void ldCA(GBCore* core)
{
	core->BC.C = core->AF.A;
	
}

void ldCB(GBCore* core)
{
	core->BC.C = core->BC.B;
	
}

void ldCC(GBCore* core)
{
	core->BC.C = core->BC.C;
	
}

void ldCD(GBCore* core)
{
	core->BC.C = core->DE.D;
	
}

void ldCE(GBCore* core)
{
	core->BC.C = core->DE.E;
	
}

void ldCH(GBCore* core)
{
	core->BC.C = core->HL.L;
	
}

void ldCL(GBCore* core)
{
	core->BC.C = core->HL.L;
	
}

void ldCHL(GBCore* core)
{
	core->BC.C = core->mem[core->HL.val];
	
}

void ldDA(GBCore* core)
{
	core->DE.D = core->AF.A;
	
}

void ldDB(GBCore* core)
{
	core->DE.D = core->BC.B;
	
}

void ldDC(GBCore* core)
{
	core->DE.D = core->BC.C;
	
}

void ldDD(GBCore* core)
{
	core->DE.D = core->DE.D;
	
}

void ldDE(GBCore* core)
{
	core->DE.D = core->DE.E;
	
}

void ldDH(GBCore* core)
{
	core->DE.D = core->HL.H;
	
}

void ldDL(GBCore* core)
{
	core->DE.D = core->HL.L;
	
}

void ldDHL(GBCore* core)
{
	core->DE.D = core->mem[core->HL.val];
	
}

void ldEA(GBCore* core)
{
	core->DE.E = core->AF.A;
	
}

void ldEB(GBCore* core)
{
	core->DE.E = core->BC.B;
	
}

void ldEC(GBCore* core)
{
	core->DE.E = core->BC.C;
	
}

void ldED(GBCore* core)
{
	core->DE.E = core->DE.D;
	
}

void ldEE(GBCore* core)
{
	core->DE.E = core->DE.E;
	
}

void ldEH(GBCore* core)
{
	core->DE.E = core->HL.H;
	
}

void ldEL(GBCore* core)
{
	core->DE.E = core->HL.L;
	
}

void ldEHL(GBCore* core)
{
	core->DE.E = core->mem[core->HL.val];
	
}

void ldHA(GBCore* core)
{
	core->HL.H = core->AF.A;
	
}

void ldHB(GBCore* core)
{
	core->HL.H = core->BC.B;
	
}

void ldHC(GBCore* core)
{
	core->HL.H = core->BC.C;
	
}

void ldHD(GBCore* core)
{
	core->HL.H = core->DE.D;
	
}

void ldHE(GBCore* core)
{
	core->HL.H = core->DE.E;
	
}

void ldHH(GBCore* core)
{
	core->HL.H = core->HL.H;
	
}

void ldHL(GBCore* core)
{
	core->HL.H = core->HL.L;
	
}

void ldHHL(GBCore* core)
{
	core->HL.H = core->mem[core->HL.val];
	
}

void ldLA(GBCore* core)
{
	core->HL.L = core->AF.A;
	
}

void ldLB(GBCore* core)
{
	core->HL.L = core->BC.B;
	
}

void ldLC(GBCore* core)
{
	core->HL.L = core->BC.C;
	
}

void ldLD(GBCore* core)
{
	core->HL.L = core->DE.D;
	
}

void ldLE(GBCore* core)
{
	core->HL.L = core->DE.E;
	
}

void ldLH(GBCore* core)
{
	core->HL.L = core->HL.H;
	
}

void ldLL(GBCore* core)
{
	core->HL.L = core->HL.L;
	
}

void ldLHL(GBCore* core)
{
	core->HL.L = core->mem[core->HL.val];
	
}

void ldHLA(GBCore* core)
{
	if(core->HL.val >= PERMANENT_ROM_BANK_START && core->HL.val <= PERMANENT_ROM_BANK_END) 
		swap(core, core->AF.A);
		return;

	core->mem[core->HL.val] = core->AF.A;
	
}

void ldHLB(GBCore* core)
{
	if(core->HL.val >= PERMANENT_ROM_BANK_START && core->HL.val <= PERMANENT_ROM_BANK_END) 
		swap(core, core->BC.B);
		return;

	core->mem[core->HL.val] = core->BC.B;
	
}

void ldHLC(GBCore* core)
{
	if(core->HL.val >= PERMANENT_ROM_BANK_START && core->HL.val <= PERMANENT_ROM_BANK_END) 
		swap(core, core->BC.C);
		return;
	core->mem[core->HL.val] = core->BC.C;
	
}

void ldHLD(GBCore* core)
{
	if(core->HL.val >= PERMANENT_ROM_BANK_START && core->HL.val <= PERMANENT_ROM_BANK_END) 
		swap(core, core->DE.D);
		return;
	core->mem[core->HL.val] = core->DE.D;
	
}

void ldHLE(GBCore* core)
{
	if(core->HL.val >= PERMANENT_ROM_BANK_START && core->HL.val <= PERMANENT_ROM_BANK_END) 
		swap(core, core->DE.E);
		return;
	core->mem[core->HL.val] = core->DE.E;
	
}

void ldHLH(GBCore* core)
{
	if(core->HL.val >= PERMANENT_ROM_BANK_START && core->HL.val <= PERMANENT_ROM_BANK_END) 
		swap(core, core->HL.H);
		return;
	core->mem[core->HL.val] = core->HL.H;
	
}

void ldHLL(GBCore* core)
{
	if(core->HL.val >= PERMANENT_ROM_BANK_START && core->HL.val <= PERMANENT_ROM_BANK_END) 
		swap(core, core->HL.L);
		return;
	core->mem[core->HL.val] = core->HL.L;
	
}

void ldAByte(GBCore* core)
{
	core->AF.A = core->mem[++core->PC];
	
}

void ldBByte(GBCore* core)
{
	core->BC.B = core->mem[++core->PC];
	
}

void ldCByte(GBCore* core)
{
	core->BC.C = core->mem[++core->PC];
	
}

void ldDByte(GBCore* core)
{
	core->DE.D = core->mem[++core->PC];
	
}

void ldEByte(GBCore* core)
{
	core->DE.E = core->mem[++core->PC];
	
}

void ldHByte(GBCore* core)
{
	core->HL.H = core->mem[++core->PC];
	
}

void ldLByte(GBCore* core)
{
	core->HL.L = core->mem[++core->PC];
	
}

void ldHLByte(GBCore* core)
{
	uint8_t byte = core->mem[++core->PC];
	if(core->HL.val >= PERMANENT_ROM_BANK_START && core->HL.val <= PERMANENT_ROM_BANK_END) 
		swap(core, byte);
		return;
	core->mem[core->HL.val] = byte;
	
}

void ldBCA(GBCore* core)
{
	uint8_t byte = core->mem[++core->PC];
	if(core->BC.val >= PERMANENT_ROM_BANK_START && core->BC.val <= PERMANENT_ROM_BANK_END) 
		swap(core, byte);
		return;
	core->mem[core->BC.val] = core->AF.A;
	
}

void ldDEA(GBCore* core)
{
	if(core->DE.val > PERMANENT_ROM_BANK_START && core->DE.val <= PERMANENT_ROM_BANK_END) 
		swap(core, core->AF.A);
		return;
	core->mem[core->DE.val] = core->AF.A;
	
}

void ldAddrA(GBCore* core)
{
	uint16_t addr = getNextWord(&core->PC, core->mem);
	if(addr >= PERMANENT_ROM_BANK_START && addr <= PERMANENT_ROM_BANK_END) 
		swap(core, core->AF.A);
		return;
	core->mem[addr] = core->AF.A;
	
}

/* 16 bit */

void ldBCWord(GBCore* core)
{
	core->BC.val = getNextWord(&core->PC, core->mem);
	
}

void ldDEWord(GBCore* core)
{
	core->DE.val = getNextWord(&core->PC, core->mem);
	
}

void ldHLWord(GBCore* core)
{
	core->HL.val = getNextWord(&core->PC, core->mem);
	
}

void ldSPWord(GBCore* core)
{
	core->SP = getNextWord(&core->PC, core->mem);
	
}

void ldHLAddr(GBCore* core)
{
	core->HL.val = core->mem[getNextWord(&core->PC, core->mem)];
	
}

void ldBCAddr(GBCore* core)
{
	core->BC.val = core->mem[getNextWord(&core->PC, core->mem)];
	
}

void ldDEAddr(GBCore* core)
{
	core->DE.val = core->mem[getNextWord(&core->PC, core->mem)];
	
}

void ldAddrHL(GBCore* core)
{
	uint16_t addr = getNextWord(&core->PC, core->mem);
	if(addr >= PERMANENT_ROM_BANK_START && addr <= PERMANENT_ROM_BANK_END) 
		//swap(core, core->HL.val);
		return;
	core->mem[addr] = core->HL.val;
	
}

void ldSPHL(GBCore* core)
{
	core->SP = core->HL.val;
	
}