

#ifndef GB_EMULATOR
#define GB_EMULATOR

#include "GBCore.h"

//typedef int (*InstructionImpl)(Core*);

struct Instruction{
	int (*impl)(struct Core*);
	uint8_t cycles;
};

void bootCore(struct Core* core);
uint8_t* getAddress(struct Core*, uint16_t);

int execute(struct Core*, uint8_t);

int transfer(uint8_t* to, uint8_t* from);

/* Core functions */

int NOP(struct Core*);

/* Subtract Byte instructions */

int subAA(struct Core*);
int subAB(struct Core*);
int subAC(struct Core*);
int subAD(struct Core*);
int subAE(struct Core*);
int subAH(struct Core*);
int subAL(struct Core*);
int subAHL(struct Core*);
int subAByte(struct Core*);

#endif // Z80_INSTRUCTION_SET
