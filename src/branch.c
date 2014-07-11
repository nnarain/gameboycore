
#include "branch.h"


int call(struct Core* core)
{
	core->mem[core->SP-1] = core->PC >> 8;
	core->mem[core-SP-2] = core->PC & 0x0F;
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