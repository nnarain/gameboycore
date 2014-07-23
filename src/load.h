
#ifndef LOAD
#define LOAD

#include "gbcore.h"
#include "opts.h"

/* 8 bit */

void ldAA(GBCore*);
void ldAB(GBCore*);
void ldAC(GBCore*);
void ldAD(GBCore*);
void ldAE(GBCore*);
void ldAH(GBCore*);
void ldAL(GBCore*);
void ldAHL(GBCore*);
void ldABC(GBCore*);
void ldADE(GBCore*);
void ldAWord(GBCore*);
void ldBA(GBCore*);
void ldBB(GBCore*);
void ldBC(GBCore*);
void ldBD(GBCore*);
void ldBE(GBCore*);
void ldBH(GBCore*);
void ldBL(GBCore*);
void ldBHL(GBCore*);
void ldCA(GBCore*);
void ldCB(GBCore*);
void ldCC(GBCore*);
void ldCD(GBCore*);
void ldCE(GBCore*);
void ldCH(GBCore*);
void ldCL(GBCore*);
void ldCHL(GBCore*);
void ldDA(GBCore*);
void ldDB(GBCore*);
void ldDC(GBCore*);
void ldDD(GBCore*);
void ldDE(GBCore*);
void ldDH(GBCore*);
void ldDL(GBCore*);
void ldDHL(GBCore*);
void ldEA(GBCore*);
void ldEB(GBCore*);
void ldEC(GBCore*);
void ldED(GBCore*);
void ldEE(GBCore*);
void ldEH(GBCore*);
void ldEL(GBCore*);
void ldEHL(GBCore*);
void ldHA(GBCore*);
void ldHB(GBCore*);
void ldHC(GBCore*);
void ldHD(GBCore*);
void ldHE(GBCore*);
void ldHH(GBCore*);
void ldHL(GBCore*);
void ldHHL(GBCore*);
void ldLA(GBCore*);
void ldLB(GBCore*);
void ldLC(GBCore*);
void ldLD(GBCore*);
void ldLE(GBCore*);
void ldLH(GBCore*);
void ldLL(GBCore*);
void ldLHL(GBCore*);
void ldHLA(GBCore*);
void ldHLB(GBCore*);
void ldHLC(GBCore*);
void ldHLD(GBCore*);
void ldHLE(GBCore*);
void ldHLH(GBCore*);
void ldHLL(GBCore*);
void ldAByte(GBCore*);
void ldBByte(GBCore*);
void ldCByte(GBCore*);
void ldDByte(GBCore*);
void ldEByte(GBCore*);
void ldHByte(GBCore*);
void ldLByte(GBCore*);
void ldHLByte(GBCore*);

void ldBCA(GBCore*);
void ldDEA(GBCore*);
void ldAddrA(GBCore*);

/* 16 bit */

void ldBCWord(GBCore*);
void ldDEWord(GBCore*);
void ldHLWord(GBCore*);
void ldSPWord(GBCore*);

void ldHLAddr(GBCore*);
void ldBCAddr(GBCore*);
void ldDEAddr(GBCore*);

void ldAddrHL(GBCore*);

void ldSPHL(GBCore*);

#endif