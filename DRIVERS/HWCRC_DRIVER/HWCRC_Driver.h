/*
 * HWCRC_Driver.h
 *
 *  Created on: 28 feb. 2018
 *      Author: Zsole
 */

#ifndef HWCRC_DRIVER_H_
#define HWCRC_DRIVER_H_

#include "stm32f4xx.h"
#include "StdTypes.h"

uint32 HWCRC_Driver_Calculate_CRC(uint32 data);
void HWCRC_Driver_Init();
void HWCRC_Driver_Reset();

#endif /* HWCRC_DRIVER_H_ */
