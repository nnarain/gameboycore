
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




int rlca(struct Core*);
int rrca(struct Core*);
int rla(struct Core*);
int rra(struct Core*);

int rlcb(struct Core*);
int rlcc(struct Core*);
int rlcd(struct Core*);
int rlce(struct Core*);
int rlch(struct Core*);
int rlcl(struct Core*);

int rrcb(struct Core*);
int rrcc(struct Core*);
int rrcd(struct Core*);
int rrce(struct Core*);
int rrch(struct Core*);
int rrcl(struct Core*);

int rlb(struct Core*);
int rlc(struct Core*);
int rld(struct Core*);
int rle(struct Core*);
int rlh(struct Core*);
int rll(struct Core*);

int rrb(struct Core*);
int rrc(struct Core*);
int rrd(struct Core*);
int rre(struct Core*);
int rrh(struct Core*);
int rrl(struct Core*);

#endif

