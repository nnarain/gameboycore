

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

int execute(struct Core*, uint8_t);
void step(struct Core*);

void initCore(struct Core* core);
uint8_t* getAddress(struct Core*, uint16_t);

void swap(struct Core*, int);

void releaseBanks(struct MBC*);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
