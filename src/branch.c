
#include "branch.h"


void call(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 3) >> 8;
	core->mem[core->SP-2] = (core->PC + 3) & 0x0F;
	core->SP -= 2;

	core->PC = getNextWord(&core->PC, core->mem);

}

void rst00H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0;

}

void rst08H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x08;

}

void rst10H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x10;

}

void rst18H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x18;

}

void rst20H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x20;

}

void rst28H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x28;

}

void rst30H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x30;

}

void rst38H(GBCore* core)
{
	core->mem[core->SP-1] = (core->PC + 1) >> 8;
	core->mem[core->SP-2] = (core->PC + 1) & 0x0F;
	core->SP -= 2;

	core->PC = 0x38;

}

void ret(GBCore* core)
{
	core->PC = bytecat(core->mem[core->SP+1], core->mem[core->SP]);
	core->SP += 2;
}

void jp(GBCore* core)
{
#ifdef DEBUG
	printf("\njmp\n");
#endif
	core->PC = getNextWord(&core->PC, core->mem);
}

void jpnz(GBCore* core)
{
	if(isClear(core->AF.F, bv(FLAG_Z))) jp(core);
}

void jpz(GBCore* core)
{
	if(isSet(core->AF.F, bv(FLAG_Z))) jp(core);
}

void jpnc(GBCore* core)
{
	if(isClear(core->AF.F, bv(FLAG_C))) jp(core);
}

void jpc(GBCore* core)
{
	if(isSet(core->AF.F, bv(FLAG_C))) jp(core);
}

void pcHL(GBCore* core)
{
	core->PC = core->HL.val;
}

void cnz(GBCore* core)
{
	if(isClear(core->AF.F, bv(FLAG_Z))) call(core);
}

void cz(GBCore* core)
{
	if(isSet(core->AF.F, bv(FLAG_Z))) call(core);
}

void cnc(GBCore* core)
{
	if(isClear(core->AF.F, bv(FLAG_C))) call(core);
}

void cc(GBCore* core)
{
	if(isSet(core->AF.F, bv(FLAG_C))) call(core);
}

void rnz(GBCore* core)
{
	if(isClear(core->AF.F, bv(FLAG_Z))) ret(core);
}

void rz(GBCore* core)
{
	if(isSet(core->AF.F, bv(FLAG_Z))) ret(core);
}

void rnc(GBCore* core)
{
	if(isClear(core->AF.F, bv(FLAG_C))) ret(core);
}

void rc(GBCore* core)
{
	if(isSet(core->AF.F, bv(FLAG_C))) ret(core);
}

void jr(GBCore* core)
{
	signed char idx = core->mem[++core->PC];
	core->PC += idx;
}

void jrnz(GBCore* core)
{
	if( isClear(core->AF.F, bv(FLAG_Z)) ) jr(core);
	else core->PC += 2;
}

void jrz(GBCore* core)
{
	if( isSet(core->AF.F, bv(FLAG_Z)) ) jr(core);
	else core->PC += 2;
}

void jrnc(GBCore* core)
{
	if( isClear(core->AF.F, bv(FLAG_C)) ) jr(core);
	else core->PC += 2;
}

void jrc(GBCore* core)
{
	if( isSet(core->AF.F, bv(FLAG_C)) ) jr(core);
	else core->PC += 2;
}

void halt(GBCore* core)
{
	NOP(core);
	core->PC--;
}