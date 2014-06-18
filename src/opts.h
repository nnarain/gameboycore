
#ifndef OPTS
#define OPTS

#define BIT0 0x01 
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

#define bv(x) 1<<x

#define set(x, y) x |= y
#define clear(x, y) x &= ~y

#define setbit(x,y) set(x, bv(y))
#define clearbit(x,y) clear(x, bv(y))

#define bitset(target,mask,val) target = (val) ? target | mask : target & ~mask

#endif // OPTS
