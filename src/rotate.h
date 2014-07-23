
#ifndef ROTATE
#define ROTATE

#include "gbcore.h"

#define _rl(x) (x << 1) | ( (x & 0x80) >> 0x07 ) ///< Rotate left
#define _rr(x) (x >> 1) | ( (x & 0x01) << 0x07 ) ///< Rotate right

#define _rlc(f,x) \
	f |= ( (x & 0x80) >> (7 - FLAG_C) ); \
	x = _rl(x)

#define _rrc(f,x) \
	f |= ( (x & 0x01) << FLAG_C ); \
	x = _rr(x)

#define _rlc0(f,x) \
	uint8_t y = (f & 1<<FLAG_C) >> FLAG_C; \
	_rlc(f,x); \
	x &= y

#define _rrc0(f,x) \
	uint8_t y = (f & 1<<FLAG_C) << (7-FLAG_C); \
	_rrc(f,x); \
	x &= y




void rlca(GBCore*);
void rrca(GBCore*);
void rla(GBCore*);
void rra(GBCore*);

void rlcb(GBCore*);
void rlcc(GBCore*);
void rlcd(GBCore*);
void rlce(GBCore*);
void rlch(GBCore*);
void rlcl(GBCore*);
void rlchl(GBCore* core);

void rrcb(GBCore*);
void rrcc(GBCore*);
void rrcd(GBCore*);
void rrce(GBCore*);
void rrch(GBCore*);
void rrcl(GBCore*);
void rrchl(GBCore*);

void rlb(GBCore*);
void rlc(GBCore*);
void rld(GBCore*);
void rle(GBCore*);
void rlh(GBCore*);
void rll(GBCore*);
void rlhl(GBCore*);

void rrb(GBCore*);
void rrc(GBCore*);
void rrd(GBCore*);
void rre(GBCore*);
void rrh(GBCore*);
void rrl(GBCore*);
void rrhl(GBCore*);

#endif

