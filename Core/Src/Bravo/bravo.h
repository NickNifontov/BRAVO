/*
 * bravo.h
 *
 *  Created on: Mar 27, 2020
 *      Author: Nick Nifontov
 */

#ifndef SRC_BRAVO_BRAVO_H_
#define SRC_BRAVO_BRAVO_H_

#include "bravo_inc.h"
#include "bravo_sinus.h"

// *** GLOBAL ***//
extern volatile enum BRAVO_STATE stateBRAVO;
extern volatile enum BRAVO_WAVE_50HZ waveBRAVO;
extern volatile uint16_t waveindBRAVO;

extern volatile uint32_t PULSE_B[1];

// *** RTOS *** //
extern qTask_t LedTask, FirstRunTask;

void CheckPerek(void);
void HRTIM_FLT_StartTask_Callback(void);
void HRTIM_FLT_StopTask_Callback(void);

void IdleTask_Callback(qEvent_t e);
void LedTask_Callback(qEvent_t e);
void FirstRunTask_Callback(qEvent_t e);

// *** BRAVO *** //
void BRAVO_Init(void);
void BRAVO_Run(void);
void BRAVO_MRep(void);
void BRAVO_Init_VDac(void);

// *** VCC API *** //
void VCC15V_ON(void);
void VCC15V_OFF(void);

// *** DRV API *** //
void DRV_OFF(void);
void DRV_ON(void);

#endif /* SRC_BRAVO_BRAVO_H_ */
