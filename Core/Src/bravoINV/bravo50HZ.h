/*
 * bravo50HZ.h
 *
 *  Created on: Apr 4, 2020
 *      Author: Nick Nifontov
 */

#ifndef SRC_BRAVOINV_BRAVO50HZ_H_
#define SRC_BRAVOINV_BRAVO50HZ_H_

#include "bravoINC.h"

// ****** 50Hz API ****** //
#define MAX_50HZ_STATES 5 // 0..5

enum bravo50HZ_ {halfA1_50HZ, halfA2_50HZ, dtA_50HZ, halfB1_50HZ, halfB2_50HZ, dtB_50HZ};

extern volatile  uint8_t  MREP_Table[6];

extern volatile  enum bravo50HZ_ StateMachine_50hz[6];
extern volatile uint8_t StateMachine_50hz_Ind;

extern volatile uint8_t StateMachine_50hz_FirstRun;

void bravoInit50HZ(void);
void bravoMainTimerRep(void);
void bravoSetWave50HZ(void);
void bravoOFF50HZ(void);
void bravoSoftStartCalc(void);
// ******************************* //


#endif /* SRC_BRAVOINV_BRAVO50HZ_H_ */
