
#ifndef LOGIC
#define LOGIC

#include "gbcore.h"
#include "opts.h"

int AandA(GBCore*);
int AandB(GBCore*);
int AandC(GBCore*);
int AandD(GBCore*);
int AandE(GBCore*);
int AandH(GBCore*);
int AandL(GBCore*);

int Aand_HL_(GBCore*);

int AandByte(GBCore*);

int AxorA(GBCore*);
int AxorB(GBCore*);
int AxorC(GBCore*);
int AxorD(GBCore*);
int AxorE(GBCore*);
int AxorH(GBCore*);
int AxorL(GBCore*);
int Axor_HL_(GBCore*);
int AxorByte(GBCore*);

int AorA(GBCore*);
int AorB(GBCore*);
int AorC(GBCore*);
int AorD(GBCore*);
int AorE(GBCore*);
int AorH(GBCore*);
int AorL(GBCore*);
int Aor_HL_(GBCore*);
int AorByte(GBCore*);

#endif
