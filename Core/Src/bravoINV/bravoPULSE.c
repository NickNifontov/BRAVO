/*
 * bravoPULSE.c
 *
 *  Created on: Apr 5, 2020
 *      Author: Nick Nifontov
 */

#include "bravoPULSE.h"

// ****** PULSE API ****** //
volatile enum BRAVO_PULSE_TYPE_A pA=A_SEARCH;
volatile enum BRAVO_PULSE_TYPE_B pB=B_NORMAL;

volatile uint32_t pA_Duty=PULSE_A_MAX;
volatile uint32_t pB_Duty=PULSE_B_MAX;

uint32_t tempDuty=0;

void bravo_A_Cap_V(void){
	tempDuty=(uint32_t)(HRTIM1->sTimerxRegs[3].CPT1xR);
	if (tempDuty>=25100) {
		tempDuty=0;
	} else {
		if (tempDuty>PULSE_A_MAX) {
			tempDuty=PULSE_A_MAX;
		}
		if (tempDuty<PULSE_A_MIN) {
			tempDuty=PULSE_A_MIN;
		}
		tempDuty=25000+tempDuty;

		pB_Duty=tempDuty;
	}
}

void bravo_A_Cap_I(void){
	//
}

void bravoCalcA(void){
	// pre set
	pA_Duty=PULSE_A_MAX;
	pB_Duty=PULSE_B_MAX;
	tempDuty=0;

	// Set
	HRTIM1->sTimerxRegs[0].CMP2xR=pA_Duty;
}

void bravoCalcB(void){
	HRTIM1->sTimerxRegs[2].CMP2xR=pB_Duty;
}
// ******************************* //
