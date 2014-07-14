

#include "rotate.h"


int rlca(struct Core* core)
{
	_rlc(core->AF.F, core->AF.A);
	return 0;
}

int rrca(struct Core* core)
{
	_rrc(core->AF.F, core->AF.A);
	return 0;
}

int rla(struct Core* core)
{
	_rlc0(core->AF.F, core->AF.A);
	return 0;
}

int rra(struct Core* core)
{
	_rrc0(core->AF.F, core->AF.A);
	return 0;
}


int rlcb(struct Core* core)
{
	_rlc(core->AF.F, core->BC.B);
	return 0;
}

int rlcc(struct Core* core)
{
	_rlc(core->AF.F, core->BC.C);
	return 0;
}

int rlcd(struct Core* core)
{
	_rlc(core->AF.F, core->DE.D);
	return 0;
}

int rlce(struct Core* core)
{
	_rlc(core->AF.F, core->DE.E);
	return 0;
}

int rlch(struct Core* core)
{
	_rlc(core->AF.F, core->HL.H);
	return 0;
}

int rlcl(struct Core* core)
{
	_rlc(core->AF.F, core->HL.L);
	return 0;
}

int rlchl(struct Core* core)
{
	_rlc(core->AF.F, core->mem[core->HL.val]);
	return 0;
}

int rrcb(struct Core* core)
{
	_rrc(core->AF.F, core->BC.B);
	return 0;
}
int rrcc(struct Core* core)
{
	_rrc(core->AF.F, core->BC.C);
	return 0;
}
int rrcd(struct Core* core)
{
	_rrc(core->AF.F, core->DE.D);
	return 0;
}
int rrce(struct Core* core)
{
	_rrc(core->AF.F, core->DE.E);
	return 0;
}
int rrch(struct Core* core)
{
	_rrc(core->AF.F, core->HL.H);
	return 0;
}
int rrcl(struct Core* core)
{
	_rrc(core->AF.F, core->HL.L);
	return 0;
}

int rrchl(struct Core* core)
{
	_rrc(core->AF.F, core->mem[core->HL.val]);
	return 0;
}

int rlb(struct Core* core)
{
	_rlc0(core->AF.F, core->BC.B);
	return 0;
}

int rlc(struct Core* core)
{
	_rlc0(core->AF.F, core->BC.C);
	return 0;
}

int rld(struct Core* core)
{
	_rlc0(core->AF.F, core->DE.D);
	return 0;
}

int rle(struct Core* core)
{
	_rlc0(core->AF.F, core->DE.E);
	return 0;
}

int rlh(struct Core* core)
{
	_rlc0(core->AF.F, core->HL.H);
	return 0;
}

int rll(struct Core* core)
{
	_rlc0(core->AF.F, core->HL.L);
	return 0;
}

int rlhl(struct Core* core)
{
	_rlc0(core->AF.F, core->mem[core->HL.val]);
	return 0;
}


int rrb(struct Core* core)
{
	_rrc0(core->AF.F, core->BC.B);
	return 0;
}

int rrc(struct Core* core)
{
	_rlc0(core->AF.F, core->BC.C);
	return 0;
}

int rrd(struct Core* core)
{
	_rlc0(core->AF.F, core->DE.D);
	return 0;
}

int rre(struct Core* core)
{
	_rlc0(core->AF.F, core->DE.E);
	return 0;
}

int rrh(struct Core* core)
{
	_rlc0(core->AF.F, core->HL.H);
	return 0;
}

int rrl(struct Core* core)
{
	_rlc0(core->AF.F, core->HL.L);
	return 0;
}

int rrhl(struct Core* core)
{
	_rlc0(core->AF.F, core->mem[core->HL.val]);
	return 0;
}