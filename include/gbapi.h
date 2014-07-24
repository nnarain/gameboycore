

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
#include "memopts.h"

#define EXECUTE_CYCLES 256

int execute(GBCore*, uint8_t);
void step(GBCore*);

void initCore(GBCore* core);

void releaseBanks(GBMemoryBankController*);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
