/*
 * GPIO_Driver.c
 *
 *  Created on: Jan 10, 2018
 *      Author: zsolt.balo
 */

#include "GPIO_Driver_Cfg.h"

/*Initialize the selected GPIO modules*/
void GPIO_Driver_Init()
{
	uint16 index = 0x00;
	uint16 index1 = 0x00;

	/*Enable the selected peripheral's clock signal*/

	#if GPIO_DRIVER_GPIOA!=FALSE
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
	#endif
	#if GPIO_DRIVER_GPIOB!=FALSE
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;
	#endif
	#if GPIO_DRIVER_GPIOC!=FALSE
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;
	#endif
	#if GPIO_DRIVER_GPIOD!=FALSE
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;
	#endif
	#if GPIO_DRIVER_GPIOE!=FALSE
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOEEN;
	#endif
	#if GPIO_DRIVER_GPIOF!=FALSE
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOFEN;
	#endif
	#if GPIO_DRIVER_GPIOG!=FALSE
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOGEN;
	#endif
	#if GPIO_DRIVER_GPIOH!=FALSE
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOHEN;
	#endif
	#if GPIO_DRIVER_GPIOI!=FALSE
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOIEN;
	#endif
	#if GPIO_DRIVER_GPIOJ!=FALSE
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOJEN;
	#endif
	#if GPIO_DRIVER_GPIOK!=FALSE
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIOKEN;
	#endif

	for(index=0x00;index<GPIO_DRIVER_INSTANCE_NUM;index++)
	{
		for(index1=0x00;index1<GPIO_SETUP[index].GPIO_Pin_nr;index1++)
		{

			/*The first step is to clear the default setting*/

			GPIO_SETUP[index].GPIO_Port->MODER   &=(~(((uint32_t)0x03)<<(2*(GPIO_SETUP[index].GPIO_Pins[index1]))));
			GPIO_SETUP[index].GPIO_Port->OSPEEDR &=(~(((uint32_t)0x03)<<(2*(GPIO_SETUP[index].GPIO_Pins[index1]))));
			GPIO_SETUP[index].GPIO_Port->PUPDR   &=(~(((uint32_t)0x03)<<(2*(GPIO_SETUP[index].GPIO_Pins[index1]))));
			GPIO_SETUP[index].GPIO_Port->OTYPER  &=(~(((uint32_t)0x01)<<(GPIO_SETUP[index].GPIO_Pins[index1])));

			/*Set the GPIO configuration*/

			GPIO_SETUP[index].GPIO_Port->MODER   |=(((uint32_t)GPIO_SETUP[index].GPIO_Pin_Mode[index1])<<(2*(GPIO_SETUP[index].GPIO_Pins[index1])));
			GPIO_SETUP[index].GPIO_Port->OSPEEDR |=(((uint32_t)GPIO_SETUP[index].GPIO_Pin_Speed[index1])<<(2*(GPIO_SETUP[index].GPIO_Pins[index1])));
			GPIO_SETUP[index].GPIO_Port->PUPDR   |=(((uint32_t)GPIO_SETUP[index].GPIO_Pin_PuPd[index1])<<(2*(GPIO_SETUP[index].GPIO_Pins[index1])));
			GPIO_SETUP[index].GPIO_Port->OTYPER  |=(((uint32_t)GPIO_SETUP[index].GPIO_Pin_Type[index1])<<(GPIO_SETUP[index].GPIO_Pins[index1]));
		}
	}
}

/*Set the selected pin to 1*/
void GPIO_Driver_SetPin(GPIO_TypeDef* GPIOx,uint16 Pin)
{
	GPIOx->BSRRL|=(1<<Pin);
}

/*Clear the selected pin*/
void GPIO_Driver_ClearPin(GPIO_TypeDef* GPIOx,uint16 Pin)
{
	GPIOx->BSRRH|=(1<<Pin);
}

/*Read the value of the input data (the value of all the bits)*/
uint16 GPIO_Driver_ReadInputData(GPIO_TypeDef* GPIOx)
{
	uint16 result = 0x00;
	result = ((uint16)(GPIOx->IDR));
	return result;
}

/*Read the value of the input data (the value of only one bit)*/
uint8 GPIO_Driver_ReadInputDataBit(GPIO_TypeDef* GPIOx,uint16 Bit_number)
{
	uint16 input = 0x00;
	uint8 result = 0x00;

	input  = ((uint16)(GPIOx->IDR));
	result = ((input&Bit_number)!=0x00) ? 1 : 0;
	return result;
}

/*Read the value of the output data register(the value of all the bits)*/
uint16 GPIO_Driver_ReadOutputData(GPIO_TypeDef* GPIOx)
{
	uint16 result = 0x00;
	result = ((uint16)(GPIOx->ODR));
	return result;
}

void GPIO_Driver_SetAlternateFunction(GPIO_TypeDef* GPIOx,uint16_t Pin_number,uint8 Alternate_Function)
{
	if(Pin_number<0x08)
	{
		GPIOx->AFR[0]|= (Alternate_Function<<(4*Pin_number));
	}
	else
	{
		GPIOx->AFR[1]|= (Alternate_Function<<(4*(Pin_number-8)));
	}
}
