

#ifndef MEMOPTS
#define MEMOPTS

uint8_t* getAddress(GBCore*, uint16_t);

uint8_t readMem(GBCore*, uint16_t);
void writeMem(GBCore*, uint16_t, uint8_t);

#endif