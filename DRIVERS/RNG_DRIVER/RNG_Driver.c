/*
 * RNG_Driver.c
 *
 *  Created on: Mar 2, 2018
 *      Author: zsolt.balo
 */

#include "RNG_Driver.h"
#include "RNG_Driver_Cfg.h"

static uint32 RNG_Driver_Result = 0x00;

uint8 RNG_Driver_Check_Error() {
	uint8 Status_Value = RNG_DRIVER_NO_ERROR;

	if ((RNG->SR & RNG_DRIVER_CLOCK_ERROR_FLAG) != 0x00) {
		Status_Value = RNG_DRIVER_CLOCK_ERROR;
	}
	if ((RNG->SR & RNG_DRIVER_SEED_ERROR_FLAG) != 0x00) {
		Status_Value = RNG_DRIVER_SEED_ERROR;
	}

	return Status_Value;
}

void RNG_Driver_Clear_Status_Register() {
	RNG->SR = (uint32) 0x00;
}

static uint32 RNG_Driver_Get_Value() {
	if ((RNG_Driver_Check_Error() == RNG_DRIVER_NO_ERROR)
			&& (RNG_Driver_Check_Error() == RNG_DRIVER_NO_ERROR)
			&& (RNG->SR & RNG_DRIVER_DATA_READY_FLAG) != 0x00) {
		return (uint32) (RNG->DR);
	} else {
		return 0x00;
	}
}

void RNG_Driver_Init() {
#if (RNG_DRIVER_ENABLE == OK)
	RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
#endif
	/*As required by the FIPS PUB (Federal Information Processing Standard Publication) 140-2,
	 the first random number generated after setting the RNGEN bit should not be used, but
	 saved for comparison with the next generated random number.*/

	/*Enable the random number generator*/
	RNG->CR |= ((0x01) << (0x02));

	RNG_Driver_Result = RNG_Driver_Get_Value();

}

/*
 Each subsequent generated random number has to be compared with the previously generated number.
 The test fails if any two compared numbers are equal (continuous random number generator test).
 */

static uint8 RNG_Driver_Value_Check(uint32* Old_Value, uint32* New_Value) {
	uint32 tmp = 0x00;
	if (*Old_Value != *New_Value)
	{
		tmp = *Old_Value;
		*Old_Value = *New_Value;
		*New_Value = tmp;

		return SUCCES;
	} else {
		return FAILED;
	}

}

uint32 RNG_Driver_Get_Random_Number() {
	uint32 New_random_number = 0x00;
	New_random_number = RNG_Driver_Get_Value();
	if (RNG_Driver_Value_Check(&RNG_Driver_Result, &New_random_number)==SUCCES) {
		return RNG_Driver_Result;
	} else {
		return 0x00;
	}
}

