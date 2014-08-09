
#include "branch.h"


int call(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 3) >> 8;
	core->mem[core->SP-2] = (core->PC + 3) & 0x0F;
	core->SP -= 2;

	core->PC = getNextWord(&core->PC, core->mem);

	return 0;
}

int rst00H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0;

	return 0;
}

int rst08H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x08;

	return 0;
}

int rst10H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x10;

	return 0;
}

int rst18H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x18;

	return 0;
}

int rst20H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x20;

	return 0;
}

int rst28H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x28;

	return 0;
}

int rst30H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x30;

	return 0;
}

int rst38H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x38;

	return 0;
}

int ret(GBCore* core)
{
	core->PC = bytecat(core->mem[core->SP+1], core->mem[core->SP]);
	core->SP += 2;

	return 0;
}

int jp(GBCore* core)
{
#ifdef DEBUG
	printf("\njmp\n");
#endif
	core->PC = getNextWord(&core->PC, core->mem);

	return 0;
}

int jpnz(GBCore* core)
{
	if(isClear(core->AF.F, bv(FLAG_Z))) jp(core);
}

int jpz(GBCore* core)
{
	if(isSet(core->AF.F, bv(FLAG_Z))) 
		return jp(core);

	core->PC += 2;
	return 1;
}

int jpnc(GBCore* core)
{
	if(isClear(core->AF.F, bv(FLAG_C))) 
		return jp(core);

	core->PC += 2;

	return 1;
}

int jpc(GBCore* core)
{
	if(isSet(core->AF.F, bv(FLAG_C))) 
		return jp(core);

	core->PC += 2;

	return 1;
}

int pcHL(GBCore* core)
{
	core->PC = core->HL.val;
	return 0;
}

int cnz(GBCore* core)
{
	if(isClear(core->AF.F, bv(FLAG_Z))) 
		return call(core);

	core->PC += 2;

	return 1;
}

int cz(GBCore* core)
{
	if(isSet(core->AF.F, bv(FLAG_Z))) 
		return call(core);

	core->PC += 2;

	return 1;
}

int cnc(GBCore* core)
{
	if(isClear(core->AF.F, bv(FLAG_C))) 
		return call(core);

	core->PC += 2;
	return 1;
}

int cc(GBCore* core)
{
	if(isSet(core->AF.F, bv(FLAG_C))) 
		return call(core);

	core->PC += 2;
	return 1;
}

int rnz(GBCore* core)
{
	if(isClear(core->AF.F, bv(FLAG_Z))) 
		return ret(core);

	return 1;
}

int rz(GBCore* core)
{
	if(isSet(core->AF.F, bv(FLAG_Z))) 
		return ret(core);

	return 1;
}

int rnc(GBCore* core)
{
	if(isClear(core->AF.F, bv(FLAG_C))) 
		return ret(core);

	return 1;
}

int rc(GBCore* core)
{
	if(isSet(core->AF.F, bv(FLAG_C))) 
		return ret(core);

	return 1;
}

int jr(GBCore* core)
{
	signed char idx = core->mem[++core->PC];
	core->PC += idx;
	return 0;
}

int jrnz(GBCore* core)
{
	if( isClear(core->AF.F, bv(FLAG_Z)) ) 
		return jr(core);

	core->PC++;
	return 1;
}

int jrz(GBCore* core)
{
	if( isSet(core->AF.F, bv(FLAG_Z)) ) 
		return jr(core);

	core->PC++;
	return 1;
}

int jrnc(GBCore* core)
{
	if( isClear(core->AF.F, bv(FLAG_C)) ) 
		return jr(core);

	core->PC++;
	return 1;
}

int jrc(GBCore* core)
{
	if( isSet(core->AF.F, bv(FLAG_C)) ) 
		return jr(core);

	core->PC++;
	return 1;
}

int halt(GBCore* core)
{
	NOP(core);
	core->PC--;

	return 1;
}