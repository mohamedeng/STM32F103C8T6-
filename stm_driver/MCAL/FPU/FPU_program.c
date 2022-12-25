/*
 * FPU_program.c
 *
 *  Created on: Aug 27, 2022
 *      Author: mohamed mahmoud abdo
 */

#include "FPU_interface.h"



void FPU_void_ENABLE()
{

	FPU->CPACR |= (3<<20) | (3<<22);

}
