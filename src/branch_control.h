

#ifndef BRANCH_CONTROL
#define BRANCH_CONTROL

#include "gbcore.h"
#include "opts.h"


int jp(struct Core*);

int jpNZ(struct Core*);
int jpZ(struct Core*);
int jpNC(struct Core*);
int jpC(struct Core*);

#endif

