/*
 * bravoFirstRunTask.c
 *
 *  Created on: Apr 4, 2020
 *      Author: Nick Nifontov
 */

#include "bravoFirstRunTask.h"

qTask_t FirstRunTask;

// ****** FirstRun Task ****** //
void FirstRunTask_Callback(qEvent_t e)
{
	qTask_Set_Time(qTask_Self(),3.0);
	switch (bravoSTATE) {
	    case FLT:
	    	bravoSTATE=NOAC;
	    	bravoFltStartTask();
	    	break;
		case SD:
		case NOAC:
		case AC:
			qTask_Suspend(qTask_Self());
			break;
		case BOOT:
			// check ALL Blocks

			// try to Start HRTIM
			if (0==0) {
				bravoSTATE=NOAC;

				// HRTIM interrupt init
				bravoHRTIMintInit();

				bravoCheckPerek();
			}
			break;
	}
}
// ******************************* //
