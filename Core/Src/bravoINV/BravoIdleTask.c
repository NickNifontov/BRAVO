/*
 * BravoIdleTask.c
 *
 *  Created on: Apr 4, 2020
 *      Author: Nick Nifontov
 */

#include "bravoIdleTask.h"

// ****** IDLE Task ****** //
void IdleTask_Callback(qEvent_t e) {
	LL_IWDG_ReloadCounter(IWDG);

	if (bravoSTATE!=NOAC) {
		LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_1, 0);
		LL_DAC_TrigSWConversion(DAC1, LL_DAC_CHANNEL_1);
	}
}
// ******************************* //
