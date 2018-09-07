/*
 * USART_Driver.c
 *
 *  Created on: Jan 31, 2018
 *      Author: zsolt.balo
 */

#include "USART_Driver.h"
#include "USART_Driver_Cfg.h"

void USART_Driver_Init(USART_TypeDef* USARTx)
{
	#if (USART_DRIVER_USART1_SELECT != NOK)
		RCC->APB2ENR|=RCC_APB2ENR_USART1EN;
	#endif

	#if (USART_DRIVER_USART2_SELECT != NOK)
		RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
	#endif

	#if (USART_DRIVER_USART3_SELECT != NOK)
		RCC->APB1ENR|=RCC_APB1ENR_USART3EN;
	#endif

	#if (USART_DRIVER_USART4_SELECT != NOK)
		RCC->APB1ENR|=RCC_APB1ENR_UART4EN;
	#endif

	#if (USART_DRIVER_USART5_SELECT != NOK)
		RCC->APB1ENR|=RCC_APB1ENR_UART5EN;
	#endif

	#if (USART_DRIVER_USART6_SELECT != NOK)
		RCC->APB2ENR|=RCC_APB2ENR_USART6EN;
	#endif

	USARTx->CR1 |=(USART_DRIVER_OVERSAMPLING<<0x0F)
				|(USART_DRIVER_WORD_LENGTH<<0x0C)
				|(USART_DRIVER_PARITY_CONTROL_ENABLE<<0x0A);

	#if (USART_DRIVER_PARITY_CONTROL_ENABLE == OK)
		USARTx->CR1 |=(USART_DRIVER_PARITY_SELECTION<<0x09);
	#endif

	USARTx->CR1 |=(USART_DRIVER_TRANSMITTER_ENABLE<<0x03)|(USART_DRIVER_RECEIVER_ENABLE<<0x02);

	USARTx->CR2 |=(USART_DRIVER_STOP_BIT_SELECT<<0x0C);
	#if(USART_DRIVER_HALF_DUPLEX_SELECTION == OK)
		USARTx->CR3 |=(0x01<<0x03);
	#endif
}

void  USART_Driver_Set_Baudrate(USART_TypeDef* USARTx)
{
		uint16_t MANTISA = 0;
		uint8_t FRACTION = 0;
		uint32_t tmp = 0;

		uint32_t result = 0;
		#if (USART_DRIVER_OVERSAMPLING == USART_DRIVER_OVERSAMPLING_BY_16 )
			tmp = (((25*(USART_DRIVER_WORKING_FREQUENCY_2))/USART_DRIVER_BAUDRATE)/4);
		#else
			tmp = (((25*(USART_DRIVER_WORKING_FREQUENCY_2))/USART_DRIVER_BAUDRATE)/2);
		#endif
		//to double precision
		MANTISA = ((tmp/100)<<4);
		//truchate the fraction, move the integer left to left space for the new fraction
		tmp = tmp - ((MANTISA>>4)*100);
		//to get the fraction shift back the last value and multiply back,
		// then save the difference got by subtracting from the old one
		#if (USART_DRIVER_OVERSAMPLING == USART_DRIVER_OVERSAMPLING_BY_16 )
			FRACTION = ((((tmp*16)+50)/100)&((uint8_t)0x0F));
		#else
			FRACTION = ((((tmp*8)+50)/100)&((uint8_t)0x07));
		#endif
		//\100 with the multiplication at the begining the value had been modified, it had to be turned back
		//+50 is used for rounding up
		//Multiply with the available maximum value of the fraction part of the BRR
		result = MANTISA|FRACTION;

		USARTx->BRR = result;
}

uint8 USART_Driver_Receive_Char(USART_TypeDef* USARTx)
{
	uint8 Payload=0x00;
	while((USART_Driver_GetStatus(USARTx,USART_Driver_RXNE))==FAILED);
	Payload = USARTx->DR;
	return Payload;
}

void USART_Driver_Send_Char(USART_TypeDef* USARTx,uint8 data)
{
	USARTx->DR = data;
	while((USART_Driver_GetStatus(USARTx,USART_Driver_TXE))==FAILED);
}

void USART_Driver_Send_Str(USART_TypeDef* USARTx,char* Msg)
{
	uint8 index = 0x00;
	while(Msg[index])
	{
		USART_Driver_Send_Char(USARTx,Msg[index]);
		index++;
	}
}

void USART_Driver_Start(USART_TypeDef* USARTx)
{
	USARTx->CR1|=(0x01<<0x0D);
}

void USART_Driver_Stop(USART_TypeDef* USARTx)
{
	USARTx->CR1 &= (~(0x01<<0x0D));
}

uint8 USART_Driver_GetStatus(USART_TypeDef* USARTx,uint8 Status_Bit)
{
	if((USARTx->SR & Status_Bit)!=FALSE)
	{
		return SUCCES;
	}
	else
	{
		return FAILED;
	}
}
