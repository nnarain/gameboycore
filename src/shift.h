
#ifndef SHIFT
#define SHIFT

#include "gbcore.h"
#include "opts.h"

int slaA(struct Core*);
int slaB(struct Core*);
int slaC(struct Core*);
int slaD(struct Core*);
int slaE(struct Core*);
int slaH(struct Core*);
int slaL(struct Core*);
int sla_HL_(struct Core*);

int sraA(struct Core*);
int sraB(struct Core*);
int sraC(struct Core*);
int sraD(struct Core*);
int sraE(struct Core*);
int sraH(struct Core*);
int sraL(struct Core*);
int sra_HL_(struct Core*);

int srlA(struct Core*);
int srlB(struct Core*);
int srlC(struct Core*);
int srlD(struct Core*);
int srlE(struct Core*);
int srlH(struct Core*);
int srlL(struct Core*);
int srl_HL_(struct Core*);

#endif


