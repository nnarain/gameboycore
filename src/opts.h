
#ifndef OPTS
#define OPTS

#define bv(x) 1<<x

#define set(x, y) x |= y
#define clear(x, y) x &= ~y

#define setbit(x,y) set(x, bv(y))
#define clearbit(x,y) clear(x, bv(y))

#endif // OPTS
