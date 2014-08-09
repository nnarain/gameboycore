
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




int rlca(GBCore*);
int rrca(GBCore*);
int rla(GBCore*);
int rra(GBCore*);

int rlcb(GBCore*);
int rlcc(GBCore*);
int rlcd(GBCore*);
int rlce(GBCore*);
int rlch(GBCore*);
int rlcl(GBCore*);
int rlchl(GBCore* core);

int rrcb(GBCore*);
int rrcc(GBCore*);
int rrcd(GBCore*);
int rrce(GBCore*);
int rrch(GBCore*);
int rrcl(GBCore*);
int rrchl(GBCore*);

int rlb(GBCore*);
int rlc(GBCore*);
int rld(GBCore*);
int rle(GBCore*);
int rlh(GBCore*);
int rll(GBCore*);
int rlhl(GBCore*);

int rrb(GBCore*);
int rrc(GBCore*);
int rrd(GBCore*);
int rre(GBCore*);
int rrh(GBCore*);
int rrl(GBCore*);
int rrhl(GBCore*);

#endif

