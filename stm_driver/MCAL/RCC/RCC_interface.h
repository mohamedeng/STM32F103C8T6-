#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H


#include <stdint.h>
#include "LIB/STM_CONFIG.h"
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/RCC/RCC_private.h"

u8 RCC_u8_INIT_SYSCLK(RCC_CLK_SOURCE_ID RCC_CLK_SOURCE);

void RCC_void_ENABLE_PERCLK(RCC_Peripheral_ID RCC_Peripheral);

void RCC_void_DISABLE_PERCLK(RCC_Peripheral_ID RCC_Peripheral);

void RCC_void_RESET_PER(RCC_Peripheral_ID RCC_Peripheral);


void RCC_void_PLL_CONFIG(u32 FREQ);


void RCC_void_BUS_PRESCFACTOR(RCC_Bus_ID RCC_Bus,RCC_PRESCFACTOR_ID RCC_PRESCFACTOR);




#endif
