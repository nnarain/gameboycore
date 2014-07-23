

#ifndef STACK
#define STACK

#include "gbcore.h"

void pushAF(GBCore*);
void pushBC(GBCore*);
void pushDE(GBCore*);
void pushHL(GBCore*);

void popAF(GBCore*);
void popBC(GBCore*);
void popDE(GBCore*);
void popHL(GBCore*);

#endif


