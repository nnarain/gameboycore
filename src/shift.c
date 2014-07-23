

#include "shift.h"

void slaA(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->AF.A & 0x80 );
	core->AF.A <<= 1;

}

void slaB(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->BC.B & 0x80 );
	core->BC.B <<= 1;

}

void slaC(GBCore* core){

	bitset(core->BC.C, FLAG_C, core->BC.C & 0x80 );
	core->BC.C <<= 1;

}

void slaD(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->DE.D & 0x80 );
	core->DE.D <<= 1;

}

void slaE(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->DE.E & 0x80 );
	core->DE.E <<= 1;

}
void slaH(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->HL.H & 0x80 );
	core->HL.H <<= 1;

}
void slaL(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->HL.L & 0x80 );
	core->HL.L <<= 1;

}
void sla_HL_(GBCore* core){

	uint8_t byte = core->mem[core->HL.val];

	bitset(core->AF.F, FLAG_C, byte & 0x80 );
	byte <<= 1;

	core->mem[core->HL.val] = byte;

}


void sraA(GBCore* core)
{
	uint8_t cpy = core->AF.A;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->AF.A >>= 1;

	core->AF.A |= (cpy & 0x80);

}
void sraB(GBCore* core)
{
	uint8_t cpy = core->BC.B;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->BC.B >>= 1;

	core->BC.B |= (cpy & 0x80);

}
void sraC(GBCore* core)
{
	uint8_t cpy = core->BC.C;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->BC.C >>= 1;

	core->BC.C |= (cpy & 0x80);

}
void sraD(GBCore* core)
{
	uint8_t cpy = core->DE.D;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->DE.D >>= 1;

	core->DE.D |= (cpy & 0x80);

}
void sraE(GBCore* core)
{
	uint8_t cpy = core->DE.E;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->DE.E >>= 1;

	core->DE.E |= (cpy & 0x80);

}
void sraH(GBCore* core)
{
	uint8_t cpy = core->HL.H;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->HL.H >>= 1;

	core->HL.H |= (cpy & 0x80);

}
void sraL(GBCore* core)
{
	uint8_t cpy = core->HL.L;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	core->HL.L >>= 1;

	core->HL.L |= (cpy & 0x80);

}
void sra_HL_(GBCore* core)
{
	uint8_t byte = core->mem[core->HL.val];
	uint8_t cpy = byte;

	bitset(core->AF.F, FLAG_C, cpy & 0x01);
	byte >>= 1;

	byte |= (cpy & 0x80);

	core->mem[core->HL.val] = byte;

}

void srlA(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->AF.A & 0x01);
	core->AF.A >>= 1;

}
void srlB(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->BC.B & 0x01);
	core->BC.B >>= 1;

}
void srlC(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->BC.C & 0x01);
	core->BC.C >>= 1;

}
void srlD(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->DE.D & 0x01);
	core->DE.D >>= 1;

}
void srlE(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->DE.E & 0x01);
	core->DE.E >>= 1;

}
void srlH(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->HL.H & 0x01);
	core->HL.H >>= 1;

}
void srlL(GBCore* core){

	bitset(core->AF.F, FLAG_C, core->HL.L & 0x01);
	core->HL.L >>= 1;

}
void srl_HL_(GBCore* core){

	uint8_t byte = core->mem[core->HL.val];

	bitset(core->AF.F, FLAG_C, byte & 0x01);
	byte >>= 1;

	core->mem[core->HL.val] = byte;

}