

#ifndef STACK
#define STACK

#include "gbcore.h"

int pushAF(struct Core*);
int pushBC(struct Core*);
int pushDE(struct Core*);
int pushHL(struct Core*);

int popAF(struct Core*);
int popBC(struct Core*);
int popDE(struct Core*);
int popHL(struct Core*);

#endif


