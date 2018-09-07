/*
 * RNG_Driver.h
 *
 *  Created on: Mar 2, 2018
 *      Author: zsolt.balo
 */

#ifndef RNG_DRIVER_H_
#define RNG_DRIVER_H_

#include "stm32f4xx.h"
#include "StdTypes.h"

#define RNG_DRIVER_NO_ERROR								0x00
#define RNG_DRIVER_CLOCK_ERROR							0x01
#define RNG_DRIVER_SEED_ERROR							0x02
#define RNG_DRIVER_DATA_READY_FLAG						0x01
#define RNG_DRIVER_CLOCK_ERROR_FLAG						0x02
#define RNG_DRIVER_SEED_ERROR_FLAG						0x04

/*Check if a clock or a seed error occurred */
uint8 RNG_Driver_Check_Error();
/*Clear the status register*/
void RNG_Driver_Clear_Status_Register();
/*Returns the new random number, if its correct*/
uint32 RNG_Driver_Get_Random_Number();
/*Init the RNG Driver*/
void RNG_Driver_Init();

#endif /* RNG_DRIVER_H_ */
