/*
 * bravoLedTask.c
 *
 *  Created on: Apr 4, 2020
 *      Author: Nick Nifontov
 */

#ifndef SRC_BRAVOINV_BRAVOLEDTASK_C_
#define SRC_BRAVOINV_BRAVOLEDTASK_C_

#include "bravoLedTask.h"

qTask_t LedTask;

// ****** LED Task ****** //
void LedTask_Callback(qEvent_t e)
{
			switch (bravoSTATE) {
					case AC:
					case NOAC:
						qTask_Set_Time(&LedTask,0.5);
						break;
					case SD:
						qTask_Set_Time(&LedTask,0.2);
						break;
					case BOOT:
					case FLT:
						qTask_Set_Time(&LedTask,0.05);
						break;
			}

			if (bravoSTATE==AC) {
				LL_GPIO_ResetOutputPin(GPIOC, LED_SD_Pin);
			} else {
				LL_GPIO_TogglePin(GPIOC, LED_SD_Pin);
			}
}
// ******************************* //

#endif /* SRC_BRAVOINV_BRAVOLEDTASK_C_ */
