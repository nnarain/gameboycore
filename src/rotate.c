

#include "rotate.h"


int rlca(GBCore* core)
{
	_rlc(core->AF.F, core->AF.A);
	return 1;	
}

int rrca(GBCore* core)
{
	_rrc(core->AF.F, core->AF.A);
	return 1;	
}

int rla(GBCore* core)
{
	_rlc0(core->AF.F, core->AF.A);
	return 1;	
}

int rra(GBCore* core)
{
	_rrc0(core->AF.F, core->AF.A);
	return 1;	
}


int rlcb(GBCore* core)
{
	_rlc(core->AF.F, core->BC.B);
	return 1;	
}

int rlcc(GBCore* core)
{
	_rlc(core->AF.F, core->BC.C);
	return 1;	
}

int rlcd(GBCore* core)
{
	_rlc(core->AF.F, core->DE.D);
	return 1;	
}

int rlce(GBCore* core)
{
	_rlc(core->AF.F, core->DE.E);
	return 1;	
}

int rlch(GBCore* core)
{
	_rlc(core->AF.F, core->HL.H);
	return 1;	
}

int rlcl(GBCore* core)
{
	_rlc(core->AF.F, core->HL.L);
	return 1;	
}

int rlchl(GBCore* core)
{
	_rlc(core->AF.F, core->mem[core->HL.val]);
	return 1;	
}

int rrcb(GBCore* core)
{
	_rrc(core->AF.F, core->BC.B);
	return 1;	
}
int rrcc(GBCore* core)
{
	_rrc(core->AF.F, core->BC.C);
	return 1;	
}
int rrcd(GBCore* core)
{
	_rrc(core->AF.F, core->DE.D);
	return 1;	
}
int rrce(GBCore* core)
{
	_rrc(core->AF.F, core->DE.E);
	return 1;	
}
int rrch(GBCore* core)
{
	_rrc(core->AF.F, core->HL.H);
	return 1;	
}
int rrcl(GBCore* core)
{
	_rrc(core->AF.F, core->HL.L);
	return 1;	
}

int rrchl(GBCore* core)
{
	_rrc(core->AF.F, core->mem[core->HL.val]);
	return 1;	
}

int rlb(GBCore* core)
{
	_rlc0(core->AF.F, core->BC.B);
	return 1;	
}

int rlc(GBCore* core)
{
	_rlc0(core->AF.F, core->BC.C);
	return 1;	
}

int rld(GBCore* core)
{
	_rlc0(core->AF.F, core->DE.D);
	return 1;	
}

int rle(GBCore* core)
{
	_rlc0(core->AF.F, core->DE.E);
	return 1;	
}

int rlh(GBCore* core)
{
	_rlc0(core->AF.F, core->HL.H);
	return 1;	
}

int rll(GBCore* core)
{
	_rlc0(core->AF.F, core->HL.L);
	return 1;	
}

int rlhl(GBCore* core)
{
	_rlc0(core->AF.F, core->mem[core->HL.val]);
	return 1;	
}


int rrb(GBCore* core)
{
	_rrc0(core->AF.F, core->BC.B);
	return 1;	
}

int rrc(GBCore* core)
{
	_rlc0(core->AF.F, core->BC.C);
	return 1;	
}

int rrd(GBCore* core)
{
	_rlc0(core->AF.F, core->DE.D);
	return 1;	
}

int rre(GBCore* core)
{
	_rlc0(core->AF.F, core->DE.E);
	return 1;	
}

int rrh(GBCore* core)
{
	_rlc0(core->AF.F, core->HL.H);
	return 1;	
}

int rrl(GBCore* core)
{
	_rlc0(core->AF.F, core->HL.L);
	return 1;	
}

int rrhl(GBCore* core)
{
	_rlc0(core->AF.F, core->mem[core->HL.val]);
	return 1;	
}