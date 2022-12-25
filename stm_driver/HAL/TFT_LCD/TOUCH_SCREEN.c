/*
 * TOUCH_SCREEN.c
 *
 *  Created on: Sep 17, 2022
 *      Author: hp
 */
#include "LIB/DELAY.h"
#include "TOUCH_SCREEN.h"



long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



void insert_sort(u32* Array,u16 ArraySize)
{
	u16 TEMP ;
	u16 HOLE;
	for (int i = 0; i< ArraySize; i++)
	{
		TEMP = Array[i];
		HOLE = i;
		while ((i > 0) && (Array[HOLE] > TEMP ) )
		{
			Array[HOLE] = Array[HOLE-1];
			HOLE--;

		}
		Array[HOLE] = TEMP ;

	}
}

TUOCH_SCREEN_ID TUOCH_SCREEN_INIT(GPIO_ID** Touch_PORTS,u8* Touch_PINS,u16 rxplate,u16 high,u16 width)
{
	TUOCH_SCREEN_ID TUOCH_SCREEN = {Touch_PORTS,Touch_PINS,rxplate,high,width};
	return TUOCH_SCREEN;
}

TUOCH_POINT_ID TUOCH_SCREEN_GET_POINT(TUOCH_SCREEN_ID* TUOCH_SCREEN)
{
	u32 SAMPLES [NUMSAMPLES] = {0};
	u32 temp[4];
	for(int i =0;i<4;i++)
	{
		temp[i] = TUOCH_SCREEN->Touch_PORTS[i]->GPIO_MODER;

	}
	u32 x = 0,y = 0,z = 0;

	GPIO_void_PIN_MODE(TUOCH_SCREEN->Touch_PORTS[YP],TUOCH_SCREEN->Touch_PINS[YP] , GPIO_ANALOGINPUT);
	GPIO_void_PIN_MODE(TUOCH_SCREEN->Touch_PORTS[YM],TUOCH_SCREEN->Touch_PINS[YM] , GPIO_ANALOGINPUT);
	GPIO_void_PIN_MODE(TUOCH_SCREEN->Touch_PORTS[XM],TUOCH_SCREEN->Touch_PINS[XM] , GPIO_OUTPUT_PUSHPULL);
	GPIO_void_PIN_MODE(TUOCH_SCREEN->Touch_PORTS[XP],TUOCH_SCREEN->Touch_PINS[XP] , GPIO_OUTPUT_PUSHPULL);

	GPIO_void_PIN_WRITE(TUOCH_SCREEN->Touch_PORTS[XP],TUOCH_SCREEN->Touch_PINS[XP], GPIO_HIGH_VALUE);
	GPIO_void_PIN_WRITE(TUOCH_SCREEN->Touch_PORTS[XM],TUOCH_SCREEN->Touch_PINS[XM], GPIO_LOW_VALUE);
	Delay_ms(1);



	for (int i = 0; i< NUMSAMPLES;i++)
	{
		if(TUOCH_SCREEN->Touch_PORTS[YP] == GPIOB_REGS)
			ADC_u32_ANALOG_REGULAR_SingleRead_NON_BLOCKING( (TUOCH_SCREEN->Touch_PINS[YP]+8),SAMPLES+i);
		else
			ADC_u32_ANALOG_REGULAR_SingleRead_NON_BLOCKING( TUOCH_SCREEN->Touch_PINS[YP],SAMPLES+i);

	}

	insert_sort(SAMPLES, NUMSAMPLES);

	x = 4095 - SAMPLES[NUMSAMPLES/2];
//////////////////////////////////////////////////////////////////////
	GPIO_void_PIN_MODE(TUOCH_SCREEN->Touch_PORTS[XP],TUOCH_SCREEN->Touch_PINS[XP] , GPIO_ANALOGINPUT);
	GPIO_void_PIN_MODE(TUOCH_SCREEN->Touch_PORTS[XM],TUOCH_SCREEN->Touch_PINS[XM] , GPIO_ANALOGINPUT);
	GPIO_void_PIN_MODE(TUOCH_SCREEN->Touch_PORTS[YM],TUOCH_SCREEN->Touch_PINS[YM] , GPIO_OUTPUT_PUSHPULL);
	GPIO_void_PIN_MODE(TUOCH_SCREEN->Touch_PORTS[YP],TUOCH_SCREEN->Touch_PINS[YP] , GPIO_OUTPUT_PUSHPULL);

	GPIO_void_PIN_WRITE(TUOCH_SCREEN->Touch_PORTS[YP],TUOCH_SCREEN->Touch_PINS[YP], GPIO_HIGH_VALUE);
	GPIO_void_PIN_WRITE(TUOCH_SCREEN->Touch_PORTS[YM],TUOCH_SCREEN->Touch_PINS[YM], GPIO_LOW_VALUE);
	Delay_ms(1);


	for (int i = 0; i< NUMSAMPLES;i++)
	{
		if(TUOCH_SCREEN->Touch_PORTS[XM] == GPIOB_REGS)
			ADC_u32_ANALOG_REGULAR_SingleRead_NON_BLOCKING( TUOCH_SCREEN->Touch_PINS[XM]+8,&SAMPLES[i]);
		else
			ADC_u32_ANALOG_REGULAR_SingleRead_NON_BLOCKING( TUOCH_SCREEN->Touch_PINS[XM],&SAMPLES[i]);

		//SAMPLES[i] = ADC_u32_ANALOG_REGULAR_SingleRead( (TUOCH_SCREEN->Touch_PINS[XM] < 8) ? (TUOCH_SCREEN->Touch_PINS[XM]) : (TUOCH_SCREEN->Touch_PINS[XM]-8));

	}

	insert_sort(SAMPLES, NUMSAMPLES);

	y = 4095 - SAMPLES[NUMSAMPLES/2];


//////////////////////////////////////////////////////////////////////////
	GPIO_void_PIN_MODE(TUOCH_SCREEN->Touch_PORTS[XP],TUOCH_SCREEN->Touch_PINS[XP] , GPIO_OUTPUT_PUSHPULL);
	GPIO_void_PIN_MODE(TUOCH_SCREEN->Touch_PORTS[XM],TUOCH_SCREEN->Touch_PINS[XM] , GPIO_ANALOGINPUT);
	GPIO_void_PIN_MODE(TUOCH_SCREEN->Touch_PORTS[YM],TUOCH_SCREEN->Touch_PINS[YM] , GPIO_OUTPUT_PUSHPULL);
	GPIO_void_PIN_MODE(TUOCH_SCREEN->Touch_PORTS[YP],TUOCH_SCREEN->Touch_PINS[YP] , GPIO_ANALOGINPUT);

	GPIO_void_PIN_WRITE(TUOCH_SCREEN->Touch_PORTS[XP],TUOCH_SCREEN->Touch_PINS[XP], GPIO_LOW_VALUE);
	GPIO_void_PIN_WRITE(TUOCH_SCREEN->Touch_PORTS[YM],TUOCH_SCREEN->Touch_PINS[YM], GPIO_HIGH_VALUE);

	Delay_ms(1);
	u32 z1,z2;
	if(TUOCH_SCREEN->Touch_PORTS[XM] == GPIOB_REGS)
		 ADC_u32_ANALOG_REGULAR_SingleRead_NON_BLOCKING( TUOCH_SCREEN->Touch_PINS[XM] + 8,&z1);
	else
		 ADC_u32_ANALOG_REGULAR_SingleRead_NON_BLOCKING( TUOCH_SCREEN->Touch_PINS[XM],&z1);

	if(TUOCH_SCREEN->Touch_PORTS[YP] == GPIOB_REGS)
		ADC_u32_ANALOG_REGULAR_SingleRead_NON_BLOCKING(TUOCH_SCREEN->Touch_PINS[YP] + 8,&z2);
	else
		ADC_u32_ANALOG_REGULAR_SingleRead_NON_BLOCKING( TUOCH_SCREEN->Touch_PINS[YP],&z2 );



	if(TUOCH_SCREEN->rxplate != 0 )
	{

		f32 rtouch = 0;
	    rtouch = z2;
	    rtouch /= z1;
	    rtouch -= 1;
	    rtouch *= x;
	    rtouch *= TUOCH_SCREEN->rxplate;
	    rtouch /= 4096;

	    z = rtouch;

	}

	else {
	    z = 4095 - (z2 - z1);
	  }


	for(int i = 0;i<4;i++)
	{
		TUOCH_SCREEN->Touch_PORTS[i]->GPIO_MODER = temp[i];

	}
	// 0 high
	// x 4095
	x = map(x, x_min_calibration, x_max_calibration, 0, 320);
	y = map(y, y_min_calibration, y_max_calibration, 0, 480);

	TUOCH_POINT_ID TUOCH_POINT = {x,y,z};

	return TUOCH_POINT;

}





/*	example code
 *
 		u8 strx[10],stry[10],strz[10] ;
		TUOCH_POINT_ID TUOCH_POINT;
		ADC_void_INIT(0, 0);

		int x,y,z = 0;
 		GPIO_ID* Touch_PORTS []={GPIOB_REGS,GPIOB_REGS,GPIOA_REGS,GPIOA_REGS};
		u8 Touch_PINS[] = {0,1,2,1};//xp,yp,xm,ym
	    TUOCH_SCREEN_ID TUOCH_SCREEN = TUOCH_SCREEN_INIT(Touch_PORTS,Touch_PINS,0,TFT_LCD.TFT_LCD_high,TFT_LCD.TFT_LCD_width);

	    while(1)
	    {
			TUOCH_POINT = TUOCH_SCREEN_GET_POINT(&TUOCH_SCREEN);
			x=  TUOCH_POINT.x;
			z=  TUOCH_POINT.z;
			y=  TUOCH_POINT.y;
			sprintf((char*)strx, "%d", x);
			sprintf((char*)stry, "%d", y);
			sprintf((char*)strz, "%d", z);
			if(z>300)
			{
				TFT_LCD_void_STRING_WRITE(&TFT_LCD,strx,0,0, TFT_LCD_FONT16,0xFF00,0);
				TFT_LCD_void_STRING_WRITE(&TFT_LCD,stry,0,16, TFT_LCD_FONT16,0xFF00,0);
				TFT_LCD_void_STRING_WRITE(&TFT_LCD,strz,0,32, TFT_LCD_FONT16,0xFF00,0);
				Delay_ms(100);
				TFT_LCD_void_DRAW_RECT(&TFT_LCD,0,0,50,64,0x0000);

			}
		}
		Delay_ms(1);
 *
 *
 */
