

#ifndef BRANCH
#define BRANCH

#include "gbcore.h"
#include "opts.h"

int call(struct Core*);
int ret(struct Core*);
int jp(struct Core*);

int jpnz(struct Core*);
int jpz(struct Core*);

int jpnc(struct Core*);
int jpc(struct Core*);

int pcHL(struct Core*);

int cnz(struct Core*);
int cz(struct Core*);

int cnc(struct Core*);
int cc(struct Core*);

int rnz(struct Core*);
int rz(struct Core*);

int rnc(struct Core*);
int rc(struct Core*);

#endif


