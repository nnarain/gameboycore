

#include "shift.h"

int slaA(struct Core* core){

	bitset(core->AF.F, FLAG_C, core->AF.A & 0x80 );
	core->AF.A <<= 1;

	return 0;
}

int slaB(struct Core* core){

	bitset(core->AF.F, FLAG_C, core->BC.B & 0x80 );
	core->BC.B <<= 1;

	return 0;
}

int slaC(struct Core* core){

	bitset(core->BC.C, FLAG_C, core->BC.C & 0x80 );
	core->BC.C <<= 1;

	return 0;
}

int slaD(struct Core* core){

	bitset(core->AF.F, FLAG_C, core->DE.D & 0x80 );
	core->DE.D <<= 1;

	return 0;
}

int slaE(struct Core* core){

	bitset(core->AF.F, FLAG_C, core->DE.E & 0x80 );
	core->DE.E <<= 1;

	return 0;
}
int slaH(struct Core* core){

	bitset(core->AF.F, FLAG_C, core->HL.H & 0x80 );
	core->HL.H <<= 1;

	return 0;
}
int slaL(struct Core* core){

	bitset(core->AF.F, FLAG_C, core->HL.L & 0x80 );
	core->HL.L <<= 1;

	return 0;
}
int sla_HL_(struct Core* core){

	uint8_t byte = core->mem[core->HL.val];

	bitset(core->AF.F, FLAG_C, byte & 0x80 );
	byte <<= 1;

	core->mem[core->HL.val] = byte;

	return 0;
}


int sraA(struct Core* core)
{
	uint8_t cpy = core->AF.A;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->AF.A >>= 1;

	core->AF.A |= (cpy & 0x80);

	return 0;
}
int sraB(struct Core* core)
{
	uint8_t cpy = core->BC.B;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->BC.B >>= 1;

	core->BC.B |= (cpy & 0x80);

	return 0;
}
int sraC(struct Core* core)
{
	uint8_t cpy = core->BC.C;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->BC.C >>= 1;

	core->BC.C |= (cpy & 0x80);

	return 0;
}
int sraD(struct Core* core)
{
	uint8_t cpy = core->DE.D;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->DE.D >>= 1;

	core->DE.D |= (cpy & 0x80);

	return 0;
}
int sraE(struct Core* core)
{
	uint8_t cpy = core->DE.E;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->DE.E >>= 1;

	core->DE.E |= (cpy & 0x80);

	return 0;
}
int sraH(struct Core* core)
{
	uint8_t cpy = core->HL.H;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->HL.H >>= 1;

	core->HL.H |= (cpy & 0x80);

	return 0;
}
int sraL(struct Core* core)
{
	uint8_t cpy = core->HL.L;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->HL.L >>= 1;

	core->HL.L |= (cpy & 0x80);

	return 0;
}
int sra_HL_(struct Core* core)
{
	uint8_t byte = core->mem[core->HL.val];
	uint8_t cpy = byte;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	byte >>= 1;

	byte |= (cpy & 0x80);

	core->mem[core->HL.val] = byte;

	return 0;
}