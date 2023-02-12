/**
 * dec :
 * An nikname for variable types for easy use
 *
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <stdlib.h>


//#define NULL (void *)0

typedef enum {FALSE,TRUE} Bool;

typedef enum {

	u8_Type ,u16_Type,u32_Type ,
	u64_Type,s8_Type ,s16_Type ,
	s32_Type,s64_Type ,f32_Type ,
	d64_Type

}Types;



typedef unsigned char          u8;
typedef unsigned short int     u16;
typedef unsigned long int      u32;
typedef unsigned long long int u64;

typedef char s8;
typedef short int s16;
typedef long int s32;
typedef long long int s64;

typedef float f32;
typedef double d64;


#endif
