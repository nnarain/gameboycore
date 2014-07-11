
#include "branch.h"


int call(struct Core* core)
{
	core->mem[core->SP-1] = core->PC >> 8;
	core->mem[core->SP-2] = core->PC & 0x0F;
	core->SP -= 2;

	core->PC = getNextWord(&core->PC, core->mem);

	return 0;
}

int ret(struct Core* core)
{
	core->PC = bytecat(core->mem[core->SP+1], core->mem[core->SP]);
	core->SP += 2;
	return 0;
}

int jp(struct Core* core)
{
	core->PC = getNextWord(&core->PC, core->mem);
	return 0;
}

int jpnz(struct Core* core)
{
	if(isClear(core->AF.F, bv(FLAG_Z))) core->PC = jp(core);
	return 0;
}

int jpz(struct Core* core)
{
	if(isSet(core->AF.F, bv(FLAG_Z))) jp(core);
	return 0;
}

int jpnc(struct Core* core)
{
	if(isClear(core->AF.F, bv(FLAG_C))) jp(core);
	return 0;
}

int jpc(struct Core* core)
{
	if(isSet(core->AF.F, bv(FLAG_C))) jp(core);
	return 0;
}

int pcHL(struct Core* core)
{
	core->PC = core->HL.val;
	return 0;
}

int cnz(struct Core* core)
{
	if(isClear(core->AF.F, bv(FLAG_Z))) call(core);
	return 0;
}

int cz(struct Core* core)
{
	if(isSet(core->AF.F, bv(FLAG_Z))) call(core);
	return 0;
}

int cnc(struct Core* core)
{
	if(isClear(core->AF.F, bv(FLAG_C))) call(core);
	return 0;
}

int cc(struct Core* core)
{
	if(isSet(core->AF.F, bv(FLAG_C))) call(core);
	return 0;
}

int rnz(struct Core* core)
{
	if(isClear(core->AF.F, bv(FLAG_Z))) ret(core);
	return 0;
}

int rz(struct Core* core)
{
	if(isSet(core->AF.F, bv(FLAG_Z))) ret(core);
	return 0;
}

int rnc(struct Core* core)
{
	if(isClear(core->AF.F, bv(FLAG_C))) ret(core);
	return 0;
}

int rc(struct Core* core)
{
	if(isSet(core->AF.F, bv(FLAG_C))) ret(core);
	return 0;
}