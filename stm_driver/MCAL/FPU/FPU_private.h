/*
 * FPU_private.h
 *
 *  Created on: Aug 27, 2022
 *      Author: mohamed mahmoud abdo
 */

#ifndef MCAL_FPU_FPU_PRIVATE_H_
#define MCAL_FPU_FPU_PRIVATE_H_

#include "LIB/STM_CONFIG.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"



typedef struct


{

	u32 CPACR;

}
FPU_ID;


#define FPU ((FPU_ID*)(0xE000ED88))


#endif /* MCAL_FPU_FPU_PRIVATE_H_ */
