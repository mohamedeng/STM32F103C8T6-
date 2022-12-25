/*
 *
	u8 cmd_pins[3] = {12,10,9};
	u8 data_pins[4] = {11,10,9,8};
	LCD_ID LCD = LCD_LCD_ID_INIT(LCD_4BIT, GPIOA_REGS, data_pins, GPIOB_REGS, cmd_pins);
 */

#include "lcd.h"


void(*LCD_GPIO_PIN_MODE_FUNC)(GPIO_ID* GPIO,u8 PIN,GPIO_STATE_ID GPIO_STATE) = GPIO_void_PIN_MODE;

void(*LCD_GPIO_PIN_WRITE_FUNC)(GPIO_ID* GPIO,u8 PIN , GPIO_VALUE_ID GPIO_VALUE) = GPIO_void_PIN_WRITE;
void(*LCD_DELAY)(u32) = Delay_ms;

void LCD_void_EPIN_PULSE(LCD_ID* LCD)
{
	LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_CMD,LCD->EN_PIN,GPIO_HIGH_VALUE);
	LCD_DELAY(1);
	LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_CMD,LCD->EN_PIN,GPIO_LOW_VALUE);
	LCD_DELAY(2);

}

void LCD_void_INIT_GPIOPINS(LCD_ID* LCD)
{
	switch(LCD->LCD_DISPLAY_MODE)
	{

	case LCD_4BIT:
	case LCD4line_4BIT:

		LCD_GPIO_PIN_MODE_FUNC(LCD->GPIO_PORT_CMD, LCD->RS_PIN, GPIO_OUTPUT_PUSHPULLUP);
		LCD_GPIO_PIN_MODE_FUNC(LCD->GPIO_PORT_CMD, LCD->EN_PIN, GPIO_OUTPUT_PUSHPULLUP);
		LCD_GPIO_PIN_MODE_FUNC(LCD->GPIO_PORT_CMD, LCD->RW_PIN, GPIO_OUTPUT_PUSHPULLUP);

		for (int i=0;i<4;i++)
		{
			LCD_GPIO_PIN_MODE_FUNC(LCD->GPIO_PORT_DATA,LCD->DPINS_NUMEBER[i],GPIO_OUTPUT_PUSHPULLUP);
		}


		break;


	case LCD_8BIT:
	case LCD4line_8BIT:

		LCD_GPIO_PIN_MODE_FUNC(LCD->GPIO_PORT_CMD, LCD->RS_PIN, GPIO_OUTPUT_PUSHPULL);
		LCD_GPIO_PIN_MODE_FUNC(LCD->GPIO_PORT_CMD, LCD->EN_PIN, GPIO_OUTPUT_PUSHPULL);
		LCD_GPIO_PIN_MODE_FUNC(LCD->GPIO_PORT_CMD, LCD->RW_PIN, GPIO_OUTPUT_PUSHPULL);


		for (int i=0;i<8;i++)
		{
			LCD_GPIO_PIN_MODE_FUNC(LCD->GPIO_PORT_DATA,LCD->DPINS_NUMEBER[i],GPIO_OUTPUT_PUSHPULL);
		}

	}


}

void LCD_void_DATABUSWRITE_GPIOPINS(LCD_ID* LCD,LCD_DATABUSWRITE_MODE_ID LCD_DATABUSWRITE_MODE ,u8 PINVALUE)
{

	switch(LCD->LCD_DISPLAY_MODE)
	{

	case LCD_4BIT:
	case LCD4line_4BIT:

		if(LCD_DATABUSWRITE_MODE == LCD_CMD)
		{
			LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_CMD,LCD->RS_PIN,GPIO_LOW_VALUE);
			LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_CMD,LCD->RW_PIN,GPIO_LOW_VALUE);

		}


		if(LCD_DATABUSWRITE_MODE == LCD_DATA)
		{

			LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_CMD,LCD->RS_PIN,GPIO_HIGH_VALUE);
			LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_CMD,LCD->RW_PIN,GPIO_LOW_VALUE);

		}

		for (int i=7;i>=4;i--)
					{
						LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_DATA,LCD->DPINS_NUMEBER[i-4],GET_BIT(PINVALUE,i));
					}



		LCD_void_EPIN_PULSE(LCD);

		for (int i=4;i>=0;i--)
					{
						LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_DATA,LCD->DPINS_NUMEBER[i],GET_BIT(PINVALUE,i));
					}

		LCD_void_EPIN_PULSE(LCD);

		break;


	case LCD_8BIT:
	case LCD4line_8BIT:


		if(LCD_DATABUSWRITE_MODE == LCD_CMD)
		{

			LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_CMD,LCD->RS_PIN,GPIO_LOW_VALUE);
			LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_CMD,LCD->RW_PIN,GPIO_LOW_VALUE);

		}


		if(LCD_DATABUSWRITE_MODE == LCD_DATA)
		{

			LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_CMD,LCD->RS_PIN,GPIO_HIGH_VALUE);
			LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_CMD,LCD->RW_PIN,GPIO_LOW_VALUE);

		}


		for (int i=0;i<8;i++)
		{
			LCD_GPIO_PIN_WRITE_FUNC(LCD->GPIO_PORT_DATA,LCD->DPINS_NUMEBER[i],GET_BIT(PINVALUE,i));
		}

		LCD_void_EPIN_PULSE(LCD);


	}


}



LCD_ID LCD_LCD_ID_INIT(LCD_DISPLAY_MODE_ID LCD_DISPLAY_MODE,GPIO_ID* GPIO_PORT_DATA, u8* DPINS_NUMEBER,GPIO_ID* GPIO_PORT_CMD,u8* CPINS_NUMEBER)
{
	


	LCD_ID LCD = {LCD_DISPLAY_MODE,GPIO_PORT_DATA,DPINS_NUMEBER,GPIO_PORT_CMD,CPINS_NUMEBER[0],CPINS_NUMEBER[1],CPINS_NUMEBER[2],0,0,16};

	switch(LCD_DISPLAY_MODE)
	{
		case LCD_8BIT:
			
			LCD8bit_void_INIT( &LCD );
			break;
		case LCD_4BIT:
		
			LCD4bit_void_INIT( &LCD);

			break;

		case LCD4line_8BIT:

			LCD8bit_void_INIT( &LCD );
			break;


		case LCD4line_4BIT:
			LCD4bit_void_INIT( &LCD);

			break;
		
	}
	return LCD;
}
void LCD8bit_void_INIT(LCD_ID* LCD)
{

	LCD_void_INIT_GPIOPINS(LCD);


	LCD_void_cmd( LCD,0x38);
	LCD_void_cmd( LCD,0x02);
	LCD_void_cmd( LCD,0x06);
	LCD_void_cmd( LCD,0x80);
	LCD_void_cmd( LCD,0x0C);
	LCD_void_cmd( LCD,0x01);
		
	
}
void LCD4bit_void_INIT(LCD_ID* LCD)

{
	LCD_void_INIT_GPIOPINS(LCD);


	LCD_DELAY(150);		/* LCD Power ON delay always >15ms */

	LCD_void_cmd(LCD,0x33);
	LCD_void_cmd(LCD,0x32);	/* Send for 4 bit initialization of LCD  */
	LCD_void_cmd(LCD,0x28);	/* 2 line, 5*7 matrix in 4-bit mode */
	LCD_void_cmd(LCD,0x0c);	/* Display on cursor off */
	LCD_void_cmd(LCD,0x06);	/* Increment cursor (shift cursor to right) */
	LCD_void_cmd(LCD,0x01);	/* Clear display screen */

}



void LCD_void_cmd(LCD_ID* LCD,u8 cmd)
{

	LCD_void_DATABUSWRITE_GPIOPINS(LCD,LCD_CMD,cmd);


}
void LCD_void_char(LCD_ID* LCD,u8 chars)
{
	
	LCD_void_DATABUSWRITE_GPIOPINS(LCD,LCD_DATA,chars);

}

void LCD_void_string(LCD_ID* LCD,u8* string)
{
	for (int i = 0; string[i] != '\0';i++)
	{
		LCD_void_char(LCD,string[i]);

		LCD->Column_pointer++;
		if(LCD->Column_pointer >= LCD->MAX_CHARS_PERLINE)
		{
			LCD->Row_pointer++;

			if(LCD->LCD_DISPLAY_MODE == LCD_4BIT && LCD->LCD_DISPLAY_MODE == LCD_8BIT && LCD->Row_pointer == 2)
			{
				LCD_void_clear(LCD);
			}
			else if ( LCD->Row_pointer == 4)
			{
				LCD_void_clear(LCD);
			}

			LCD->Column_pointer = 0;
			LCD_void_Cursorpos(LCD,LCD->Row_pointer,LCD->Column_pointer);

		}

	}
}

void LCD_void_string_pos(LCD_ID* LCD,u8 row,u8 coulm,u8* string)
{
	LCD_void_Cursorpos(LCD,row,coulm);
	LCD_DELAY(2);
	LCD_void_string(LCD,string);
}


void LCD_void_Cursorpos(LCD_ID* LCD,u8 row,u8 coulm)
{

	if (row == 0 )
	{
		LCD_void_cmd( LCD,(coulm & 0x0F)|0x80);

	}
	if(row == 1)
	{
		LCD_void_cmd( LCD,(coulm & 0x0F)|0xC0);

	}
	if (row == 2)
	{
		LCD_void_cmd( LCD,(coulm & 0x0F)|0x90 );
	}
	if (row == 3)
	{
		LCD_void_cmd( LCD,(coulm & 0x0F)|0xD0 );
	}

	LCD->Row_pointer = row;
	LCD->Column_pointer = coulm;

}

void LCD_void_clear(LCD_ID* LCD)
{
	LCD->Column_pointer = 0;
	LCD->Row_pointer = 0;
	LCD_void_cmd ( LCD,0x01);		/* clear display */

	LCD_void_cmd ( LCD,0x80);		/* cursor at home position */

}

void LCD_void_delete(LCD_ID* LCD,u8 number_of_chars_to_delete)
{
	if (LCD->Column_pointer+(LCD->Row_pointer*16) <= number_of_chars_to_delete)
	{
		LCD_void_clear(LCD);
		return;

	}

	u8* white =(u8*) malloc(sizeof(u8)*(number_of_chars_to_delete+1));

	for (int i = 0;i<number_of_chars_to_delete;i++)
	{
		white[i] = ' ';
	}

	*(white+number_of_chars_to_delete) = '\0';



	LCD->Column_pointer = 0;
	LCD->Row_pointer = 0;

	for(int i =0 ;i<4;i++)
	{

		if ((LCD->Column_pointer-number_of_chars_to_delete)>=0)
		{
			 LCD->Column_pointer = (LCD->Column_pointer-number_of_chars_to_delete);
			 break;
		}

		else
		{
			LCD->Row_pointer--;
			number_of_chars_to_delete = number_of_chars_to_delete-16;

		}

	}

	LCD_void_string(LCD,white);

	free(white);
}

void LCD_void_custom_char (LCD_ID* LCD,u8 loc, u8 *msg)
{
	u8 i;
	if(loc<8)
	{
		LCD_void_cmd (LCD,0x40 + (loc*8));	/* Command 0x40 and onwards forces the device to point CGRAM address */
		for(i=0;i<8;i++)	/* Write 8 byte for generation of 1 character */
		LCD_void_char(LCD,msg[i]);
	}
	
}




void LCD_void_List_on_screen(LCD_ID* LCD ,u8** data_list,u8 list_size,u8 frist_screen_value)
{
	for (int i = frist_screen_value;i<list_size;i++)
	{

			if(i>2 && (LCD->LCD_DISPLAY_MODE == LCD4line_4BIT || LCD->LCD_DISPLAY_MODE == LCD4line_8BIT))
			{
				return;
			}

			if(i>0 && (LCD->LCD_DISPLAY_MODE == LCD_4BIT || LCD->LCD_DISPLAY_MODE == LCD_8BIT))
			{
				return;
			}


			LCD_void_string_pos(LCD,i,0,data_list[i]);

	}

}
