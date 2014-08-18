
#ifndef LOAD
#define LOAD

#include "gbcore.h"
#include "opts.h"
#include "memopts.h"

/* 8 bit */

int ldAA(GBCore*);
int ldAB(GBCore*);
int ldAC(GBCore*);
int ldAD(GBCore*);
int ldAE(GBCore*);
int ldAH(GBCore*);
int ldAL(GBCore*);
int ldAHL(GBCore*);
int ldABC(GBCore*);
int ldADE(GBCore*);
int ldAWord(GBCore*);
int ldBA(GBCore*);
int ldBB(GBCore*);
int ldBC(GBCore*);
int ldBD(GBCore*);
int ldBE(GBCore*);
int ldBH(GBCore*);
int ldBL(GBCore*);
int ldBHL(GBCore*);
int ldCA(GBCore*);
int ldCB(GBCore*);
int ldCC(GBCore*);
int ldCD(GBCore*);
int ldCE(GBCore*);
int ldCH(GBCore*);
int ldCL(GBCore*);
int ldCHL(GBCore*);
int ldDA(GBCore*);
int ldDB(GBCore*);
int ldDC(GBCore*);
int ldDD(GBCore*);
int ldDE(GBCore*);
int ldDH(GBCore*);
int ldDL(GBCore*);
int ldDHL(GBCore*);
int ldEA(GBCore*);
int ldEB(GBCore*);
int ldEC(GBCore*);
int ldED(GBCore*);
int ldEE(GBCore*);
int ldEH(GBCore*);
int ldEL(GBCore*);
int ldEHL(GBCore*);
int ldHA(GBCore*);
int ldHB(GBCore*);
int ldHC(GBCore*);
int ldHD(GBCore*);
int ldHE(GBCore*);
int ldHH(GBCore*);
int ldHL(GBCore*);
int ldHHL(GBCore*);
int ldLA(GBCore*);
int ldLB(GBCore*);
int ldLC(GBCore*);
int ldLD(GBCore*);
int ldLE(GBCore*);
int ldLH(GBCore*);
int ldLL(GBCore*);
int ldLHL(GBCore*);
int ldHLA(GBCore*);
int ldHLB(GBCore*);
int ldHLC(GBCore*);
int ldHLD(GBCore*);
int ldHLE(GBCore*);
int ldHLH(GBCore*);
int ldHLL(GBCore*);
int ldAByte(GBCore*);
int ldBByte(GBCore*);
int ldCByte(GBCore*);
int ldDByte(GBCore*);
int ldEByte(GBCore*);
int ldHByte(GBCore*);
int ldLByte(GBCore*);
int ldHLByte(GBCore*);

int ldBCA(GBCore*);
int ldDEA(GBCore*);
int ldAddrA(GBCore*);

/* 16 bit */

int ldBCWord(GBCore*);
int ldDEWord(GBCore*);
int ldHLWord(GBCore*);
int ldSPWord(GBCore*);

int ldHLAddr(GBCore*);
int ldBCAddr(GBCore*);
int ldDEAddr(GBCore*);

int ldAddrHL(GBCore*);

int ldSPHL(GBCore*);

#endif