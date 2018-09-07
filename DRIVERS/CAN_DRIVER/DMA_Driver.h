/*
 * DMA_Driver.h
 *
 *  Created on: Aug 14, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_DMA_DRIVER_DMA_DRIVER_H_
#define DRIVERS_DMA_DRIVER_DMA_DRIVER_H_

#include "stm32f4xx.h"
#include "StdTypes.h"

#define DMA_DRIVER_NORMAL_MODE									(0x00)
#define DMA_DRIVER_CIRCULAR_MODE								(0x01)
#define DMA_DRIVER_CHANNEL_PRIORITY_LOW							(0x00<<0x10)
#define DMA_DRIVER_CHANNEL_PRIORITY_MEDIUM						(0x01<<0x10)
#define DMA_DRIVER_CHANNEL_PRIORITY_HIGH						(0x02<<0x10)
#define DMA_DRIVER_CHANNEL_PRIORITY_VERY_HIGH					(0x03<<0x10)
#define DMA_DRIVER_MEMMORY_SIZE_8_BITS							(0x00<<0x0D)
#define DMA_DRIVER_MEMMORY_SIZE_16_BITS                         (0x01<<0x0D)
#define DMA_DRIVER_MEMMORY_SIZE_32_BITS                         (0x02<<0x0D)
#define DMA_PERIPHERAL_SIZE_8_bits                              (0x00<<0x0B)
#define DMA_PERIPHERAL_SIZE_16_bits                             (0x01<<0x0B)
#define DMA_PERIPHERAL_SIZE_32_bits                             (0x02<<0x0B)
#define DMA_FIFO_THRESHOLD_1DIV4                             	(0x00)
#define DMA_FIFO_THRESHOLD_1DIV2                             	(0x01)
#define DMA_FIFO_THRESHOLD_3DIV4                             	(0x02)
#define DMA_FIFO_THRESHOLD_FULL                             	(0x03)
#define DMA_DRIVER_DIRECTION_FROM_PERIPHERAL					(0x00)
#define DMA_DRIVER_DIRECTION_FROM_MEMORY                        (0x01)
#define DMA_DRIVER_DIRECTION_MEMORY_TO_MEMORY                   (0x02)
#define DMA_DRIVER_BURST_TRANSFER_SINGLE_TRANSFER				(0x00)
#define DMA_DRIVER_BURST_TRANSFER_INCR4							(0x01)
#define DMA_DRIVER_BURST_TRANSFER_INCR8							(0x02)
#define DMA_DRIVER_BURST_TRANSFER_INCR16						(0x03)
#define DMA_DRIVER_REQ_CHANNEL_0								(0x00<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_1								(0x01<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_2								(0x02<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_3								(0x03<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_4								(0x04<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_5								(0x05<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_6								(0x06<<0x19)
#define DMA_DRIVER_REQ_CHANNEL_7								(0x07<<0x19)

void DMA_Driver_Init(DMA_Stream_TypeDef * DMA_Streamx);
void DMA_Driver_SetBuffers(DMA_Stream_TypeDef * DMA_Streamx,uint32* Tx_Buffer,uint32* Rx_Buffer);
void DMA_Driver_Start(DMA_Stream_TypeDef * DMA_Streamx);
void DMA_Driver_Stop(DMA_Stream_TypeDef * DMA_Streamx);


#endif /* DRIVERS_DMA_DRIVER_DMA_DRIVER_H_ */
