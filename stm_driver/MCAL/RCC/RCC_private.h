#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H




typedef enum{


	RCC_PRESCFACTOR_NOT_DIVID,
	RCC_PRESCFACTOR_2 ,
	RCC_PRESCFACTOR_4,
	RCC_PRESCFACTOR_8,
	RCC_PRESCFACTOR_16,
	RCC_PRESCFACTOR_64,
	RCC_PRESCFACTOR_128,
	RCC_PRESCFACTOR_256,
	RCC_PRESCFACTOR_512

}
RCC_PRESCFACTOR_ID ;


typedef enum {

		RCC_HSE,    // External clock source
		RCC_HSI,	// Internal clock source
		RCC_PLL		// Internal clock source with factor need HSE or HSI

			 }
RCC_CLK_SOURCE_ID;





typedef enum {

		RCC_AHB2 = 0,
		RCC_AHB1 = 32,
		RCC_APB2 = 64,
		RCC_APB1 = 96

			 }
RCC_Bus_ID;

typedef enum {


		RCC_USB_OTG_FS 						= RCC_AHB2 +  7,

		RCC_DMA2 							= RCC_AHB1 + 22,
		RCC_DMA1							= RCC_AHB1 + 21,
	//	RCC_Flash_interface 				= RCC_AHB1,
	//	RCC_RCC								= RCC_AHB1,
		RCC_CRC								= RCC_AHB1 + 12,
		RCC_GPIOH							= RCC_AHB1 +  7,
		RCC_GPIOE							= RCC_AHB1 +  4,
		RCC_GPIOD							= RCC_AHB1 +  3,
		RCC_GPIOC							= RCC_AHB1 +  2,
		RCC_GPIOB							= RCC_AHB1 +  1,
		RCC_GPIOA							= RCC_AHB1 +  0,

		RCC_TIM11 							= RCC_APB2 + 18,
		RCC_TIM10							= RCC_APB2 + 17,
		RCC_TIM9 							= RCC_APB2 + 16,
	//	RCC_EXTI 							= RCC_APB2 ,
		RCC_SYSCFG 							= RCC_APB2 + 14,
		RCC_SPI4 							= RCC_APB2 + 13,
		RCC_SPI1 							= RCC_APB2 + 12,
		RCC_SDIO 							= RCC_APB2 + 11,
		RCC_ADC1 							= RCC_APB2 +  8,
		RCC_USART6 							= RCC_APB2 +  5,
		RCC_USART1 							= RCC_APB2 +  4,
		RCC_TIM1 							= RCC_APB2 +  0,

		RCC_PWR 							= RCC_APB1 + 28,
		RCC_I2C3 							= RCC_APB1 + 23,
		RCC_I2C2 							= RCC_APB1 + 22,
		RCC_I2C1 							= RCC_APB1 + 21,
		RCC_USART2 							= RCC_APB1 + 17,
	//	RCC_I2S3ext 						= RCC_APB1,
		RCC_SPI3 							= RCC_APB1 + 15,
		RCC_SPI2							= RCC_APB1 + 14,
	//	RCC_I2S2ext 						= RCC_APB1,
	//	RCC_IWDG 							= RCC_APB1,
		RCC_WWDG 							= RCC_APB1 + 11,
	//	RCC_RTC 							= RCC_APB1,
		RCC_TIM5 							= RCC_APB1 +  3,
		RCC_TIM4 							= RCC_APB1 +  2,
		RCC_TIM3 							= RCC_APB1 +  1,
		RCC_TIM2 							= RCC_APB1 +  0,


			 }
RCC_Peripheral_ID;

typedef struct
{

    u32 RCC_CR;
    u32 RCC_PLLCFGR;
    u32 RCC_CFGR;
    u32 RCC_CIR;
    u32 RCC_AHB1RSTR;
    u32 RCC_AHB2RSTR;

    u32 Reserved0[2];

    u32 RCC_APB1RSTR;
    u32 RCC_APB2RSTR;

    u32 Reserved1[2];

    u32 RCC_AHB1ENR;
    u32 RCC_AHB2ENR;

    u32 Reserved2[2];

    u32 RCC_APB1ENR;
    u32 RCC_APB2ENR;

    u32 Reserved3[2];

    u32 RCC_AHB1LPENR;
    u32 RCC_AHB2LPENR;

    u32 Reserved4[2];

    u32 RCC_APB1LPENR;
    u32 RCC_APB2LPENR;

    u32 Reserved5[2];

    u32 RCC_BDCR;
    u32 RCC_CSR;

    u32 Reserved6[2];

    u32 RCC_SSCGR;
    u32 RCC_PLLI2SCFGR;

    u32 Reserved7;

    u32 RCC_DCKCFGR;

}RCC_ID;


#define RCC_REGS ((volatile RCC_ID*) 0x40023800)


#endif
