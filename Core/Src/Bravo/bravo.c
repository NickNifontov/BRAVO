/*
 * bravo.c
 *
 *  Created on: Mar 27, 2020
 *      Author: Nick Nifontov
 */


#include "bravo.h"

// *** GLOBAL ***//
volatile enum BRAVO_STATE stateBRAVO=BOOT;
volatile enum BRAVO_WAVE_50HZ waveBRAVO=AA;
volatile uint16_t waveindBRAVO=0;

volatile uint32_t NewDutyB=MIN_PULSE;
volatile uint32_t NewDutyA=MIN_PULSE;

volatile uint8_t Polka=0;

uint16_t tmp=0;

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

		// reset Wave
		Polka=0;
		waveindBRAVO=0;
		waveBRAVO=AA;
		LL_GPIO_ResetOutputPin(GPIOA, MCU_50HZ1_Pin|MCU_50HZ2_Pin);

		BRAVO_Init_VDac();

		LL_HRTIM_EnableOutput(HRTIM1, LL_HRTIM_OUTPUT_TA1 | LL_HRTIM_OUTPUT_TC1);

		LL_HRTIM_TIM_CounterEnable(HRTIM1, LL_HRTIM_TIMER_MASTER | LL_HRTIM_TIMER_A | LL_HRTIM_TIMER_C
				| LL_HRTIM_TIMER_E );
}

void HRTIM_FLT_StopTask_Callback(void)
{
		// Disable Driver
		DRV_OFF();

		// reset Wave
		Polka=0;
		waveindBRAVO=0;
		waveBRAVO=AA;
		LL_GPIO_ResetOutputPin(GPIOA, MCU_50HZ1_Pin|MCU_50HZ2_Pin);

		LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_1, 0);
		LL_DAC_TrigSWConversion(DAC1, LL_DAC_CHANNEL_1);

		/* Stop HRTIM's  */
		LL_HRTIM_DisableOutput(HRTIM1, LL_HRTIM_OUTPUT_TA1 | LL_HRTIM_OUTPUT_TC1);

		LL_HRTIM_TIM_CounterDisable(HRTIM1, LL_HRTIM_TIMER_MASTER | LL_HRTIM_TIMER_A | LL_HRTIM_TIMER_C
				| LL_HRTIM_TIMER_E );
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

				/* Master - Enable repetition interrupt */
				LL_HRTIM_EnableIT_REP(HRTIM1, LL_HRTIM_TIMER_MASTER);

				/* E - Enable CPT1 interrupt */
				LL_HRTIM_EnableIT_CPT1(HRTIM1, LL_HRTIM_TIMER_E);

				/* E - Enable CPT2 interrupt */
				//LL_HRTIM_EnableIT_CPT2(HRTIM1, LL_HRTIM_TIMER_E);

				/* D - Enable CPT1 interrupt */
				//LL_HRTIM_EnableIT_CPT1(HRTIM1, LL_HRTIM_TIMER_D);

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

	/* Enable comparator */
	LL_COMP_Enable(COMP2);

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

void BRAVO_DCPT1(void)
{
	Polka=1;
}

void BRAVO_ECPT2(void)
{
	NewDutyA=(uint32_t)(HRTIM1->sTimerxRegs[4].CPT2xR)-MAX_PULSE;
}

void BRAVO_ECPT1(void)
{
	NewDutyB=(uint32_t)(HRTIM1->sTimerxRegs[4].CPT1xR);
	HRTIM1->sTimerxRegs[2].CMP2xR=NewDutyB;
}

void BRAVO_MRep(void)
{

	//reset if overroll
	if (waveindBRAVO==0) {
		Polka=0;
		//
		DRV_ON();

		if (waveBRAVO==AA) {
			waveBRAVO=BB;
			LL_GPIO_ResetOutputPin(GPIOA, MCU_50HZ1_Pin);
			LL_GPIO_SetOutputPin(GPIOA, MCU_50HZ2_Pin);
		} else {
			waveBRAVO=AA;
			LL_GPIO_SetOutputPin(GPIOA, MCU_50HZ1_Pin);
			LL_GPIO_ResetOutputPin(GPIOA, MCU_50HZ2_Pin);
		}
	}

	if  (waveindBRAVO>=WAVE_DT_PULSES_R)  {
		LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_1, 0);

		LL_GPIO_ResetOutputPin(GPIOA, MCU_50HZ1_Pin|MCU_50HZ2_Pin);
		DRV_OFF();
	} else {
		LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_1, Sin_Etalon[waveindBRAVO]);

		NewDutyA=MAX_PULSE;
		HRTIM1->sTimerxRegs[0].CMP2xR=NewDutyA;
		HRTIM1->sTimerxRegs[2].CMP2xR=NewDutyB;
		//HRTIM1->sTimerxRegs[0].CMP2xR=(3400+(Sin_Etalon[waveindBRAVO]*21600)/3500);
		//
		/*tmp++;
		if (tmp>=20) {
			tmp=0;
		}
		if (tmp<10) {
			HRTIM1->sTimerxRegs[0].CMP2xR=10000;
		} else {
			HRTIM1->sTimerxRegs[0].CMP2xR=25000;
		}*/
	}

	LL_DAC_TrigSWConversion(DAC1, LL_DAC_CHANNEL_1);

	if (waveindBRAVO>=WAVE_PARTS) {
		waveindBRAVO=0;
	} else {
		waveindBRAVO++;
	}

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

// *** DAC *** //
void BRAVO_Init_VDac(void)
{
	/* Set DMA transfer addresses of source and destination */
	//LL_DMA_ConfigAddresses(DMA1,
	//                         LL_DMA_CHANNEL_3,
	//                         (uint32_t)&Sin_Etalon,
	//                         LL_DAC_DMA_GetRegAddr(DAC1, LL_DAC_CHANNEL_1, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED),
	//                         LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	/* Set DMA transfer size */
	 //LL_DMA_SetDataLength(DMA1,
	 //                      LL_DMA_CHANNEL_3,
	//					   WAVE_PARTS);

	 /* Enable DMA transfer interruption: transfer error */
	  // LL_DMA_EnableIT_TE(DMA1,
	 //                     LL_DMA_CHANNEL_3);

	 /* Enable the DMA transfer */
	  // LL_DMA_EnableChannel(DMA1,
	  //                      LL_DMA_CHANNEL_3);

	   /* Enable DAC channel DMA request */
	   //  LL_DAC_EnableDMAReq(DAC1, LL_DAC_CHANNEL_1);

	     /* Enable DAC channel */
	      LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_1);
	      LL_DAC_EnableTrigger(DAC1, LL_DAC_CHANNEL_1);

}
