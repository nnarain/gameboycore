

#ifndef BRANCH
#define BRANCH

#include "gbcore.h"
#include "nop.h"
#include "opts.h"

void call(GBCore*);
void rst00H(GBCore*);
void rst08H(GBCore*);
void rst10H(GBCore*);
void rst18H(GBCore*);
void rst20H(GBCore*);
void rst28H(GBCore*);
void rst30H(GBCore*);
void rst38H(GBCore*);

void ret(GBCore*);
void jp(GBCore*);

void jpnz(GBCore*);
void jpz(GBCore*);

void jpnc(GBCore*);
void jpc(GBCore*);

void pcHL(GBCore*);

void cnz(GBCore*);
void cz(GBCore*);

void cnc(GBCore*);
void cc(GBCore*);

void rnz(GBCore*);
void rz(GBCore*);

void rnc(GBCore*);
void rc(GBCore*);

void jr(GBCore*);
void jrnz(GBCore*);
void jrz(GBCore*);
void jrnc(GBCore*);
void jrc(GBCore*);

void halt(GBCore*);


#endif


