/*
 * bravo.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Nick Nifontov
 */


#include "bravo.h"

// *** GLOBAL ***//
volatile enum BRAVO_STATE stateBRAVO=BOOT;

// *** RTOS *** //
qTask_t LedTask, FirstRunTask;

void CheckPerek(void)
{
			if (LL_GPIO_IsInputPinSet(PEREK_GPIO_Port, PEREK_Pin)==SET) {
	        	stateBRAVO=AC;
	        	HRTIM_FLT_StopTask_Callback();
	        } else {
	        	stateBRAVO=NOAC;
	        	HRTIM_FLT_StartTask_Callback();
	        }
}

void HRTIM_FLT_StartTask_Callback(void)
{
		// Allow Driver
		DRV_ON();

		LL_HRTIM_TIM_CounterEnable(HRTIM1, LL_HRTIM_TIMER_MASTER);
}

void HRTIM_FLT_StopTask_Callback(void)
{
		// Disable Driver
		DRV_OFF();

		/* Stop HRTIM's  */
		LL_HRTIM_TIM_CounterDisable(HRTIM1, LL_HRTIM_TIMER_MASTER);
}

void FirstRunTask_Callback(qEvent_t e)
{
	qTask_Set_Time(qTask_Self(),3.0);
	switch (stateBRAVO) {
	    case FLT:
	    	stateBRAVO=NOAC;
	    	HRTIM_FLT_StartTask_Callback();
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
				stateBRAVO=NOAC;

				LL_HRTIM_EnableIT_FLT1(HRTIM1);
				LL_HRTIM_EnableIT_FLT2(HRTIM1);
				LL_HRTIM_EnableIT_SYSFLT(HRTIM1);

				CheckPerek();
			}
			break;
	}
}

void LedTask_Callback(qEvent_t e)
{
			switch (stateBRAVO) {
					case AC:
					case NOAC:
						qTask_Set_Time(&LedTask,1.0);
						break;
					case SD:
						qTask_Set_Time(&LedTask,0.2);
						break;
					case BOOT:
					case FLT:
						qTask_Set_Time(&LedTask,0.05);
						break;
			}

			switch (stateBRAVO) {
					case AC:
						LL_GPIO_ResetOutputPin(GPIOC, LED_SD_Pin);
						break;
					case NOAC:
					case FLT:
					case SD:
					case BOOT:
						LL_GPIO_TogglePin(GPIOC, LED_SD_Pin);
						break;
			}
}

void IdleTask_Callback(qEvent_t e)
{
	LL_IWDG_ReloadCounter(IWDG);
}


// *** BRAVO *** //
void BRAVO_Init(void) {
	// Default state
	VCC15V_OFF();
	DRV_OFF();

	qOS_Setup(NULL, TIMER_TICK, IdleTask_Callback);

	// LEDTAsk
	qOS_Add_Task(&LedTask, LedTask_Callback, qLowest_Priority, 1.0, qPeriodic, qEnabled, NULL);

	//FirstRunTask
	qOS_Add_Task(&FirstRunTask, FirstRunTask_Callback, qLowest_Priority, 3.0, qPeriodic, qEnabled, NULL);

	// Enable VCC
	VCC15V_ON();

	// SysTick Enable
	LL_SYSTICK_EnableIT();
}

void BRAVO_Run(void) {
	qOS_Run();
}

// *** VCC API *** //
void VCC15V_ON(void) {
	LL_GPIO_SetOutputPin(GPIOB, VCC_15V_Pin|VCC_15B_Pin); // ON VCC 15V
}

void VCC15V_OFF(void) {
	LL_GPIO_ResetOutputPin(GPIOB, VCC_15V_Pin|VCC_15B_Pin);  // OFF VCC 15V
}
// *** DRV API *** //
void DRV_OFF(void) {
		LL_GPIO_ResetOutputPin(GPIOB, DRV_SD_EX_Pin); //  OFF EXT DRV UNBLOCK
		LL_GPIO_SetOutputPin(GPIOB, DRV_SD_IN_Pin); // OFF INT DRV UNBLOCK
}

void DRV_ON(void) {
	 	LL_GPIO_SetOutputPin(GPIOB, DRV_SD_EX_Pin); // ON EXT DRV UNBLOCK
	 	LL_GPIO_ResetOutputPin(GPIOB, DRV_SD_IN_Pin); // ON INT DRV UNBLOCK
}
