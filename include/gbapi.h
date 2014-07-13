

#ifndef GB_API
#define GB_API

#include "gbcore.h"
#include "gbparser.h"

int execute(struct Core*, uint8_t);
void step(struct Core*);

void initCore(struct Core* core);
uint8_t* getAddress(struct Core*, uint16_t);

void releaseBanks(struct MBC*);

#endif
