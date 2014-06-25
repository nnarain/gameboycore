
#include "GBEmulator.h"
#include "instructionset.h"

#include <time.h>

#ifdef DEBUG
#include <stdio.h>
#endif

int execute(struct Core* core, uint8_t optCode)
{
	uint8_t cycles;

	clock_t tick = clock();

	if(optCode != 0xCB){
		cycles = instructionSet1[optCode].cycles;
		instructionSet1[optCode].impl(core);
	}
	else{
		cycles = instructionSet2[optCode].cycles;
		instructionSet2[core->rom[++core->PC]].impl(core);
	}
 
	float elapseMillis = ( ((float)clock() - (float)tick) / (float)CLOCKS_PER_SEC ) * 1000.0f;

	while(elapseMillis < (CLK_PERIOD * 1000.0f * cycles)){
		elapseMillis = ( ((float)clock() - (float)tick) / (float)CLOCKS_PER_SEC ) * 1000.0f;
#ifdef DEBUG
		
#endif	
	}

	return 0;
}

void bootCore(struct Core* core)
{
	// Initialize all core members to 0
	core->AF.val = 0;
	core->BC.val = 0;
	core->DE.val = 0;
	core->HL.val = 0;
	core->SP     = WORK_RAM_BANK_0_END;
	core->PC     = 0x00;
}

uint8_t* getAddress(struct Core* core, uint16_t addr)
{
	return &core->rom[addr];
}

int genericTransfer(uint8_t* to, uint8_t* from)
{
	*to = *from;
	return 0;
}

/* Core Functions */

int NOP(struct Core* core)
{
	return 0;
}

/* Add Byte instructions */

<<<<<<< HEAD
int decBC(struct Core* core)
{
	core->BC.val--;
	return 0;
}

int decDE(struct Core* core)
{
	core->DE.val--;
	return 0;
}

int decHL(struct Core* core)
{
	core->HL.val--;
	return 0;
}

int decSP(struct Core* core)
{
	core->SP--;
	return 0;
}

int ldAA(struct Core* core)
{
	core->AF.A = core->AF.A;
	return 0;
}

int ldAB(struct Core* core)
{
	core->AF.A = core->BC.B;
	return 0;
}

int ldAC(struct Core* core)
{
	core->AF.A = core->BC.C;
	return 0;
}

int ldAD(struct Core* core)
{
	core->AF.A = core->DE.D;
	return 0;
}

int ldAE(struct Core* core)
{
	core->AF.A = core->BC.B;
	return 0;
}

int ldAH(struct Core* core)
{
	core->AF.A = core->HL.H;
	return 0;
}

int ldAL(struct Core* core)
{
	core->AF.A = core->HL.L;
	return 0;
}

int ldAHL(struct Core* core)
{
	core->AF.A = core->HL.val;
	return 0;
}

int ldAWord(struct Core* core)
{

	return 0;
}

int ldBA(struct Core* core)
{
	core->BC.B = core->AF.A;
	return 0;
}

int ldBB(struct Core* core)
{
	core->BC.B = core->BC.B;
	return 0;
}

int ldBC(struct Core* core)
{
	core->BC.B = core->BC.C;
	return 0;
}

int ldBD(struct Core* core)
{
	core->BC.B = core->DE.D;
	return 0;
}

int ldBE(struct Core* core)
{
	core->BC.B = core->DE.D;
	return 0;
}

int ldBH(struct Core* core)
{
	core->BC.B = core->HL.H;
	return 0;
}

int ldBL(struct Core* core)
{
	core->BC.B = core->HL.L;
	return 0;
}

int ldBHL(struct Core* core)
{
	core->BC.B = core->HL.val;
	return 0;
}

int ldCA(struct Core* core)
{
	core->BC.C = core->AF.A;
	return 0;
}

int ldCB(struct Core* core)
{
	core->BC.C = core->BC.B;
	return 0;
}

int ldCC(struct Core* core)
{
	core->BC.C = core->BC.C;
	return 0;
}

int ldCD(struct Core* core)
{
	core->BC.C = core->DE.D;
	return 0;
}

int ldCE(struct Core* core)
{
	core->BC.C = core->DE.E;
	return 0;
}

int ldCH(struct Core* core)
{
	core->BC.C = core->HL.L;
	return 0;
}

int ldCL(struct Core* core)
{
	core->BC.C = core->HL.L;
	return 0;
}

int ldCHL(struct Core* core)
{
	core->BC.C = core->HL.val;
	return 0;
}

int ldDA(struct Core* core)
{
	core->DE.D = core->AF.A;
	return 0;
}

int ldDB(struct Core* core)
{
	core->DE.D = core->BC.B;
	return 0;
}

int ldDC(struct Core* core)
{
	core->DE.D = core->BC.C;
	return 0;
}

int ldDD(struct Core* core)
{
	core->DE.D = core->DE.D;
	return 0;
}

int ldDH(struct Core* core)
{
	core->DE.D = core->HL.H;
	return 0;
}

int ldDL(struct Core* core)
{
	core->DE.D = core->HL.L;
	return 0;
}

int ldDHL(struct Core* core)
{
	core->DE.D = core->HL.val;
	return 0;
}

int ldEA(struct Core* core)
{
	core->DE.E = core->AF.A;
	return 0;
}

int ldEB(struct Core* core)
{
	core->DE.E = core->BC.B;
	return 0;
}

int ldEC(struct Core* core)
{
	core->DE.E = core->BC.C;
	return 0;
}

int ldED(struct Core* core)
{
	core->DE.E = core->DE.D;
	return 0;
}

int ldEE(struct Core* core)
{
	core->DE.E = core->DE.E;
	return 0;
}

int ldEH(struct Core* core)
{
	core->DE.E = core-HL.H;
	return 0;
}

int ldEL(struct Core* core)
{
	core->DE.E = core->HL.L;
	return 0;
}

int ldEHL(struct Core* core)
{
	core->DE.E = core->HL.val;
	return 0;
}

int ldHA(struct Core* core)
{
	core->HL.H = core->AF.A;
	return 0;
}

int ldHB(struct Core* core)
{
	core->HL.H = core->BC.B;
	return 0;
}

int ldHC(struct Core* core)
{
	core->HL.H = core->BC.C;
	return 0;
}

int ldHD(struct Core* core)
{
	core->HL.H = core->DE.D;
	return 0;
}

int ldHE(struct Core* core)
{
	core->HL.H = core->DE.E;
	return 0;
}

int ldHL(struct Core* core)
{
	core->HL.H = core->HL.L;
	return 0;
}

int ldHHL(struct Core* core)
{
	core->HL.H = core->HL.val;
	return 0;
}

int ldLA(struct Core* core)
{
	core->HL.L = core->AF.A;
	return 0;
}

int ldLB(struct Core* core)
{
	core->HL.L = core->BC.B;
	return 0;
}

int ldLC(struct Core* core)
{
	core->HL.L = core->BC.C;
	return 0;
}

int ldLD(struct Core* core)
{
	core->HL.L = core->DE.D;
	return 0;
}

int ldLE(struct Core* core)
{
	core->HL.L = core->DE.E;
	return 0;
}

int ldLH(struct Core* core)
{
	core->HL.L = core->HL.H;
	return 0;
}

int ldLHL(struct Core* core)
{
	core->HL.L = core->HL.val;
	return 0;
}

int ldHLA(struct Core* core)
{
	core->HL.val = core->AF.A;
	return 0;
}

int ldHLB(struct Core* core)
{
	core->HL.val = core->BC.B;
	return 0;
}

int ldHLC(struct Core* core)
{
	core->HL.val = core->BC.C;
	return 0;
}

int ldHLD(struct Core* core)
{
	core->HL.val = core->DE.D;
	return 0;
}

int ldHLE(struct Core* core)
{
	core->HL.val = core->DE.E;
	return 0;
}

int ldHLH(struct Core* core)
{
	core->HL.val = core->HL.H;
	return 0;
}

int ldHLL(struct Core* core)
{
	core->HL.val = core->HL.L;
	return 0;
}

int ldAByte(struct Core* core)
{
	core->AF.A = core->rom[++core->PC];
	return 0;
}

int ldBByte(struct Core* core)
{
	core->BC.B = core->rom[++core->PC];
	return 0;
}

int ldCByte(struct Core* core)
{
	core->BC.C = core->rom[++core->PC];
	return 0;
}

int ldDByte(struct Core* core)
{
	core->DE.D = core->rom[++core->PC];
	return 0;
}

int ldEByte(struct Core* core)
{
	core->DE.E = core->rom[++core->PC];
	return 0;
}

int ldHByte(struct Core* core)
{
	core->HL.H = core->rom[++core->PC];
	return 0;
}

int ldLByte(struct Core* core)
{
	core->HL.L = core->rom[++core->PC];
	return 0;
}

int ldHLByte(struct Core* core)
{
	core->HL.val = core->rom[++core->PC];
	return 0;
}

int addAA(struct Core* core)
{
	core->AF.A += core->AF.A;
	return 0;
}

int addAB(struct Core* core)
{
	core->AF.A += core->BC.B;
	return 0;
}

int addAC(struct Core* core)
{
	core->AF.A += core->BC.C;
	return 0;
}

int addAD(struct Core* core)
{
	core->AF.A += core->DE.D;
	return 0;
}

int addAE(struct Core* core)
{
	core->AF.A += core->DE.E;
	return 0;
}

int addAH(struct Core* core)
{
	core->AF.A += core->HL.H;
	return 0;
}

int addAL(struct Core* core)
{
	core->AF.A += core->HL.L;
	return 0;
}

int addAHL(struct Core* core)
{
	core->AF.A += core->HL.val;
	return 0;
}

int addAByte(struct Core* core)
{
	core->AF.A += core->rom[++core->PC];
>>>>>>> add-byte-instructions
	return 0;
}