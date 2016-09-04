
/**
	Bit operation macros

	@author Natesh Narain
*/

#ifndef BITUTIL_H
#define BITUTIL_H

//! Bit value
#define BV(b) (1 << b)

//! set mask y in x
#define SET(x, y) ((x) |= (y))
//! clear mask y in x
#define CLR(x, y) ((x) &= (~y)) // TODO : Possible loss of precision - when using uint
//! toggle mask y in x
#define TGL(x, y) ((x) ^= (y))

//! set bit y in x
#define SET_BIT(x, y) ( SET( x, BV(y) ) )
//! clear bit y in x
#define CLR_BIT(x, y) ( CLR( x, BV(y) ) )
//! toggle bit y in x
#define TGL_BIT(x, y) ( TGL( x, BV(y) ) )

//!
#define LOW(x) ( (x) & 0x0F)

//!
#define FORCE(port, mask, value) ( (port) = ( (port) & (~(mask))) | ( (value) & (mask) ) )
//!
#define FORCE_WORD(port, mask, value) ( (port) = ( (port) & (~(mask) & 0xFFFF) | ( (value) & (mask) ) ) )

//! check if mask y is set in x
#define IS_SET(x, y) ( x & y )
//! check if mask y is clear in x
#define IS_CLR(x, y) !( x & y )
//! check if bit y is set in x
#define IS_BIT_SET(x,y) ( IS_SET(x, BV(y)) )
//! check if bit y is clear in x
#define IS_BIT_CLR(x,y) ( IS_CLR(x, BV(y)) )

//!
#define LOW_NYB(x) ((x) & 0x0F)
//!
#define HIGH_NYB(x) ( LOW_NYB((x) >> 4) )

/* Bit pattern concatenation macros  */

#define BIT_CAT(x, y, bits) ((x<<bits) + y)
#define NYB_CAT(x, y)       ( BIT_CAT(x, y, 4) )
#define BYTE_CAT(x,y)       ( BIT_CAT(x, y, 8) )
#define WORD_CAT(x,y)       ( BIT_CAT(x, y, 16) )

/* Full and Half Carry */

#define IS_HALF_CARRY(x, y) ((( ((x) & 0x0F) + ((y) & 0x0F) ) & (0x10)) != 0)

//!
#define EXPAND_PORT(port)( *(volatile word * const) &(port) )

#endif // BITUTIL_H









