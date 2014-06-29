
#ifndef OPTS
#define OPTS

#include <stdint.h>

#define BIT0 0x01 
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

#define NIB  4  ///< Bits in a nibble
#define BYTE 8  ///< Bits in a byte
#define WORD 16 ///< Bits in a word

#define bv(x) 1<<x

#define set(x, y) x |= y
#define clear(x, y) x &= ~y

#define setbit(x,y) set(x, bv(y))
#define clearbit(x,y) clear(x, bv(y))

#define bitset(target,mask,val) target = (val) ? target | mask : target & ~mask

/* Concatenate bit pattern macros */

#define bitcat(x, y, bits) (x<<bits) + y 	   ///< Concatenate 2 bit patterns (i.e. 00001111, 00001111 = 111100001111)
#define nibcat(x, y) bitcat(x,y,NIB)     	   ///< Concatenate 2 nibbles
#define bytecat(x, y) bitcat(x,y,BYTE)   	   ///< Concatenate 2 bytes (i.e. 0x08, 0x01 = 0x0801)
#define wordcat(x, y) bitcat(x,y,WORD)   	   ///< Concatenate 2 words

/* Carry macros */

#define halfcarry(x,y) ( (x & 0x0F) + (y & 0x0F) ) & BIT4 ///< Determines half carry
#define fullcarry(x,y) ( x + y ) & 0x100

/* helper functions prototypes */

inline uint16_t getNextWord(uint16_t* PC, uint8_t mem[]);

#endif // OPTS
