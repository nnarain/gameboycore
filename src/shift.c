

#include "shift.h"

int slaA(struct Core* core){

	bitset(core->AF.F, FLAG_C, core->AF.A & bv(7) );
	core->AF.A <<= 1;

	return 0;
}

int slaB(struct Core* core){

	bitset(core->AF.F, FLAG_C, core->BC.B & bv(7) );
	core->BC.B <<= 1;

	return 0;
}

int slaC(struct Core* core){

	bitset(core->BC.C, FLAG_C, core->BC.C & bv(7) );
	core->BC.C <<= 1;

	return 0;
}

int slaD(struct Core* core){

	bitset(core->AF.F, FLAG_C, core->DE.D & bv(7) );
	core->DE.D <<= 1;

	return 0;
}

int slaE(struct Core* core){

	bitset(core->AF.F, FLAG_C, core->DE.E & bv(7) );
	core->DE.E <<= 1;

	return 0;
}
int slaH(struct Core* core){

	bitset(core->AF.F, FLAG_C, core->HL.H & bv(7) );
	core->HL.H <<= 1;

	return 0;
}
int slaL(struct Core* core){

	bitset(core->AF.F, FLAG_C, core->HL.L & bv(7) );
	core->HL.L <<= 1;

	return 0;
}
int sla_HL_(struct Core* core){

	uint8_t byte = core->mem[core->HL.val];

	bitset(core->AF.F, FLAG_C, byte & bv(7) );
	byte <<= 1;

	core->mem[core->HL.val] = byte;

	return 0;
}
