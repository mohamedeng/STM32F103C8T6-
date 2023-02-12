/*
 * SD_CARD.c
 *
 *  Created on: Nov 18, 2022
 *      Author: hp
 */
#include "SD_CARD_INFO.h"
#include "SD_CARD.h"
//
//	RCC_void_ENABLE_PERCLK(RCC_SPI)
// 	GPIO_void_PIN_MODE(GPIO, PIN, GPIO_STATE)
//	GPIO_void_AF_MODE(GPIO, PIN, GPIO_AF_TYPE)
//	SPI_INIT(SPI, SPI_MASTER, SPI_MODE0, SPI_BAUD_RATE_FACTOR_16, SPI_FRAME_SIZE_8, SPI_MSBF);
//

void SD_CARD_PUSH_ERROR(SD_CARD_ID* SD_CARD,u8 ERROR)
{

	Stack_Struct_Push(&SD_CARD->HW_ErrorStack, &ERROR);
	SD_CARD->HW_ErrorCount = SD_CARD->HW_ErrorStack.index;

}
void SD_CARD_POP_ERROR(SD_CARD_ID* SD_CARD)
{

	Stack_Struct_Pull(&SD_CARD->HW_ErrorStack);
	SD_CARD->HW_ErrorCount = SD_CARD->HW_ErrorStack.index;
}
u8 SD_CARD_GetLast_ERROR(SD_CARD_ID* SD_CARD)
{
	u8* the_last_error = 0;
	Stack_Struct_GetLast(&SD_CARD->HW_ErrorStack, (void*)the_last_error);
	return (*the_last_error);
}


void SD_CARD_void_RECEIVE_DATA(SD_CARD_ID* SD_CARD,u8* BUFFER,u32 DATA_size)
{
	for (int i = 0; i < DATA_size;i++)
	{
		BUFFER[i] = SD_CARD_u8_SPI_RECEIVE(SD_CARD);
	}

}

void SD_CARD_ENABLE_CS(SD_CARD_ID* SD_CARD)
{
	GPIO_void_PIN_WRITE(SD_CARD->SD_CARD_CS_PORT, SD_CARD->SD_CARD_CS_PIN, GPIO_LOW_VALUE);

}
void SD_CARD_DISABLE_CS(SD_CARD_ID* SD_CARD)
{
	GPIO_void_PIN_WRITE(SD_CARD->SD_CARD_CS_PORT, SD_CARD->SD_CARD_CS_PIN, GPIO_HIGH_VALUE);

}

void SD_CARD_void_SPI_SEND(SD_CARD_ID* SD_CARD,u8 DATA)
{
	SPI_void_TRANSMIT_BYTE(SD_CARD->SD_CARD_SPI, DATA);

}
u8 SD_CARD_u8_SPI_RECEIVE(SD_CARD_ID* SD_CARD)
{
	u8 DATA = 0xFF;
	DATA = SPI_u16_RECEIVE_BYTE_TX_CONTROL(SD_CARD->SD_CARD_SPI,DATA);
	return DATA;
}
void SD_CARD_void_WAIT(SD_CARD_ID* SD_CARD,u32 TIME_OUT)
{
	u8 RES =0xFF;
	u32 wait_time = 0;
	while( wait_time != TIME_OUT)
	{
		RES = SD_CARD_u8_SPI_RECEIVE(SD_CARD);
		if(RES != 0xFF)
		{
			return;
		}
		wait_time++;
	}

}



u8 SD_CARD_u8_RES_WAIT(SD_CARD_ID* SD_CARD,u32* value_Expected,u8 value_Expected_count,u32 TIME_OUT)
{
	u8 RES = 0xFF;
	u32 wait_time = 0;
	while( wait_time != TIME_OUT)
	{
		for(int i = 0; i<value_Expected_count;i++)
		{
			if(RES == value_Expected[i] )
			return RES;
		}
		RES = SD_CARD_u8_SPI_RECEIVE(SD_CARD);
		wait_time++;
	}
	if(TIME_OUT == wait_time)
	{
		return 0xFF;
	}
	return RES;
	//error if the return 0xFF

}



void SD_CARD_void_SEND_COMMAND(SD_CARD_ID* SD_CARD,SD_CARD_COMMANDS SD_CARD_COMMAND,u32 ARGUMENT)
{
	SD_CARD_void_SPI_SEND(SD_CARD,0xFF);
	SD_CARD_ENABLE_CS(SD_CARD);
	SD_CARD_void_SPI_SEND(SD_CARD,0xFF);
	u8 fake_CRC = 0xFF;
	u8 a[4] = {((ARGUMENT)>>24),((ARGUMENT)>>16),((ARGUMENT)>>8),(ARGUMENT)};

	if(CMD0 == SD_CARD_COMMAND)
		fake_CRC = 0x95;

	if(CMD8 == SD_CARD_COMMAND)
		fake_CRC = 0x87;// with argument 0x1AA

	SD_CARD_void_SPI_SEND(SD_CARD,(SD_CARD_COMMAND|0x40));
	for(int i = 0;i<4;i++)
	{

		SD_CARD_void_SPI_SEND(SD_CARD, a[i]);

	}
	SD_CARD_void_SPI_SEND(SD_CARD,fake_CRC);

}

u8 SD_CARD_u8_READ_SOME_BLOCK(SD_CARD_ID* SD_CARD,u32 LBA,u8* BLOCK_ARRAY,u32 SIZE_OF_ARRAY,u32 START_READ)
{
	u8 TEMP_ARRAY[256];
	u8 error = 	SD_CARD_u8_READ_BLOCK(SD_CARD, LBA, TEMP_ARRAY);
	BLOCK_ARRAY = TEMP_ARRAY+START_READ;
	return error;

}

u8 SD_CARD_u8_READ_BLOCK(SD_CARD_ID* SD_CARD,u32 LBA,u8* BLOCK_ARRAY)
{
	//----------------------------------------- some clock cycles for the sd card
	SD_CARD_void_SPI_SEND(SD_CARD,0xFF);
	SD_CARD_ENABLE_CS(SD_CARD);
	SD_CARD_void_SPI_SEND(SD_CARD,0xFF);
	//-----------------------------------------

	u8 R1 =0xFF;
	u8 DATA_TOKEN = 0xFF;
	u8 crc [2] = {0xFF};

	//----------------------------------------- send the request to sd card
	SD_CARD_void_SEND_COMMAND(SD_CARD, CMD17, LBA);
	R1 = SD_CARD_u8_RES_WAIT(SD_CARD,(u32[]){0x01,0x00},2,200);
	DATA_TOKEN = SD_CARD_u8_RES_WAIT(SD_CARD,(u32[]){0xfe,0x01,0x02,0x03,0x04,0x05},6,1000);
	if(DATA_TOKEN != 0xfe)
	{
		SD_CARD_PUSH_ERROR(SD_CARD, SD_CARD_CMD17_DATA_TOKEN_ERROR);
		return 0xFF;
	}
	//-----------------------------------------


	//----------------------------------------- the sd card response with data in 512 byte block
	SD_CARD_void_RECEIVE_DATA(SD_CARD, BLOCK_ARRAY, 512);
	SD_CARD_void_RECEIVE_DATA(SD_CARD, crc,2);
	BLOCK_ARRAY[512] = crc[0];
	BLOCK_ARRAY[513] = crc[1];
	//-----------------------------------------

	//----------------------------------------- some clock cycles for the sd card
	SD_CARD_void_SPI_SEND(SD_CARD,0xFF);
	SD_CARD_DISABLE_CS(SD_CARD);
	SD_CARD_void_SPI_SEND(SD_CARD,0xFF);
	//-----------------------------------------

	return 0;
}




SD_CARD_ID SD_CARD_INIT(
		SPI_PER SPI_PER_NUMER,
		GPIO_ID** SD_CARD_PORTS,u8* SD_CARD_PINS)
{

	// set pins to spi mode

	switch(SPI_PER_NUMER)
	{
	case SPI1:
		RCC_void_ENABLE_PERCLK(RCC_SPI1);

		GPIO_void_AF_MODE(SD_CARD_PORTS[SD_CARD_SCK], SD_CARD_PINS[SD_CARD_SCK], GPIO_AF_SPI1);
		GPIO_void_PIN_MODE(SD_CARD_PORTS[SD_CARD_SCK],SD_CARD_PINS[SD_CARD_SCK], GPIO_AF_PUSHPULL);
		GPIO_void_PIN_MODE(SD_CARD_PORTS[SD_CARD_CS],SD_CARD_PINS[SD_CARD_CS], GPIO_OUTPUT_PUSHPULLUP);

		for(int i = 0;i<2;i++)
		{
			// need to replace to more general
			GPIO_void_PIN_MODE(SD_CARD_PORTS[i],SD_CARD_PINS[i], GPIO_AF_PUSHPULLUP); // must pulled high
			GPIO_void_AF_MODE(SD_CARD_PORTS[i], SD_CARD_PINS[i], GPIO_AF_SPI1);

		}

		break;

	case SPI2:
		RCC_void_ENABLE_PERCLK(RCC_SPI2);

		GPIO_void_AF_MODE(SD_CARD_PORTS[SD_CARD_SCK], SD_CARD_PINS[SD_CARD_SCK], GPIO_AF_SPI2);
		GPIO_void_PIN_MODE(SD_CARD_PORTS[SD_CARD_SCK],SD_CARD_PINS[SD_CARD_SCK], GPIO_AF_PUSHPULL);
		GPIO_void_PIN_MODE(SD_CARD_PORTS[SD_CARD_CS],SD_CARD_PINS[SD_CARD_CS], GPIO_OUTPUT_PUSHPULLUP);

		for(int i = 0;i<2;i++)
		{
			// need to replace to more general
			GPIO_void_PIN_MODE(SD_CARD_PORTS[i],SD_CARD_PINS[i], GPIO_AF_PUSHPULLUP); // must pulled high
			GPIO_void_AF_MODE(SD_CARD_PORTS[i], SD_CARD_PINS[i], GPIO_AF_SPI2);

		}

		break;
	case SPI3:
		RCC_void_ENABLE_PERCLK(RCC_SPI3);

		GPIO_void_AF_MODE(SD_CARD_PORTS[SD_CARD_SCK], SD_CARD_PINS[SD_CARD_SCK], GPIO_AF_SPI3);
		GPIO_void_PIN_MODE(SD_CARD_PORTS[SD_CARD_SCK],SD_CARD_PINS[SD_CARD_SCK], GPIO_AF_PUSHPULL);
		GPIO_void_PIN_MODE(SD_CARD_PORTS[SD_CARD_CS],SD_CARD_PINS[SD_CARD_CS], GPIO_OUTPUT_PUSHPULLUP);

		for(int i = 0;i<2;i++)
		{
			// need to replace to more general
			GPIO_void_PIN_MODE(SD_CARD_PORTS[i],SD_CARD_PINS[i], GPIO_AF_PUSHPULLUP); // must pulled high
			GPIO_void_AF_MODE(SD_CARD_PORTS[i], SD_CARD_PINS[i], GPIO_AF_SPI3);

		}

		break;
	case SPI4:
		RCC_void_ENABLE_PERCLK(RCC_SPI4);

		GPIO_void_AF_MODE(SD_CARD_PORTS[SD_CARD_SCK], SD_CARD_PINS[SD_CARD_SCK], GPIO_AF_SPI4);
		GPIO_void_PIN_MODE(SD_CARD_PORTS[SD_CARD_SCK],SD_CARD_PINS[SD_CARD_SCK], GPIO_AF_PUSHPULL);
		GPIO_void_PIN_MODE(SD_CARD_PORTS[SD_CARD_CS],SD_CARD_PINS[SD_CARD_CS], GPIO_OUTPUT_PUSHPULLUP);

		for(int i = 0;i<2;i++)
		{
			// need to replace to more general
			GPIO_void_PIN_MODE(SD_CARD_PORTS[i],SD_CARD_PINS[i], GPIO_AF_PUSHPULLUP); // must pulled high
			GPIO_void_AF_MODE(SD_CARD_PORTS[i], SD_CARD_PINS[i], GPIO_AF_SPI4);

		}

		break;
	}

	// save the spi bouderate to return back after init sd card
	SPI_ID* SPI_data= (SPI_ID*)(SPI_PER_NUMER);


	u32 SPI_PREVIOUS_INFO = SPI_void_GETBAUDRATE( SPI_PER_NUMER) ;


	// config the spi to the sd card to be between 100k --- 400k
	for(u64 i = 0,j = 2 ; i <=7;i++)
	{

		if( 300*1000 > (AHB1_CLOCK_SOURCE/j) && (AHB1_CLOCK_SOURCE/j) > 100*1000)
		{
			SPI_void_SETBAUDRATE(SPI_PER_NUMER, i);
			break;
		}
		j = j*2;

	}


	u8 RES1 = 0xFF; // response R1 from sd card most time be 0x01 or 0x00 any thing else is error
	u8 RES7 [10] ; // the most important one that make the init work

	SD_CARD_ID SD_CARD = { SPI_PER_NUMER,
			SD_CARD_PORTS[SD_CARD_MOSI],SD_CARD_PINS[SD_CARD_MOSI],
			SD_CARD_PORTS[SD_CARD_MISO],SD_CARD_PINS[SD_CARD_MISO],
			SD_CARD_PORTS[SD_CARD_SCK],SD_CARD_PINS[SD_CARD_SCK],
			SD_CARD_PORTS[SD_CARD_CS],SD_CARD_PINS[SD_CARD_CS],
			{0},
			0,
			SD_CARD_VER2_BYTE_ADRESS,
	};

	Stack_Struct_init(&SD_CARD.HW_ErrorStack, SD_CARD_ERROR_LOG_ARRAY_SIZE, u8_Type);


	SD_CARD_DISABLE_CS(&SD_CARD);
	Delay_ms(1);
	// dummy clocks to make the sd card init (th sd card do not have internal clock)
	for(u8 i = 0;i<10;i++ )
	{
		SD_CARD_void_SPI_SEND(&SD_CARD, 0xFF);
	}
	Delay_ms(1);
	SD_CARD_ENABLE_CS(&SD_CARD);
	// RES1 must be = 0x01


	u32 RES_response[1] = {0x01};

	// some clocks so the sd card can manage internal operation
	SD_CARD_void_SPI_SEND(&SD_CARD, 0xFF);


	//------------------------------------------------------------------

	SD_CARD_void_SEND_COMMAND(&SD_CARD, CMD0, 0x00);
	RES1 = SD_CARD_u8_RES_WAIT(&SD_CARD,(u32*)RES_response,1,5000);

	if (RES1 == R1_WAIT_ERROR)
	{
		SD_CARD_PUSH_ERROR(&SD_CARD, SD_CARD_COMAND_0_ERORR);
		return SD_CARD;
	}

	// some clocks so the sd card can manage internal operation
	SD_CARD_void_SPI_SEND(&SD_CARD, 0xFF);


	//------------------------------------------------------------------
	// read OCR memory in sd card
	SD_CARD_void_SEND_COMMAND(&SD_CARD, CMD8, 0x1AA);
	RES1 = SD_CARD_u8_RES_WAIT(&SD_CARD,(u32[]){0x01,0x04},1,5000);
	if(RES1 == R1_WAIT_ERROR)
	{
		SD_CARD_PUSH_ERROR(&SD_CARD, R1_WAIT_ERROR);
	}
	RES7[0] = SD_CARD_u8_RES_WAIT(&SD_CARD,(u32[]){0xaa,0x04},1,100000);
	//SD_CARD_void_RECEIVE_DATA(&SD_CARD, RES7, 10);
	if(RES7[0] != 0xaa) // Hard error
	{
		SD_CARD_PUSH_ERROR(&SD_CARD, SD_CARD_COMAND_8_ERORR);
		return SD_CARD;
	}

	//------------------------------------------------------------------
	// check the sd card type (for now we are using sd card v2 only)
	RES1 = 0xFF;
	u32 time_out = 0;

	while((RES1 == 0xFF || RES1 == 0x01) && time_out != 1000)
	{
		SD_CARD_void_SEND_COMMAND(&SD_CARD, CMD55, 0x00);
		RES1 = SD_CARD_u8_RES_WAIT(&SD_CARD,(u32[]){0x01},1,5000);
		SD_CARD_void_SEND_COMMAND(&SD_CARD, ACMD41, 0x40000000);
		RES1 = SD_CARD_u8_RES_WAIT(&SD_CARD,(u32[]){0x00},1,5000);
		time_out++;
	}

	if(time_out == 1000)
	{
		SD_CARD_PUSH_ERROR(&SD_CARD, SD_CARD_COMAND_55_ERORR);
		return SD_CARD;
	}

	//------------------------------------------------------------------

	if(RES1 == 0x00)
	{
		SD_CARD_void_SEND_COMMAND(&SD_CARD, CMD58, 0x00000000);
		RES1 = SD_CARD_u8_RES_WAIT(&SD_CARD,(u32[]){0x00},1,5000);
		SD_CARD_void_RECEIVE_DATA(&SD_CARD, RES7, 4);
	}

	if( RES7[0] != 0xc0 && RES7[1] != 0xc0 ) // byte adress force it to block adress mode
	{
		SD_CARD_void_SEND_COMMAND(&SD_CARD, CMD16, 512);
		SD_CARD.SD_CARD_VERSION = SD_CARD_VER2_BYTE_ADRESS;
	}
	else // it is block adress mode
	{
		SD_CARD.SD_CARD_VERSION = SD_CARD_VER2_BLOCK_ADRESS;
	}

	//------------------------------------------------------------------

	SD_CARD_DISABLE_CS(&SD_CARD);
	SPI_void_SETBAUDRATE(SPI_PER_NUMER, SPI_PREVIOUS_INFO);


	return SD_CARD;

}

