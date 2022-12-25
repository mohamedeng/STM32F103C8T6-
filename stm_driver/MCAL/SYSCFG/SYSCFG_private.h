/*
 * SYSCFG_private.h
 *
 *  Created on: Aug 29, 2022
 *      Author: hp
 */

#ifndef MCAL_SYSCFG_SYSCFG_PRIVATE_H_
#define MCAL_SYSCFG_SYSCFG_PRIVATE_H_

#include <stdlib.h>
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"



typedef struct {

	u32 SYSCFG_MEMRMP;
	u32 SYSCFG_PMC;
	u32 SYSCFG_EXTICR[4];
	u32 SYSCFG_CMPCR;


}SYSCFG_ID;


#define SYSCFG_REGS ((SYSCFG_ID*)(0x40013800))



#endif /* MCAL_SYSCFG_SYSCFG_PRIVATE_H_ */
