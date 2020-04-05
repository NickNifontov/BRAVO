/*
 * bravoGLOBAL.c
 *
 *  Created on: Apr 4, 2020
 *      Author: Nick Nifontov
 */

#include "bravoGLOBAL.h"

// ****** System API ****** //
void bravoInitCOMP(void) {
	/* Enable comparator */
	LL_COMP_Enable(COMP2);
}

void bravoCheckPerek(void) {
	if (bravoSTATE!=BOOT) {
			if (LL_GPIO_IsInputPinSet(PEREK_GPIO_Port, PEREK_Pin)==SET) {
				bravoSTATE=AC;
	        	bravoFltStopTask();
	        } else {
	        	bravoSTATE=NOAC;
	        	bravoFltStartTask();
	        }
	}
}

void bravoFltStartTask(void)
{
		// Allow Driver
	    bravoDrvOn();

		// reset Wave
	    bravoInit50HZ();

		LL_HRTIM_EnableOutput(HRTIM1, LL_HRTIM_OUTPUT_TA1 | LL_HRTIM_OUTPUT_TC1);

		LL_HRTIM_TIM_CounterEnable(HRTIM1, LL_HRTIM_TIMER_MASTER | LL_HRTIM_TIMER_A | LL_HRTIM_TIMER_E
				| LL_HRTIM_TIMER_C | LL_HRTIM_TIMER_D);
}

void bravoFltStopTask(void)
{
		// Disable Driver
		bravoDrvOff();

		/* Stop HRTIM's  */
		LL_HRTIM_DisableOutput(HRTIM1, LL_HRTIM_OUTPUT_TA1 | LL_HRTIM_OUTPUT_TC1);

		LL_HRTIM_TIM_CounterDisable(HRTIM1, LL_HRTIM_TIMER_MASTER | LL_HRTIM_TIMER_A | LL_HRTIM_TIMER_E
				| LL_HRTIM_TIMER_C | LL_HRTIM_TIMER_D);

		bravoOFF50HZ();
}
// ******************************* //


// ****** HRTIM INT ****** //
void bravoHRTIMintInit(void){
	LL_HRTIM_EnableIT_FLT1(HRTIM1);
	LL_HRTIM_EnableIT_FLT2(HRTIM1);
	LL_HRTIM_EnableIT_SYSFLT(HRTIM1);

	/* Master - Enable repetition interrupt */
	LL_HRTIM_EnableIT_REP(HRTIM1, LL_HRTIM_TIMER_MASTER);

	LL_HRTIM_EnableIT_REP(HRTIM1, LL_HRTIM_TIMER_E);
	LL_HRTIM_EnableIT_CMP1(HRTIM1, LL_HRTIM_TIMER_E);
	LL_HRTIM_EnableIT_CMP2(HRTIM1, LL_HRTIM_TIMER_E);
	LL_HRTIM_EnableIT_CMP3(HRTIM1, LL_HRTIM_TIMER_E);
	LL_HRTIM_EnableIT_CMP4(HRTIM1, LL_HRTIM_TIMER_E);

	LL_HRTIM_EnableIT_CPT1(HRTIM1, LL_HRTIM_TIMER_D);
	LL_HRTIM_EnableIT_CPT2(HRTIM1, LL_HRTIM_TIMER_D);
}
// ******************************* //


// ****** BRAVO Global API ****** //

void bravoOutputOFF(void){
	HRTIM1->sCommonRegs.ODISR = HRTIM_ODISR_TA1ODIS  + HRTIM_ODISR_TC1ODIS;
}


void bravoOutputON(void){
	HRTIM1->sCommonRegs.OENR = HRTIM_OENR_TA1OEN  + HRTIM_OENR_TC1OEN;
}


void bravoInit(void) {

	// DAC Init
	bravoDacInit();


	// Default state
	bravoVccOff();
	bravoDrvOff();

	/* Enable comparator */
	bravoInitCOMP();

	qOS_Setup(NULL, TIMER_TICK, IdleTask_Callback);

	// LEDTAsk
	qOS_Add_Task(&LedTask, LedTask_Callback, qLowest_Priority, 1.0, qPeriodic, qEnabled, NULL);

	//FirstRunTask
	qOS_Add_Task(&FirstRunTask, FirstRunTask_Callback, qLowest_Priority, 3.0, qPeriodic, qEnabled, NULL);

	// Enable VCC
	bravoVccOn();

	// SysTick Enable
	LL_SYSTICK_EnableIT();
}

void bravoRun(void) {
	qOS_Run();
}
// ******************************* //



// ****** VCC API ****** //
void bravoVccOn(void) {
	//LL_GPIO_SetOutputPin(GPIOB, VCC_15V_Pin|VCC_15B_Pin); // ON VCC 15V
	GPIOB->BSRR=VCC_15V_Pin|VCC_15B_Pin;
}

void bravoVccOff(void) {
	//LL_GPIO_ResetOutputPin(GPIOB, VCC_15V_Pin|VCC_15B_Pin);  // OFF VCC 15V
	GPIOB->BRR=VCC_15V_Pin|VCC_15B_Pin;
}
// ******************************* //


// ****** DRV API ****** //
void bravoDrvOff(void) {
		//LL_GPIO_ResetOutputPin(GPIOB, DRV_SD_EX_Pin); //  OFF EXT DRV UNBLOCK
		//LL_GPIO_SetOutputPin(GPIOB, DRV_SD_IN_Pin); // OFF INT DRV UNBLOCK

		GPIOB->BRR=DRV_SD_EX_Pin;
		GPIOB->BSRR=DRV_SD_IN_Pin;
}

void bravoDrvOn(void) {
	 	//LL_GPIO_SetOutputPin(GPIOB, DRV_SD_EX_Pin); // ON EXT DRV UNBLOCK
	 	//LL_GPIO_ResetOutputPin(GPIOB, DRV_SD_IN_Pin); // ON INT DRV UNBLOCK

	 	GPIOB->BSRR=DRV_SD_EX_Pin;
	 	GPIOB->BRR=DRV_SD_IN_Pin;
}
// ******************************* //


// ****** DAC API ****** //
void bravoDacInit(void)
{
	      LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_1);
	      LL_DAC_EnableTrigger(DAC1, LL_DAC_CHANNEL_1);

	      LL_DAC_Enable(DAC2, LL_DAC_CHANNEL_1);
	      LL_DAC_SetTriggerSource(DAC2, LL_DAC_CHANNEL_1, LL_DAC_TRIG_SOFTWARE);
	      LL_DAC_EnableTrigger(DAC2, LL_DAC_CHANNEL_1);

	      LL_DAC_ConvertData12RightAligned(DAC2, LL_DAC_CHANNEL_1, DAC_CUR_LEVEL);

	      LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_1, 0);
	      LL_DAC_TrigSWConversion(DAC1, LL_DAC_CHANNEL_1);

}
// ******************************* //


/*void BRAVO_ARep(void)
{
	//start or overoll
	if (pulseindBRAVO==0) {
		PulseType=0; // Set Pulse to 0, we plan to start from Left

		PulseDuty=MAX_PULSE; // we plan to 100% pulse, reset Value
		HRTIM1->sTimerxRegs[0].CMP2xR=PulseDuty;
		HRTIM1->sTimerxRegs[2].CMP1xR=PulseDuty;

		DRV_ON(); // DRV ON
		HRTIM1->sCommonRegs.OENR = HRTIM_OENR_TA1OEN + HRTIM_OENR_TC1OEN; // Enable A+B
	}

	if  (pulseindBRAVO>=WAVE_DT_PULSES_R)  {
		LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_1, 0);

		//LL_GPIO_ResetOutputPin(GPIOA, MCU_50HZ1_Pin|MCU_50HZ2_Pin);
		GPIOA->BRR=MCU_50HZ1_Pin;
		GPIOA->BRR=MCU_50HZ2_Pin;

		DRV_OFF(); // DRV OFF
		HRTIM1->sCommonRegs.ODISR = HRTIM_ODISR_TA1ODIS  + HRTIM_ODISR_TC1ODIS; // Disable output


	} else {
		LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_1, Sin_Etalon[pulseindBRAVO]);

		if (PulseType==1) {
			PulseType=0;
			HRTIM1->sCommonRegs.ODISR = HRTIM_ODISR_TA1ODIS;//Disable A
			HRTIM1->sCommonRegs.OENR = HRTIM_OENR_TC1OEN; // Enable A
		} else {
			PulseType=1;
			HRTIM1->sCommonRegs.OENR = HRTIM_OENR_TA1OEN; // Enable A
			HRTIM1->sCommonRegs.ODISR = HRTIM_ODISR_TC1ODIS;//Disable B
		}

		HRTIM1->sTimerxRegs[0].CMP2xR=MAX_PULSE;
		HRTIM1->sTimerxRegs[2].CMP2xR=MAX_PULSE;

	}

	LL_DAC_TrigSWConversion(DAC1, LL_DAC_CHANNEL_1);

	if (pulseindBRAVO>=WAVE_PARTS) {
		pulseindBRAVO=0;
	} else {
		pulseindBRAVO++;
	}

}*/
