

#include "shift.h"

int slaA(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->AF.A & 0x80 );
	core->AF.A <<= 1;
	return 1;
}

int slaB(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->BC.B & 0x80 );
	core->BC.B <<= 1;
	return 1;
}

int slaC(GBCore* core){

	bitset(core->BC.C, FLAG_C, core->BC.C & 0x80 );
	core->BC.C <<= 1;
	return 1;
}

int slaD(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->DE.D & 0x80 );
	core->DE.D <<= 1;
	return 1;
}

int slaE(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->DE.E & 0x80 );
	core->DE.E <<= 1;
	return 1;
}
int slaH(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->HL.H & 0x80 );
	core->HL.H <<= 1;
	return 1;
}
int slaL(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->HL.L & 0x80 );
	core->HL.L <<= 1;
	return 1;
}
int sla_HL_(GBCore* core){

	uint8_t byte = core->mem[core->HL.val];

	bitset(core->AF.F, FLAG_C, byte & 0x80 );
	byte <<= 1;

	core->mem[core->HL.val] = byte;
	return 1;
}


int sraA(GBCore* core)
{
	uint8_t cpy = core->AF.A;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->AF.A >>= 1;

	core->AF.A |= (cpy & 0x80);
	return 1;
}
int sraB(GBCore* core)
{
	uint8_t cpy = core->BC.B;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->BC.B >>= 1;

	core->BC.B |= (cpy & 0x80);
	return 1;
}
int sraC(GBCore* core)
{
	uint8_t cpy = core->BC.C;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->BC.C >>= 1;

	core->BC.C |= (cpy & 0x80);
	return 1;
}
int sraD(GBCore* core)
{
	uint8_t cpy = core->DE.D;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->DE.D >>= 1;

	core->DE.D |= (cpy & 0x80);
	return 1;
}
int sraE(GBCore* core)
{
	uint8_t cpy = core->DE.E;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->DE.E >>= 1;

	core->DE.E |= (cpy & 0x80);
	return 1;
}
int sraH(GBCore* core)
{
	uint8_t cpy = core->HL.H;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->HL.H >>= 1;

	core->HL.H |= (cpy & 0x80);
	return 1;
}
int sraL(GBCore* core)
{
	uint8_t cpy = core->HL.L;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->HL.L >>= 1;

	core->HL.L |= (cpy & 0x80);
	return 1;
}
int sra_HL_(GBCore* core)
{
	uint8_t byte = core->mem[core->HL.val];
	uint8_t cpy = byte;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	byte >>= 1;

	byte |= (cpy & 0x80);

	core->mem[core->HL.val] = byte;
	return 1;
}

int srlA(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->AF.A & 0x01);
	core->AF.A >>= 1;
	return 1;
}
int srlB(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->BC.B & 0x01);
	core->BC.B >>= 1;
	return 1;
}
int srlC(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->BC.C & 0x01);
	core->BC.C >>= 1;
	return 1;
}
int srlD(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->DE.D & 0x01);
	core->DE.D >>= 1;
	return 1;
}
int srlE(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->DE.E & 0x01);
	core->DE.E >>= 1;
	return 1;
}
int srlH(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->HL.H & 0x01);
	core->HL.H >>= 1;
	return 1;
}
int srlL(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->HL.L & 0x01);
	core->HL.L >>= 1;
	return 1;
}
int srl_HL_(GBCore* core){

	uint8_t byte = core->mem[core->HL.val];

	bitset(core->AF.F, FLAG_C, byte & 0x01);
	byte >>= 1;

	core->mem[core->HL.val] = byte;
	return 1;
}