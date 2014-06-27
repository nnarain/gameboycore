

#ifndef GB_API
#define GB_API

#include "gbcore.h"
#include "gbparser.h"

int execute(struct Core*, uint8_t);

void initCore(struct Core* core);
uint8_t* getAddress(struct Core*, uint16_t);

void initBanks(struct Core* core, int nBanks);
void loadBanks(struct Core*, uint8_t**, int);

void releaseCore(struct Core* core);

#endif
