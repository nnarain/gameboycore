

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

int incA(struct Core*);
int incB(struct Core*);
int incC(struct Core*);
int incD(struct Core*);
int incE(struct Core*);
int incH(struct Core*);
int incL(struct Core*);
int incHL(struct Core*);

int NOP(struct Core*);

#endif // Z80_INSTRUCTION_SET
