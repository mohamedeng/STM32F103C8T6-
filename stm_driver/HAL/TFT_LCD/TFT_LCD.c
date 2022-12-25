/*
 * TFT_LCD.c
 *
 *  Created on: Sep 13, 2022
 *      Author: hp
 */
#include "HAL/TFT_LCD/FONTS/fonts.h"
#include "LIB/DELAY.h"
#include "TFT_LCD.h"

#define FAST_MODE


TFT_LCD_ID TFT_LCD_void_INIT(GPIO_ID** TFT_LCD_DATAGPIOS,u8* TFT_LCD_DATAPINS,GPIO_ID** TFT_LCD_CMDGPIOS,u8* LCD_CMDPINS)
{
	for (int i = 0; i< 8 ; i++)
	GPIO_void_PIN_MODE(TFT_LCD_DATAGPIOS[i], TFT_LCD_DATAPINS[i], GPIO_OUTPUT_PUSHPULL);

	for (int i = 0; i < 5 ; i++)
		GPIO_void_PIN_MODE(TFT_LCD_CMDGPIOS[i], LCD_CMDPINS[i], GPIO_OUTPUT_PUSHPULL);

	TFT_LCD_ID TFT_LCD = {TFT_LCD_DATAGPIOS,TFT_LCD_DATAPINS,TFT_LCD_CMDGPIOS,LCD_CMDPINS[0],LCD_CMDPINS[1],LCD_CMDPINS[2],LCD_CMDPINS[3],LCD_CMDPINS[4],(u16)480,(u16)320};


	GPIO_void_PIN_WRITE(TFT_LCD_CMDGPIOS[0], LCD_CMDPINS[0], GPIO_HIGH_VALUE);
	Delay_ms(50);

	GPIO_void_PIN_WRITE(TFT_LCD_CMDGPIOS[1], LCD_CMDPINS[1], GPIO_HIGH_VALUE);
	GPIO_void_PIN_WRITE(TFT_LCD_CMDGPIOS[2], LCD_CMDPINS[2], GPIO_HIGH_VALUE);
	GPIO_void_PIN_WRITE(TFT_LCD_CMDGPIOS[3], LCD_CMDPINS[3], GPIO_HIGH_VALUE);
	GPIO_void_PIN_WRITE(TFT_LCD_CMDGPIOS[4], LCD_CMDPINS[4], GPIO_HIGH_VALUE);


	GPIO_void_PIN_WRITE(TFT_LCD_CMDGPIOS[1], LCD_CMDPINS[1], GPIO_LOW_VALUE);

	//Delay_ms(10);

	TFT_LCD_void_CMD(&TFT_LCD, TFT_LCD_CONTARST);
	TFT_LCD_void_DATA(&TFT_LCD, 0x54);
	TFT_LCD_void_DATA(&TFT_LCD, 0x00);

	//Delay_ms(10);

	TFT_LCD_void_CMD(&TFT_LCD, TFT_LCD_MemoryAccessControl);
	TFT_LCD_void_DATA(&TFT_LCD, 0x40);

	//Delay_ms(10);
	TFT_LCD_void_CMD(&TFT_LCD, TFT_LCD_PIXELFORMAT);
	TFT_LCD_void_DATA(&TFT_LCD, 0x55);

	//Delay_ms(10);

	TFT_LCD_void_CMD(&TFT_LCD, TFT_LCD_SLEEPOUT);

	TFT_LCD_void_CMD(&TFT_LCD, TFT_LCD_DisplayON);

	TFT_LCD_void_CMD(&TFT_LCD, TFT_LCD_MemoryWrite);
	Delay_ms(200);

	return TFT_LCD;

}


void TFT_LCD_void_WRITE_DATA_ON_PINS(TFT_LCD_ID* TFT_LCD,u8 DATA)
{


	GPIO_void_PIN_WRITE(TFT_LCD->TFT_LCD_CMDGPIOS[3],TFT_LCD->TFT_LCD_WR, GPIO_LOW_VALUE);
#ifndef FAST_MODE
	for(int i = 0; i < 8;i++)
	{
		GPIO_void_PIN_WRITE(TFT_LCD->TFT_LCD_DATAGPIOS[i],TFT_LCD->TFT_LCD_DATAPINS[i], GET_BIT(DATA,i));

	}

#else
	TFT_LCD->TFT_LCD_DATAGPIOS[0]->GPIO_ODR = DATA;

#endif
	GPIO_void_PIN_WRITE(TFT_LCD->TFT_LCD_CMDGPIOS[3],TFT_LCD->TFT_LCD_WR, GPIO_HIGH_VALUE);


}

void TFT_LCD_void_CMD(TFT_LCD_ID* TFT_LCD,u8 COMMAND)
{

	GPIO_void_PIN_WRITE(TFT_LCD->TFT_LCD_CMDGPIOS[2],TFT_LCD->TFT_LCD_RS, GPIO_LOW_VALUE);


	TFT_LCD_void_WRITE_DATA_ON_PINS(TFT_LCD,COMMAND);



}
void TFT_LCD_void_DATA(TFT_LCD_ID* TFT_LCD,u8 DATA)
{

	GPIO_void_PIN_WRITE(TFT_LCD->TFT_LCD_CMDGPIOS[2],TFT_LCD->TFT_LCD_RS, GPIO_HIGH_VALUE);


	TFT_LCD_void_WRITE_DATA_ON_PINS(TFT_LCD,DATA);


}

void TFT_LCD_void_WRITE_PIXEL(TFT_LCD_ID* TFT_LCD,u16 XPOS,u16 YPOS,u16 RGB_CODE)

{
	GPIO_void_PIN_WRITE(TFT_LCD->TFT_LCD_CMDGPIOS[4], TFT_LCD->TFT_LCD_CS, GPIO_LOW_VALUE);

	TFT_LCD_void_SET_CURSOR(TFT_LCD,XPOS,YPOS,XPOS+1,YPOS+1);


	TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_MemoryWrite);

	TFT_LCD_void_DATA(TFT_LCD, (RGB_CODE >> 8));
	TFT_LCD_void_DATA(TFT_LCD, RGB_CODE);

}

void TFT_LCD_void_SET_CURSOR(TFT_LCD_ID* TFT_LCD,u16 XPOS1,u16 YPOS1,u16 XPOS2,u16 YPOS2)
{


	TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_ColumnAddressSet);

	TFT_LCD_void_DATA(TFT_LCD, (XPOS1>>8));
	TFT_LCD_void_DATA(TFT_LCD, XPOS1);

	TFT_LCD_void_DATA(TFT_LCD, ((XPOS2)>>8));
	TFT_LCD_void_DATA(TFT_LCD, XPOS2);

	TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_PageAddressSet);
	TFT_LCD_void_DATA(TFT_LCD, (YPOS1>>8));
	TFT_LCD_void_DATA(TFT_LCD, YPOS1);

	TFT_LCD_void_DATA(TFT_LCD, ((YPOS2)>>8));
	TFT_LCD_void_DATA(TFT_LCD, YPOS2);


}



void SWAP_void(u16* XPOS1,u16* YPOS1,u16* XPOS2,u16* YPOS2)
{

	if (*XPOS1 <= *XPOS2 && *YPOS1 <= *YPOS2)
		return;

	u16* TEMP_X = XPOS1;
	XPOS1 = XPOS2;
	XPOS2 = TEMP_X;

	u16* TEMP_Y = YPOS1;
	YPOS1 = YPOS2;
	YPOS2 = TEMP_Y;




}

void TFT_LCD_void_DRAW_VLINE(TFT_LCD_ID* TFT_LCD,u16 XPOS1,u16 XPOS2,u16 YPOS,u16 RGB_CODE)
{
	TFT_LCD_void_SET_CURSOR(TFT_LCD,XPOS1,YPOS,XPOS2,YPOS+1);
	TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_MemoryWrite);
	u8 RGB_SHIFT = (RGB_CODE >> 8);
	for(int i = 0; i<(XPOS2-XPOS1) ; i++)
	{
		TFT_LCD_void_DATA(TFT_LCD, RGB_SHIFT);
		TFT_LCD_void_DATA(TFT_LCD, RGB_CODE);
	}

	}
void TFT_LCD_void_DRAW_HLINE(TFT_LCD_ID* TFT_LCD,u16 XPOS,u16 YPOS1,u16 YPOS2,u16 RGB_CODE)
{

	TFT_LCD_void_SET_CURSOR(TFT_LCD,XPOS,YPOS1, XPOS+1,YPOS2);
	TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_MemoryWrite);
	u8 RGB_SHIFT = (RGB_CODE >> 8);
	for(int i = 0; i<(YPOS2-YPOS1) ; i++)
	{
		TFT_LCD_void_DATA(TFT_LCD, RGB_SHIFT);
		TFT_LCD_void_DATA(TFT_LCD, RGB_CODE);
	}


}

void TFT_LCD_void_DRAW_LINE(TFT_LCD_ID* TFT_LCD,u16 XPOS1,u16 YPOS1,u16 XPOS2,u16 YPOS2,u16 RGB_CODE)
{

	SWAP_void(&XPOS1,&YPOS1,&XPOS2,&YPOS2);


	s16 delta_x = XPOS2 - XPOS1;
	s16 delta_y = YPOS2 - YPOS1;
	if(delta_x == 0)
	{

		TFT_LCD_void_DRAW_HLINE(TFT_LCD, XPOS1,YPOS1, YPOS2, RGB_CODE);
		return;

	}
	if(delta_y == 0)
	{

		TFT_LCD_void_DRAW_VLINE(TFT_LCD, XPOS1, XPOS2, YPOS1, RGB_CODE);
		return;

	}
	TFT_LCD_void_WRITE_PIXEL(TFT_LCD,XPOS1,YPOS1,RGB_CODE);
	float SLOP = delta_y/delta_x;
	u16 TEMP_Y;
	u16 TEMP_X;

	s16 P_X = 0;
	if(SLOP < 0)
	{
		return ;
	}

	else if (SLOP < 1)
	{
		P_X += 2*delta_y - delta_x;
		while(XPOS1 != XPOS2 && YPOS1 != YPOS2)
		{
			TEMP_Y = YPOS1;
			TFT_LCD_void_WRITE_PIXEL(TFT_LCD,XPOS1,YPOS1,RGB_CODE);

			if(P_X >= 0 )
			{

			XPOS1++;
			YPOS1++;

			}

			if(P_X < 0)
			{

			XPOS1++;

			}
			P_X += 2 * delta_y - 2 * delta_x * (YPOS1 - TEMP_Y);
		}


	}

	else if(SLOP > 1)
		{

		P_X += 2*delta_x - delta_y;
		while(XPOS1 != XPOS2 && YPOS1 != YPOS2)
		{
			TEMP_X = XPOS1;
			TFT_LCD_void_WRITE_PIXEL(TFT_LCD,XPOS1,YPOS1,RGB_CODE);

			if(P_X >= 0 )
			{

			XPOS1++;
			YPOS1++;

			}

			if(P_X < 0)
			{

			YPOS1++;

			}
			P_X += 2 * delta_x - 2 * delta_y * (XPOS1 - TEMP_X);
		}




		}

	TFT_LCD_void_SET_CURSOR(TFT_LCD,XPOS1,YPOS1,XPOS2,YPOS2);





}


void TFT_LCD_void_DRAW_RECT(TFT_LCD_ID* TFT_LCD,u16 XPOS1,u16 YPOS1,u16 XPOS2,u16 YPOS2,u16 RGB_CODE)
{
	u8 RGB_CODE_SHIFTED = RGB_CODE >> 8;
	TFT_LCD_void_SET_CURSOR(TFT_LCD, XPOS1, YPOS1, XPOS2, YPOS2);
	TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_MemoryWrite);
	for(int i = 0; i< ((XPOS2-XPOS1)*(YPOS2-YPOS1));i++)
	{

		TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_SHIFTED);
		TFT_LCD_void_DATA(TFT_LCD, RGB_CODE);

	}



}

void TFT_LCD_void_DRAW_CIRCLE(TFT_LCD_ID* TFT_LCD,u16 XPOS,u16 YPOS,u16 radius,u16 RGB_CODE)
{

	// (x - a)^2 + (y - b)^2 = r^2
	u16 CenterPoint_x = XPOS+radius/2,CenterPoint_y = YPOS+radius/2;


	TFT_LCD_void_SET_CURSOR(TFT_LCD, XPOS, YPOS, XPOS+radius, YPOS+radius);
	TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_MemoryWrite);
/*	for(u32 i = 0; i < radius*radius;i++)
	{

		if()
		TFT_LCD_void_DATA(TFT_LCD, (RGB_CODE >> 8));
		TFT_LCD_void_DATA(TFT_LCD, RGB_CODE);

	}
*/

}

void TFT_LCD_void_DRAW_POINT(TFT_LCD_ID* TFT_LCD,u16 XPOS,u16 YPOS,u16 RGB_CODE)
{
	GPIO_void_PIN_WRITE(TFT_LCD->TFT_LCD_CMDGPIOS[4], TFT_LCD->TFT_LCD_CS, GPIO_LOW_VALUE);
	TFT_LCD_void_SET_CURSOR(TFT_LCD, XPOS, YPOS, XPOS+5, YPOS+5);
	TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_MemoryWrite);

	for(u32 i = 0; i < 5*5;i++)
	{

		TFT_LCD_void_DATA(TFT_LCD, (RGB_CODE >> 8));
		TFT_LCD_void_DATA(TFT_LCD, RGB_CODE);

	}


}


void TFT_LCD_void_CHAR_WRITE(TFT_LCD_ID* TFT_LCD,u8 CHAR,u16 XPOS,u16 YPOS,FONT_SIZE_ID FONT_SIZE,u16 RGB_CODE_FONT,u16 RGB_CODE_BACKGROUND)
{
	GPIO_void_PIN_WRITE(TFT_LCD->TFT_LCD_CMDGPIOS[4], TFT_LCD->TFT_LCD_CS, GPIO_LOW_VALUE);

	const u8* pointer ;


	switch(FONT_SIZE)
	{

	case TFT_LCD_FONT8:

		TFT_LCD_void_SET_CURSOR(TFT_LCD, XPOS, YPOS, XPOS+7, YPOS+7);
		TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_MemoryWrite);
		pointer = (Font8_Table+((CHAR-32)*8));
		for(u8 i = 0; i<8 ;i++)
		{
			for(s32 k = 7 ; k >= 0 ; k--)
			{


				if(GET_BIT(pointer[i],k))
				{

					TFT_LCD_void_DATA(TFT_LCD, (RGB_CODE_FONT >> 8));
					TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_FONT);

				}
				else
				{

					TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_BACKGROUND >> 8);
					TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_BACKGROUND);
				}
			}
		}

		break;
	case TFT_LCD_FONT12:


		TFT_LCD_void_SET_CURSOR(TFT_LCD, XPOS, YPOS, XPOS+7, YPOS+11);
		TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_MemoryWrite);
		pointer = (Font12_Table+((CHAR-32)*12));//Font24_Table+792;//

		for(u32 i = 0; i<12; i++)
		{

			for(int k = 7;k >= 0;k--)
			{

							if( GET_BIT(pointer[i],k))
								{

									TFT_LCD_void_DATA(TFT_LCD, (RGB_CODE_FONT >> 8));
									TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_FONT);

									//TFT_LCD_void_WRITE_PIXEL(TFT_LCD,XPOS+i+j,YPOS+i+j,RGB_CODE);
								}
							else
								{

								TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_BACKGROUND >> 8);
								TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_BACKGROUND);
								}
			}
		}
			break;

	case TFT_LCD_FONT16:

		TFT_LCD_void_SET_CURSOR(TFT_LCD, XPOS, YPOS, XPOS+15, YPOS+15);
		TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_MemoryWrite);
		pointer = (Font16_Table+((CHAR-32)*32));//Font24_Table+792;//

		for(u32 i = 0; i<32; i++)
		{

			for(s32 k = 7;k >= 0;k--)
			{

							if( GET_BIT(pointer[i],k))
								{

									TFT_LCD_void_DATA(TFT_LCD, (RGB_CODE_FONT >> 8));
									TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_FONT);

									//TFT_LCD_void_WRITE_PIXEL(TFT_LCD,XPOS+i+j,YPOS+i+j,RGB_CODE);
								}
							else
								{

								TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_BACKGROUND >> 8);
								TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_BACKGROUND);
								}
			}
		}
			break;

	case TFT_LCD_FONT20:


		TFT_LCD_void_SET_CURSOR(TFT_LCD, XPOS, YPOS, XPOS+15, YPOS+19);
		TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_MemoryWrite);
		pointer = (Font20_Table+((CHAR-32)*40));//Font24_Table+792;//

		for(u32 i = 0; i<40; i++)
		{

			for(s32 k = 7;k >= 0;k--)
			{

							if( GET_BIT(pointer[i],k))
								{

									TFT_LCD_void_DATA(TFT_LCD, (RGB_CODE_FONT >> 8));
									TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_FONT);
								}
							else
								{

								TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_BACKGROUND >> 8);
								TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_BACKGROUND);
								}
			}
		}
			break;

	case TFT_LCD_FONT24:

		TFT_LCD_void_SET_CURSOR(TFT_LCD, XPOS, YPOS, XPOS+23, YPOS+23);
		TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_MemoryWrite);
		pointer = (Font24_Table+((CHAR-32)*72));

		for(u32 i = 0; i<72; i++)
		{

			for(s32 k = 7;k >= 0;k--)
			{

							if( GET_BIT(pointer[i],k))
								{

									TFT_LCD_void_DATA(TFT_LCD, (RGB_CODE_FONT >> 8));
									TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_FONT);
								}
							else
								{
								TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_BACKGROUND >> 8);
								TFT_LCD_void_DATA(TFT_LCD, RGB_CODE_BACKGROUND);
								}

			}

		}

		break;


	}




}


void TFT_LCD_void_STRING_WRITE(TFT_LCD_ID* TFT_LCD,u8* STR,u16 XPOS,u16 YPOS,FONT_SIZE_ID FONT_SIZE,u16 RGB_CODE_FONT,u16 RGB_CODE_BACKGROUND)
{
	u32 i = 0;
	while (STR[i] != '\0')
	{
		switch(FONT_SIZE)
		{

		case TFT_LCD_FONT8:
			TFT_LCD_void_CHAR_WRITE(TFT_LCD,STR[i],XPOS+i*5,YPOS,FONT_SIZE,RGB_CODE_FONT,RGB_CODE_BACKGROUND);
	 		break;
		case TFT_LCD_FONT12:
			TFT_LCD_void_CHAR_WRITE(TFT_LCD,STR[i],XPOS+i*7,YPOS,FONT_SIZE,RGB_CODE_FONT,RGB_CODE_BACKGROUND);
			break;

		case TFT_LCD_FONT16:
			TFT_LCD_void_CHAR_WRITE(TFT_LCD,STR[i],XPOS+i*11,YPOS,FONT_SIZE,RGB_CODE_FONT,RGB_CODE_BACKGROUND);
			break;

		case TFT_LCD_FONT20:
			TFT_LCD_void_CHAR_WRITE(TFT_LCD,STR[i],XPOS+i*14,YPOS,FONT_SIZE,RGB_CODE_FONT,RGB_CODE_BACKGROUND);
			break;

		case TFT_LCD_FONT24:
			TFT_LCD_void_CHAR_WRITE(TFT_LCD,STR[i],XPOS+i*17,YPOS,FONT_SIZE,RGB_CODE_FONT,RGB_CODE_BACKGROUND);
			break;
		}

		i++;
	}


}

u16 TFT_LCD_u16_READ_PIXEL(TFT_LCD_ID* TFT_LCD,u16 XPOS,u16 YPOS)
{
	return 0 ;
}

void TFT_LCD_void_SET_BACKGROUND(TFT_LCD_ID* TFT_LCD,u16 RGB_CODE)
{

	TFT_LCD_void_SET_CURSOR(TFT_LCD, 0, 0, TFT_LCD->TFT_LCD_width, TFT_LCD->TFT_LCD_high);
	TFT_LCD_void_CMD(TFT_LCD, TFT_LCD_MemoryWrite);
	u8 RGB_SHIFT = RGB_CODE >> 8;

	GPIO_void_PIN_WRITE(TFT_LCD->TFT_LCD_CMDGPIOS[2],TFT_LCD->TFT_LCD_RS, GPIO_HIGH_VALUE);




	for(u32 i = 0; i < TFT_LCD->TFT_LCD_width*TFT_LCD->TFT_LCD_high;i++)
	{

		//TFT_LCD_void_DATA(TFT_LCD, RGB_SHIFT);
		//TFT_LCD_void_DATA(TFT_LCD, RGB_CODE);
		TFT_LCD_void_WRITE_DATA_ON_PINS(TFT_LCD,RGB_SHIFT);
		TFT_LCD_void_WRITE_DATA_ON_PINS(TFT_LCD,RGB_CODE);

	}


}




