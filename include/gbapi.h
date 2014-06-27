

#ifndef GB_API
#define GB_API

#include "gbcore.h"

void initCore(struct Core* core);
uint8_t* getAddress(struct Core*, uint16_t);

int execute(struct Core*, uint8_t);

#endif
