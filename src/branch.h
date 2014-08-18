

#ifndef BRANCH
#define BRANCH

#include "gbcore.h"
#include "nop.h"
#include "opts.h"

int call(GBCore*);
int rst00H(GBCore*);
int rst08H(GBCore*);
int rst10H(GBCore*);
int rst18H(GBCore*);
int rst20H(GBCore*);
int rst28H(GBCore*);
int rst30H(GBCore*);
int rst38H(GBCore*);

int ret(GBCore*);
int jp(GBCore*);

int jpnz(GBCore*);
int jpz(GBCore*);

int jpnc(GBCore*);
int jpc(GBCore*);

int pcHL(GBCore*);

int cnz(GBCore*);
int cz(GBCore*);

int cnc(GBCore*);
int cc(GBCore*);

int rnz(GBCore*);
int rz(GBCore*);

int rnc(GBCore*);
int rc(GBCore*);

int jr(GBCore*);
int jrnz(GBCore*);
int jrz(GBCore*);
int jrnc(GBCore*);
int jrc(GBCore*);

int halt(GBCore*);


#endif


