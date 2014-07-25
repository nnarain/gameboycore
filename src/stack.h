

#ifndef STACK
#define STACK

#include "gbcore.h"

int pushAF(GBCore*);
int pushBC(GBCore*);
int pushDE(GBCore*);
int pushHL(GBCore*);

int popAF(GBCore*);
int popBC(GBCore*);
int popDE(GBCore*);
int popHL(GBCore*);

#endif


