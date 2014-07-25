
#include "load.h"

int ldAA(GBCore* core)
{
	core->AF.A = core->AF.A;
	return 1;	
}

int ldAB(GBCore* core)
{
	core->AF.A = core->BC.B;
	return 1;	
}

int ldAC(GBCore* core)
{
	core->AF.A = core->BC.C;
	return 1;	
}

int ldAD(GBCore* core)
{
	core->AF.A = core->DE.D;
	return 1;	
}

int ldAE(GBCore* core)
{
	core->AF.A = core->BC.B;
	return 1;	
}

int ldAH(GBCore* core)
{
	core->AF.A = core->HL.H;
	return 1;	
}

int ldAL(GBCore* core)
{
	core->AF.A = core->HL.L;
	return 1;	
}

int ldAHL(GBCore* core)
{
	//core->AF.A = core->mem[core->HL.val];
	core->AF.A = readMem(core, core->HL.val);
	return 1;	
}

int ldABC(GBCore* core)
{
	//core->AF.A = core->mem[core->BC.val];
	core->AF.A = readMem(core, core->BC.val);
	return 1;	
}

int ldADE(GBCore* core)
{
	//core->AF.A = core->mem[core->DE.val];
	core->AF.A = readMem(core, core->DE.val);
	return 1;	
}

int ldAWord(GBCore* core)
{
	//core->AF.A = core->mem[getNextWord(&core->PC, core->mem)];
	core->AF.A = readMem(core, getNextWord(&core->PC, core->mem));
	return 1;	
}

int ldBA(GBCore* core)
{
	core->BC.B = core->AF.A;
	return 1;	
}

int ldBB(GBCore* core)
{
	core->BC.B = core->BC.B;
	return 1;	
}

int ldBC(GBCore* core)
{
	core->BC.B = core->BC.C;
	return 1;	
}

int ldBD(GBCore* core)
{
	core->BC.B = core->DE.D;
	return 1;	
}

int ldBE(GBCore* core)
{
	core->BC.B = core->DE.D;
	return 1;	
}

int ldBH(GBCore* core)
{
	core->BC.B = core->HL.H;
	return 1;	
}

int ldBL(GBCore* core)
{
	core->BC.B = core->HL.L;
	return 1;	
}

int ldBHL(GBCore* core)
{
	core->BC.B = readMem(core, core->HL.val);
	return 1;	
}

int ldCA(GBCore* core)
{
	core->BC.C = core->AF.A;
	return 1;	
}

int ldCB(GBCore* core)
{
	core->BC.C = core->BC.B;
	return 1;	
}

int ldCC(GBCore* core)
{
	core->BC.C = core->BC.C;
	return 1;	
}

int ldCD(GBCore* core)
{
	core->BC.C = core->DE.D;
	return 1;	
}

int ldCE(GBCore* core)
{
	core->BC.C = core->DE.E;
	return 1;	
}

int ldCH(GBCore* core)
{
	core->BC.C = core->HL.L;
	return 1;	
}

int ldCL(GBCore* core)
{
	core->BC.C = core->HL.L;
	return 1;	
}

int ldCHL(GBCore* core)
{
	//core->BC.C = core->mem[core->HL.val];
	core->BC.C = readMem(core, core->HL.val);
	return 1;	
}

int ldDA(GBCore* core)
{
	core->DE.D = core->AF.A;
	return 1;	
}

int ldDB(GBCore* core)
{
	core->DE.D = core->BC.B;
	return 1;	
}

int ldDC(GBCore* core)
{
	core->DE.D = core->BC.C;
	return 1;	
}

int ldDD(GBCore* core)
{
	core->DE.D = core->DE.D;
	return 1;	
}

int ldDE(GBCore* core)
{
	core->DE.D = core->DE.E;
	return 1;	
}

int ldDH(GBCore* core)
{
	core->DE.D = core->HL.H;
	return 1;	
}

int ldDL(GBCore* core)
{
	core->DE.D = core->HL.L;
	return 1;	
}

int ldDHL(GBCore* core)
{
	//core->DE.D = core->mem[core->HL.val];
	core->DE.D = readMem(core, core->HL.val);
	return 1;	
}

int ldEA(GBCore* core)
{
	core->DE.E = core->AF.A;
	return 1;	
}

int ldEB(GBCore* core)
{
	core->DE.E = core->BC.B;
	return 1;	
}

int ldEC(GBCore* core)
{
	core->DE.E = core->BC.C;
	return 1;	
}

int ldED(GBCore* core)
{
	core->DE.E = core->DE.D;
	return 1;	
}

int ldEE(GBCore* core)
{
	core->DE.E = core->DE.E;
	return 1;	
}

int ldEH(GBCore* core)
{
	core->DE.E = core->HL.H;
	return 1;	
}

int ldEL(GBCore* core)
{
	core->DE.E = core->HL.L;
	return 1;	
}

int ldEHL(GBCore* core)
{
	//core->DE.E = core->mem[core->HL.val];
	core->DE.E = readMem(core, core->HL.val);
	return 1;	
}

int ldHA(GBCore* core)
{
	core->HL.H = core->AF.A;
	return 1;	
}

int ldHB(GBCore* core)
{
	core->HL.H = core->BC.B;
	return 1;	
}

int ldHC(GBCore* core)
{
	core->HL.H = core->BC.C;
	return 1;	
}

int ldHD(GBCore* core)
{
	core->HL.H = core->DE.D;
	return 1;	
}

int ldHE(GBCore* core)
{
	core->HL.H = core->DE.E;
	return 1;	
}

int ldHH(GBCore* core)
{
	core->HL.H = core->HL.H;
	return 1;	
}

int ldHL(GBCore* core)
{
	core->HL.H = core->HL.L;
	return 1;	
}

int ldHHL(GBCore* core)
{
	//core->HL.H = core->mem[core->HL.val];
	core->HL.H = readMem(core, core->HL.val);
	return 1;	

}

int ldLA(GBCore* core)
{
	core->HL.L = core->AF.A;
	return 1;	
}

int ldLB(GBCore* core)
{
	core->HL.L = core->BC.B;
	return 1;	
}

int ldLC(GBCore* core)
{
	core->HL.L = core->BC.C;
	return 1;	
}

int ldLD(GBCore* core)
{
	core->HL.L = core->DE.D;
	return 1;	
}

int ldLE(GBCore* core)
{
	core->HL.L = core->DE.E;
	return 1;	
}

int ldLH(GBCore* core)
{
	core->HL.L = core->HL.H;
	return 1;	
}

int ldLL(GBCore* core)
{
	core->HL.L = core->HL.L;
	return 1;	
}

int ldLHL(GBCore* core)
{
	core->HL.L = readMem(core, core->HL.val);//core->mem[core->HL.val];
	return 1;
}

int ldHLA(GBCore* core)
{
	//core->mem[core->HL.val] = core->AF.A;
	writeMem(core, core->HL.val, core->AF.A);
	return 1;	
}

int ldHLB(GBCore* core)
{
	//core->mem[core->HL.val] = core->BC.B;
	writeMem(core, core->HL.val, core->BC.B);
	return 1;
}

int ldHLC(GBCore* core)
{
	//core->mem[core->HL.val] = core->BC.C;
	writeMem(core, core->HL.val, core->BC.C);
	return 1;
}

int ldHLD(GBCore* core)
{
	writeMem(core, core->HL.val, core->DE.D);
	return 1;	
}

int ldHLE(GBCore* core)
{
	//core->mem[core->HL.val] = core->DE.E;
	writeMem(core, core->HL.val, core->DE.E);
	return 1;	
}

int ldHLH(GBCore* core)
{
	//core->mem[core->HL.val] = core->HL.H;
	writeMem(core, core->HL.val, core->HL.H);
	return 1;	
}

int ldHLL(GBCore* core)
{
	writeMem(core, core->HL.val, core->HL.L);
	return 1;	
}

int ldAByte(GBCore* core)
{
	core->AF.A = core->mem[++core->PC];
	return 1;	
}

int ldBByte(GBCore* core)
{
	core->BC.B = core->mem[++core->PC];
	return 1;	
}

int ldCByte(GBCore* core)
{
	core->BC.C = core->mem[++core->PC];
	return 1;	
}

int ldDByte(GBCore* core)
{
	core->DE.D = core->mem[++core->PC];
	return 1;	
}

int ldEByte(GBCore* core)
{
	core->DE.E = core->mem[++core->PC];
	return 1;	
}

int ldHByte(GBCore* core)
{
	//core->HL.H = core->mem[++core->PC];
	core->HL.H = readMem(core, ++core->PC);
	return 1;	
}

int ldLByte(GBCore* core)
{
	//core->HL.L = core->mem[++core->PC];
	core->HL.L = readMem(core, ++core->PC);
	return 1;	
}

int ldHLByte(GBCore* core)
{
	uint8_t byte = core->mem[++core->PC];
	writeMem(core, core->HL.val, byte);
	//core->mem[core->HL.val] = byte;
	return 1;	
}

int ldBCA(GBCore* core)
{
	uint8_t byte = core->mem[++core->PC];
	writeMem(core, core->BC.val, byte);
	return 1;	
}

int ldDEA(GBCore* core)
{
	core->mem[core->DE.val] = core->AF.A;
	return 1;	
}

int ldAddrA(GBCore* core)
{
	uint16_t addr = getNextWord(&core->PC, core->mem);
	writeMem(core, addr, core->AF.A);
	return 1;	

}

/* 16 bit */

int ldBCWord(GBCore* core)
{
	core->BC.val = getNextWord(&core->PC, core->mem);
	return 1;	
}

int ldDEWord(GBCore* core)
{
	core->DE.val = getNextWord(&core->PC, core->mem);
	return 1;	
}

int ldHLWord(GBCore* core)
{
	core->HL.val = getNextWord(&core->PC, core->mem);
	return 1;	
}

int ldSPWord(GBCore* core)
{
	core->SP = getNextWord(&core->PC, core->mem);
	return 1;	
}

int ldHLAddr(GBCore* core)
{
	core->HL.val = readMem(core, getNextWord(&core->PC, core->mem));
	return 1;	
}

int ldBCAddr(GBCore* core)
{
	core->BC.val = readMem(core, getNextWord(&core->PC, core->mem));
	return 1;	
}

int ldDEAddr(GBCore* core)
{
	core->DE.val = readMem(core, getNextWord(&core->PC, core->mem));
	return 1;	
}

int ldAddrHL(GBCore* core)
{
	uint16_t addr = getNextWord(&core->PC, core->mem);
	writeMem(core, addr, core->HL.val);
	return 1;		
}

int ldSPHL(GBCore* core)
{
	core->SP = core->HL.val;
	return 1;	
}