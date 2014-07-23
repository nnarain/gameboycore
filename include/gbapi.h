

#ifndef GB_API
#define GB_API

#ifdef __cplusplus
extern "C"{
#endif

#include "gbcore.h"
#include "gbparser.h"
#include "gboam.h"
#include "gbtile.h"
#include "gbmapregion.h"
#include "gbpalette.h"

#define EXECUTE_CYCLES 256

int execute(GBCore*, uint8_t);
void step(GBCore*);

void initCore(GBCore* core);
uint8_t* getAddress(GBCore*, uint16_t);

uint8_t readMem(GBCore, uint16_t);
void writeMem(GBCore, uint16_t);

void swap(GBCore*, int);

void releaseBanks(MBC*);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
