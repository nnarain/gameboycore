

#ifndef BRANCH
#define BRANCH

#include "gbcore.h"
#include "nop.h"
#include "opts.h"

int call(struct Core*);
int rst00H(struct Core*);
int rst08H(struct Core*);
int rst10H(struct Core*);
int rst18H(struct Core*);
int rst20H(struct Core*);
int rst28H(struct Core*);
int rst30H(struct Core*);
int rst38H(struct Core*);

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

int jr(struct Core*);
int jrnz(struct Core*);
int jrz(struct Core*);
int jrnc(struct Core*);
int jrc(struct Core*);

int halt(struct Core*);


#endif


