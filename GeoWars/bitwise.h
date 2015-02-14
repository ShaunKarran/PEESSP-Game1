// Information ----------------------------------------------------------------

/*	Library:		libTeensy20
 *	Purpose:		Bitwise macros
 *	Author(s):		Shaun Karran
 *	Created:		October 2014
*/

#ifndef _bitwise_h
#define _bitwise_h

// Macros ----------------------------------------------------------------

#define SET_BIT(reg, bit) 		(reg |= (1 << bit))
#define CLR_BIT(reg, bit) 		(reg &= ~(1 << bit))
#define TOG_BIT(reg, bit)		(reg ^= (1 << bit))
#define GET_BIT(reg, bit) 		(reg & (1 << bit))

#endif // _bitwise_h