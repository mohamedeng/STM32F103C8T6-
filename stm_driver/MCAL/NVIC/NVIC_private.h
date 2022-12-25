/*
 * NVIC_private.h
 *
 *  Created on: Aug 27, 2022
 *      Author: hp
 */

#ifndef MCAL_NVIC_NVIC_PRIVATE_H_
#define MCAL_NVIC_NVIC_PRIVATE_H_

#include <stdlib.h>
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"


#define AIRCR *((u32*)(0xE000ED0C))
//#define NVIC_ISER 	((u32*)(0xE000E100))
#define NVIC_ISER1 *((u32*)(0xE000E100+0x04 * 1))
#define NVIC_ISER2 *((u32*)(0xE000E100+0x04 * 2))
#define NVIC_ISER3 *((u32*)(0xE000E100+0x04 * 3))
#define NVIC_ISER4 *((u32*)(0xE000E100+0x04 * 4))
#define NVIC_ISER5 *((u32*)(0xE000E100+0x04 * 5))
#define NVIC_ISER6 *((u32*)(0xE000E100+0x04 * 6))
#define NVIC_ISER7 *((u32*)(0xE000E100+0x04 * 7))


//#define NVIC_ICER 	((u32*)(0XE000E180))
#define NVIC_ICER1 *((u32*)(0XE000E180+0x04 * 1))
#define NVIC_ICER2 *((u32*)(0XE000E180+0x04 * 2))
#define NVIC_ICER3 *((u32*)(0XE000E180+0x04 * 3))
#define NVIC_ICER4 *((u32*)(0XE000E180+0x04 * 4))
#define NVIC_ICER5 *((u32*)(0XE000E180+0x04 * 5))
#define NVIC_ICER6 *((u32*)(0XE000E180+0x04 * 6))
#define NVIC_ICER7 *((u32*)(0XE000E180+0x04 * 7))


//#define NVIC_ISPR ((u32*)(0XE000E200))

//#define NVIC_ICPR ((u32*)(0XE000E280))

//#define NVIC_IABR ((u32*)(0xE000E300))

//#define NVIC_IPR ((u32*)(0xE000E400))

//#define STIR ((u32*)(0xE000EF00))

typedef struct
{
	u32	ISER[8];
	u32 Reserved0[97];

	u32 ICER[8];
	u32 Reserved1[97];

	u32 ISPR[8];
	u32 Reserved2[97];

	u32 ICPR[8];
	u32 Reserved3[97];

	u32 IABR[8];
	u32 Reserved4[255];

	u32 IPR[60];
	u32 Reserved5[2577];

	u32 STIR;

}NVIC_ID;

#define NVIC_REGS (( NVIC_ID*) 0xE000E100)




typedef enum {



	NVIC_WWDG_INT 				= 0,
	NVIC_PVD_INT 				= 1,
	NVIC_TAMP_STAMP_INT			= 2,
	NVIC_RTC_WKUP_INT			= 3,
	NVIC_FLASH_INT				= 4,
	NVIC_RCC_INT					= 5,
	NVIC_EXTI0_INT				= 6,
	NVIC_EXTI1_INT				= 7,
	NVIC_EXTI2_INT				= 8,
	NVIC_EXTI3_INT				= 9,
	NVIC_EXTI4_INT				= 10,
	NVIC_DMA1_Stream0_INT		= 11,
	NVIC_DMA1_Stream1_INT		= 12,
	NVIC_DMA1_Stream2_INT		= 13,
	NVIC_DMA1_Stream3_INT		= 14,
	NVIC_DMA1_Stream4_INT		= 15,
	NVIC_DMA1_Stream5_INT		= 16,
	NVIC_DMA1_Stream6_INT		= 17,
	NVIC_ADC_INT					= 18,
	NVIC_EXTI9_5_INT				= 23,
	NVIC_TIM1_BRK_TIM9_INT		= 24,
	NVIC_TIM1_UP_TIM10_INT		= 25,
	NVIC_TIM1_TRG_COM_TIM11_INT	= 26,
	NVIC_TIM1_CC_INT 			= 27,
	NVIC_TIM2_INT				= 28,
	NVIC_TIM3_INT				= 29,
	NVIC_TIM4_INT				= 30,
	NVIC_I2C1_EV_INT				= 31,
	NVIC_I2C1_ER_INT				= 32,
	NVIC_I2C2_EV_INT				= 33,
	NVIC_I2C2_ER_INT				= 34,
	NVIC_SPI1_INT				= 35,
	NVIC_SPI2_INT				= 36,
	NVIC_USART1_INT				= 37,
	NVIC_USART2_INT				= 38,
	NVIC_EXTI15_10_INT			= 40,
	NVIC_RTC_Alarm_INT			= 41,
	NVIC_OTG_FS_WKUP_INT			= 42,
	NVIC_DMA1_Stream7_INT		= 47,
	NVIC_SDIO_INT				= 49,
	NVIC_TIM5_INT				= 50,
	NVIC_SPI3_INT				= 51,
	NVIC_DMA2_Stream0_INT		= 56,
	NVIC_DMA2_Stream1_INT		= 57,
	NVIC_DMA2_Stream2_INT		= 58,
	NVIC_DMA2_Stream3_INT		= 59,
	NVIC_DMA2_Stream4_INT		= 60,
	NVIC_OTG_FS_INT 				= 67,
	NVIC_DMA2_Stream5_INT		= 68,
	NVIC_DMA2_Stream6_INT		= 69,
	NVIC_DMA2_Stream7_INT		= 70,
	NVIC_USART6_INT				= 71,
	NVIC_I2C3_EV_INT				= 72,
	NVIC_I2C3_ER_INT				= 73,
	NVIC_FPU_INT					= 81,
	NVIC_SPI4_INT				= 84,


}INT_Type;


#endif /* MCAL_NVIC_NVIC_PRIVATE_H_ */
