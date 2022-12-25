/*
 *
 *
 *
 *
 *
 */
#include "LIB/STM_CONFIG.h"
#include "RCC_interface.h"


u8 RCC_u8_INIT_SYSCLK(RCC_CLK_SOURCE_ID RCC_CLK_SOURCE)
{
	//RCC_REGS->RCC_CFGR = 0;
	switch (RCC_CLK_SOURCE)
	{

		case RCC_HSE:
			CLR_BIT(RCC_REGS->RCC_CFGR,1);

			SET_BIT(RCC_REGS->RCC_CR,16);

			while(GET_BIT(RCC_REGS->RCC_CR,17) == 0);
			SET_BIT(RCC_REGS->RCC_CFGR,0);
			CLR_BIT(RCC_REGS->RCC_CFGR,1);

			break;


		case RCC_HSI:

			SET_BIT(RCC_REGS->RCC_CR,0);
			while(GET_BIT(RCC_REGS->RCC_CR,1) == 0);
			CLR_BIT(RCC_REGS->RCC_CFGR,0);
			CLR_BIT(RCC_REGS->RCC_CFGR,1);
			break;


		case RCC_PLL:

			SET_BIT(RCC_REGS->RCC_CR,24);
			while(GET_BIT(RCC_REGS->RCC_CR,25) == 0);
			CLR_BIT(RCC_REGS->RCC_CFGR,0);
			SET_BIT(RCC_REGS->RCC_CFGR,1);
			break;


	}
	u8 Lstate = GET_BIT(RCC_REGS->RCC_CFGR,2) | (GET_BIT(RCC_REGS->RCC_CFGR,3)<<1);

	return Lstate;



}

void RCC_void_ENABLE_PERCLK(RCC_Peripheral_ID RCC_Peripheral)
{

	if(RCC_Peripheral < 32) 								// RCC_AHB2

		SET_BIT(RCC_REGS->RCC_AHB2ENR,RCC_Peripheral-RCC_AHB2);

	else if(RCC_Peripheral < 64) 							// RCC_AHB1

		SET_BIT(RCC_REGS->RCC_AHB1ENR,RCC_Peripheral-RCC_AHB1);

	else if(RCC_Peripheral < 96) 							// RCC_APB2

		SET_BIT(RCC_REGS->RCC_APB2ENR,RCC_Peripheral-RCC_APB2);

	else if(RCC_Peripheral < 128)							// RCC_APB1

		SET_BIT(RCC_REGS->RCC_APB1ENR,RCC_Peripheral-RCC_APB1);

}

void RCC_void_DISABLE_PERCLK(RCC_Peripheral_ID RCC_Peripheral)

{

	if(RCC_Peripheral < 32) 								// RCC_AHB2

		CLR_BIT(RCC_REGS->RCC_AHB2ENR,RCC_Peripheral-RCC_AHB2);

	else if(RCC_Peripheral < 64) 							// RCC_AHB1

		CLR_BIT(RCC_REGS->RCC_AHB1ENR,RCC_Peripheral-RCC_AHB1);

	else if(RCC_Peripheral < 96) 							// RCC_APB2

		CLR_BIT(RCC_REGS->RCC_APB2ENR,RCC_Peripheral-RCC_APB2);

	else if(RCC_Peripheral < 128) 														// RCC_APB1

		CLR_BIT(RCC_REGS->RCC_APB1ENR,RCC_Peripheral-RCC_APB1);


}

void RCC_void_RESET_PER(RCC_Peripheral_ID RCC_Peripheral)


{

	if(RCC_Peripheral < 32) 								// RCC_AHB2

		SET_BIT(RCC_REGS->RCC_AHB2RSTR,RCC_Peripheral-RCC_AHB2);

	else if(RCC_Peripheral < 64) 							// RCC_AHB1

		SET_BIT(RCC_REGS->RCC_AHB1RSTR,RCC_Peripheral-RCC_AHB1);

	else if(RCC_Peripheral < 96) 							// RCC_APB2

		SET_BIT(RCC_REGS->RCC_APB2RSTR,RCC_Peripheral-RCC_APB2);

	else if(RCC_Peripheral < 128)  														// RCC_APB1

		SET_BIT(RCC_REGS->RCC_APB1RSTR,RCC_Peripheral-RCC_APB1);

}


void RCC_void_PLL_CONFIG(u32 FREQ)
{
	CLR_BIT(RCC_REGS->RCC_CR,19);

	CLR_BIT(RCC_REGS->RCC_PLLCFGR,22);
	RCC_REGS->RCC_PLLCFGR |= 16;

	RCC_REGS->RCC_PLLCFGR |= (255<<6);


	RCC_REGS->RCC_PLLCFGR |= (2<<16);
	RCC_REGS->RCC_PLLCFGR |= (2<<24);
	RCC_REGS->RCC_PLLI2SCFGR |= (2<<28);


}


void RCC_void_BUS_PRESCFACTOR(RCC_Bus_ID RCC_Bus,RCC_PRESCFACTOR_ID RCC_PRESCFACTOR)
{

	switch (RCC_Bus)
	{
		case RCC_AHB1:

			RCC_REGS->RCC_CFGR |= ((RCC_PRESCFACTOR + 7) << 4);
			break;

		case RCC_AHB2:
			RCC_REGS->RCC_CFGR |= ((RCC_PRESCFACTOR + 7) << 4);
			break;

		case RCC_APB1:
			RCC_REGS->RCC_CFGR |= ((RCC_PRESCFACTOR + 3) << 10);

			break;

		case RCC_APB2:
			RCC_REGS->RCC_CFGR |= ((RCC_PRESCFACTOR + 3) << 13);

			break;


	}

}



