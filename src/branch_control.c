

#include "branch_control.h"


int jp(struct Core* core)
{
	core->PC = getNextWord(&core->PC, core->mem);
	return 0;
}


