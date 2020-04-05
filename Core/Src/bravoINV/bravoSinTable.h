/*
 * bravoSinTable.h
 *
 *  Created on: Apr 4, 2020
 *      Author: Nick Nifontov
 */

#ifndef SRC_BRAVOINV_BRAVOSINTABLE_H_
#define SRC_BRAVOINV_BRAVOSINTABLE_H_

#include "bravoINC.h"

// ****** SINUS ****** //
#define PULSE_IN_WAVE 467 // 0..460
#define RetrigVDac_Delta 100

#define DAC_CUR_LEVEL 3100
#define DAC_CUR_RETRIG_LEVEL 3200

// *** SOFT START SETTINGS *** //
#define SOFTSTART_V_MAX_CNT 100 // num of waves for softstart from 0.1 to 1.0
#define SOFTSTART_STEP	(float) (0.005)
#define SOFTSTART_START_COEF (float) (0.5)

// ******************************* //


// ****** Sin Table API ****** //
extern volatile uint8_t USE_SOFTSTART;
extern volatile float SoftStart_Coeff;
extern volatile uint8_t SoftStart_CNT;

extern volatile uint16_t SinInd;
extern volatile uint16_t Sin_Etalon[PULSE_IN_WAVE];

void bravoSinTableRep(void);
void bravoRetrigVDac(void);
void bravoRestoreIDac(void);
// ******************************* //

#endif /* SRC_BRAVOINV_BRAVOSINTABLE_H_ */
