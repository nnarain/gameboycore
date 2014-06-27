
#ifndef LOGIC
#define LOGIC

#include "gbcore.h"

int AandA(struct Core*);
int AandB(struct Core*);
int AandC(struct Core*);
int AandD(struct Core*);
int AandE(struct Core*);
int AandH(struct Core*);
int AandL(struct Core*);

int Aand_HL_(struct Core*);

int AandByte(struct Core*);

int AxorA(struct Core*);
int AxorB(struct Core*);
int AxorC(struct Core*);
int AxorD(struct Core*);
int AxorE(struct Core*);
int AxorH(struct Core*);
int AxorL(struct Core*);
int Axor_HL_(struct Core*);
int AxorByte(struct Core*);

int AorA(struct Core*);
int AorB(struct Core*);
int AorC(struct Core*);
int AorD(struct Core*);
int AorE(struct Core*);
int AorH(struct Core*);
int AorL(struct Core*);
int Aor_HL_(struct Core*);
int AorByte(struct Core*);

#endif
