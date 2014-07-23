

#include "rotate.h"


void rlca(GBCore* core)
{
	_rlc(core->AF.F, core->AF.A);
	
}

void rrca(GBCore* core)
{
	_rrc(core->AF.F, core->AF.A);
	
}

void rla(GBCore* core)
{
	_rlc0(core->AF.F, core->AF.A);
	
}

void rra(GBCore* core)
{
	_rrc0(core->AF.F, core->AF.A);
	
}


void rlcb(GBCore* core)
{
	_rlc(core->AF.F, core->BC.B);
	
}

void rlcc(GBCore* core)
{
	_rlc(core->AF.F, core->BC.C);
	
}

void rlcd(GBCore* core)
{
	_rlc(core->AF.F, core->DE.D);
	
}

void rlce(GBCore* core)
{
	_rlc(core->AF.F, core->DE.E);
	
}

void rlch(GBCore* core)
{
	_rlc(core->AF.F, core->HL.H);
	
}

void rlcl(GBCore* core)
{
	_rlc(core->AF.F, core->HL.L);
	
}

void rlchl(GBCore* core)
{
	_rlc(core->AF.F, core->mem[core->HL.val]);
	
}

void rrcb(GBCore* core)
{
	_rrc(core->AF.F, core->BC.B);
	
}
void rrcc(GBCore* core)
{
	_rrc(core->AF.F, core->BC.C);
	
}
void rrcd(GBCore* core)
{
	_rrc(core->AF.F, core->DE.D);
	
}
void rrce(GBCore* core)
{
	_rrc(core->AF.F, core->DE.E);
	
}
void rrch(GBCore* core)
{
	_rrc(core->AF.F, core->HL.H);
	
}
void rrcl(GBCore* core)
{
	_rrc(core->AF.F, core->HL.L);
	
}

void rrchl(GBCore* core)
{
	_rrc(core->AF.F, core->mem[core->HL.val]);
	
}

void rlb(GBCore* core)
{
	_rlc0(core->AF.F, core->BC.B);
	
}

void rlc(GBCore* core)
{
	_rlc0(core->AF.F, core->BC.C);
	
}

void rld(GBCore* core)
{
	_rlc0(core->AF.F, core->DE.D);
	
}

void rle(GBCore* core)
{
	_rlc0(core->AF.F, core->DE.E);
	
}

void rlh(GBCore* core)
{
	_rlc0(core->AF.F, core->HL.H);
	
}

void rll(GBCore* core)
{
	_rlc0(core->AF.F, core->HL.L);
	
}

void rlhl(GBCore* core)
{
	_rlc0(core->AF.F, core->mem[core->HL.val]);
	
}


void rrb(GBCore* core)
{
	_rrc0(core->AF.F, core->BC.B);
	
}

void rrc(GBCore* core)
{
	_rlc0(core->AF.F, core->BC.C);
	
}

void rrd(GBCore* core)
{
	_rlc0(core->AF.F, core->DE.D);
	
}

void rre(GBCore* core)
{
	_rlc0(core->AF.F, core->DE.E);
	
}

void rrh(GBCore* core)
{
	_rlc0(core->AF.F, core->HL.H);
	
}

void rrl(GBCore* core)
{
	_rlc0(core->AF.F, core->HL.L);
	
}

void rrhl(GBCore* core)
{
	_rlc0(core->AF.F, core->mem[core->HL.val]);
	
}