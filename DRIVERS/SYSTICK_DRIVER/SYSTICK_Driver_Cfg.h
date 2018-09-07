/*
 * SYSTICK_Driver_Cfg.h
 *
 *  Created on: May 3, 2018
 *      Author: zsolt.balo
 */

#ifndef DRIVERS_SYSTICK_DRIVER_SYSTICK_DRIVER_CFG_H_
#define DRIVERS_SYSTICK_DRIVER_SYSTICK_DRIVER_CFG_H_

#include "SYSTICK_Driver.h"

#define SYSTICK_DRIVER_ENABLE_INTERRUPT					OK
/*For delays with a specified time interval use the CPU frequency as a reference (72000 for 1ms for ex.)*/
#define SYSTICK_DRIVER_SELECTED_LOAD 					SYSTICK_DRIVER_LOAD

#if(SYSTICK_DRIVER_LOAD>0xFFFFFF)
	#error "The configured value for the Systick Load is too big. It should be less then 0xFFFFFF"
#endif

#endif /* DRIVERS_SYSTICK_DRIVER_SYSTICK_DRIVER_CFG_H_ */
