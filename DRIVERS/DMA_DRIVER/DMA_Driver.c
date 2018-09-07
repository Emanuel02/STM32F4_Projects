/*
 * DMA_Driver_Cfg.c
 *
 *  Created on: Aug 14, 2018
 *      Author: zsolt.balo
 */

#include "DMA_Driver_Cfg.h"

void DMA_Driver_Init(DMA_Stream_TypeDef * DMA_Streamx)
{
	/*	Initialization of the selected DMA*/
	/*	Enable the DMA in the AHB bus*/
		#if (DMA_DRIVER_DMA1 == OK)
			RCC->AHB1ENR|=RCC_AHB1ENR_DMA1EN;
		#endif

		#if (DMA_DRIVER_DMA2 == OK)
			RCC->AHB1ENR|=RCC_AHB1ENR_DMA2EN;
		#endif

	/*	Shut down the DMA before setup*/
		DMA_Driver_Stop(DMA_Streamx);

	/* 	Wait for the EN bit to be cleared before starting any stream configuration*/
		while((DMA_Streamx->CR & 0x01)!=0x00){}

	/*	Select the request channel*/
		DMA_Streamx->CR |= DMA_DRIVER_REQ_CHANNEL;

	/*	Memory burst mode configuration*/
	/*	In direct mode, these bits are forced to 0x0 by hardware as soon as bit EN= '1'*/
		DMA_Streamx->CR |= (DMA_DRIVER_MEMORY_BURST<<0x17);

	/*	Peripheral burst mode configuration*/
	/*	In direct mode, these bits are forced to 0x0 by hardware as soon as bit EN= '1'*/
		DMA_Streamx->CR |= (DMA_DRIVER_PERIPHERAL_BURST<<0x15);

	/*	Double buffer mode configuration*/
		#if(DMA_DRIVER_DUBLE_BUFFERING == OK)
			DMA_Streamx->CR |= (0x01<<0x12);
		#endif

	/*	DMA direction*/
	/*	When memory-to-memory mode is used, the Circular and direct modes are not allowed.
	  	Only the DMA2 controller is able to perform memory-to-memory transfers.*/
	  	#if(DMA_DRIVER_DIRECTION == DMA_DRIVER_DIRECTION_FROM_PERIPHERAL)
			DMA_Streamx->CR &= (~(0x11<<6));
		#elif(DMA_DRIVER_DIRECTION == DMA_DRIVER_DIRECTION_FROM_MEMORY)
			DMA_Streamx->CR |= (DMA_DRIVER_DIRECTION_FROM_MEMORY<<6);
		#elif(DMA_DRIVER_DIRECTION == DMA_DRIVER_DIRECTION_MEMORY_TO_MEMORY)
			DMA_Streamx->CR |= (DMA_DRIVER_DIRECTION_MEMORY_TO_MEMORY<<6);
		#endif

	/*	DMA running Mode*/
		#if((DMA_DRIVER_RUNNING_MODE == DMA_DRIVER_NORMAL_MODE) || (DMA_DRIVER_DIRECTION == DMA_DRIVER_DIRECTION_MEMORY_TO_MEMORY))
			DMA_Streamx->CR &= (~(0x01<<0x08));
		#elif(DMA_DRIVER_RUNNING_MODE == DMA_DRIVER_CIRCULAR_MODE)
			DMA_Streamx->CR |= (0x01<<0x08);
		#endif

	/*	DMA Channel priority*/
		DMA_Streamx->CR |= DMA_DRIVER_CHANNEL_PRIORITY;

	/*	DMA Memory size*/
		DMA_Streamx->CR |= DMA_DRIVER_MEMMORY_SIZE;

	/*	DMA Peripheral size*/
		DMA_Streamx->CR |= DMA_PERIPHERAL_SIZE;

	/*	DMA Memory increment mode*/
		#if(DMA_DRIVER_MEMMORY_INCREMENT == OK)
			DMA_Streamx->CR |= (0x01<<0x0A);
		#else
			DMA_Streamx->CR &= (~(0x01<<0x0A));
		#endif

	/*	DMA Peripheral increment mode*/
		#if(DMA_DRIVER_PERIPHERAL_INCREMENT == OK)
			DMA_Streamx->CR |= (0x01<<9);
		#else
			DMA_Streamx->CR &= (~(0x01<<9));
		#endif

	/*	DMA Tx count*/
		DMA_Streamx->NDTR = (uint16_t)DMA_DRIVER_TX_COUNT;

	/*	Set Direct mode disable*/
	/*	This bit is set by hardware if the memory-to-memory mode is selected (DIR bit in
		DMA_SxCR are “10”) and the EN bit in the DMA_SxCR register is ‘1’ because the direct
		mode is not allowed in the memory-to-memory configuration.*/
		#if((DMA_DRIVER_DIRECT_MODE == OK) && (DMA_DRIVER_DIRECTION != DMA_DRIVER_DIRECTION_MEMORY_TO_MEMORY))
			DMA_Streamx->FCR &= (~(0x01<<0x02));
		#else
			DMA_Streamx->FCR |= (0x01<<0x02);
		#endif

	/*	Set FIFO threshold*/
		DMA_Streamx->FCR &= (~(0x03));
		DMA_Streamx->FCR |= DMA_DRIVER_FIFO_THRESHOLD;

}
void DMA_Driver_SetBuffers(DMA_Stream_TypeDef * DMA_Streamx,uint32* Tx_Buffer,uint32* Rx_Buffer)
{
	#if(DMA_DRIVER_DIRECTION == DMA_DRIVER_DIRECTION_FROM_PERIPHERAL)

	/*	DMA Peripheral address*/
		DMA_Streamx->PAR = (uint32_t)(Tx_Buffer);

	/*	DMA Memory address*/
		DMA_Streamx->M0AR = (uint32_t)(Rx_Buffer);

	#elif(DMA_DRIVER_DIRECTION == DMA_DRIVER_DIRECTION_FROM_MEMORY)

	/*	DMA Peripheral address*/
		DMA_Streamx->PAR = (uint32_t)(Rx_Buffer);

	/*	DMA Memory address*/
		DMA_Streamx->M0AR = (uint32_t)(Tx_Buffer);

	#elif(DMA_DRIVER_DIRECTION == DMA_DRIVER_DIRECTION_MEMORY_TO_MEMORY)

	/*	DMA Peripheral address*/
		DMA_Streamx->PAR = (uint32_t)(Tx_Buffer);

	/*	DMA Memory address*/
		DMA_Streamx->M0AR = (uint32_t)(Rx_Buffer);
	#endif
}

void DMA_Driver_Start(DMA_Stream_TypeDef * DMA_Streamx)
{
	/*	DMA Mode -> Enable*/
		DMA_Streamx->CR |= (0x01);
}

void DMA_Driver_Stop(DMA_Stream_TypeDef * DMA_Streamx)
{
	/*	Shut down the DMA 	*/
		DMA_Streamx->CR &= (~(0x01));
}
