/*
 * bravo50HZ.c
 *
 *  Created on: Apr 4, 2020
 *      Author: Nick Nifontov
 */


#include "bravo50HZ.h"

// ****** 50Hz API ****** //
volatile  enum bravo50HZ_ StateMachine_50hz[6]={halfA1_50HZ, halfA2_50HZ, dtA_50HZ, halfB1_50HZ, halfB2_50HZ, dtB_50HZ};
volatile uint8_t  MREP_Table[6]={229,5,229,229,5,229};
volatile uint8_t StateMachine_50hz_Ind=5;

volatile uint8_t StateMachine_50hz_FirstRun=1;

void bravoSoftStartCalc(void) {
	if (USE_SOFTSTART==1) {
		SoftStart_CNT++;
		if (SoftStart_CNT>SOFTSTART_V_MAX_CNT) { // softstart complele
			USE_SOFTSTART=0;
			SoftStart_Coeff=SOFTSTART_START_COEF;
			SoftStart_CNT=0;
		} else {
			SoftStart_Coeff=(float)SoftStart_Coeff+(float)SOFTSTART_STEP; //calc new coeff
		}
	}
}

void bravoOFF50HZ(void){
	GPIOA->BRR=MCU_50HZ1_Pin|MCU_50HZ2_Pin;

	LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_1, 0);
	LL_DAC_TrigSWConversion(DAC1, LL_DAC_CHANNEL_1);
}

void bravoInit50HZ(void) {
	StateMachine_50hz_FirstRun=1;

	LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_1, 0);
    LL_DAC_TrigSWConversion(DAC1, LL_DAC_CHANNEL_1);

    bravoOutputOFF();
    bravoDrvOff();

	StateMachine_50hz_Ind=5;
	GPIOA->BRR=MCU_50HZ1_Pin|MCU_50HZ2_Pin;

	// DAC V
	bravoSinTableRep();
	SinInd=0;
}

void bravoMainTimerRep(void) {
	if (StateMachine_50hz_Ind>MAX_50HZ_STATES) {
		StateMachine_50hz_Ind=0;
	}

	HRTIM1->sMasterRegs.MREP=MREP_Table[StateMachine_50hz_Ind];

	if (StateMachine_50hz_FirstRun==0) {
		bravoSetWave50HZ();
	} else {
		StateMachine_50hz_FirstRun=0;
	}

	StateMachine_50hz_Ind++;
}

void bravoSetWave50HZ(void){
	if (StateMachine_50hz[StateMachine_50hz_Ind]==halfA1_50HZ) {
		bravoSoftStartCalc();
		SinInd=0;
	}

	switch (StateMachine_50hz[StateMachine_50hz_Ind]) {
		case halfA1_50HZ:
		case halfA2_50HZ:
			//LL_GPIO_ResetOutputPin(GPIOA, MCU_50HZ1_Pin);
			GPIOA->BRR=MCU_50HZ1_Pin;
			//LL_GPIO_SetOutputPin(GPIOA, MCU_50HZ2_Pin);
			GPIOA->BSRR=MCU_50HZ2_Pin;

			bravoOutputON();
			bravoDrvOn();
			break;
		case halfB1_50HZ:
		case halfB2_50HZ:
			//LL_GPIO_SetOutputPin(GPIOA, MCU_50HZ1_Pin);
			GPIOA->BSRR=MCU_50HZ1_Pin;
			//LL_GPIO_ResetOutputPin(GPIOA, MCU_50HZ2_Pin);
			GPIOA->BRR=MCU_50HZ2_Pin;

			bravoOutputON();
			bravoDrvOn();
			break;
		case dtA_50HZ:
		case dtB_50HZ:
			SinInd=0;

			//LL_GPIO_ResetOutputPin(GPIOA, MCU_50HZ1_Pin|MCU_50HZ2_Pin);
			GPIOA->BRR=MCU_50HZ1_Pin|MCU_50HZ2_Pin;

			//
			bravoOutputOFF();
			bravoDrvOff();
			break;
	}
}

// ******************************* //
