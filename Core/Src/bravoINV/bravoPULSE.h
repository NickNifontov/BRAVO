/*
 * bravoPULSE.h
 *
 *  Created on: Apr 5, 2020
 *      Author: Nick Nifontov
 */

#ifndef SRC_BRAVOINV_BRAVOPULSE_H_
#define SRC_BRAVOINV_BRAVOPULSE_H_

#include "bravoINC.h"

// ****** PULSE DEF ****** //
enum BRAVO_PULSE_TYPE_A {A_SEARCH, A_CUR_BY_B, A_CUR_BY_A};
enum BRAVO_PULSE_TYPE_B {B_NORMAL, B_CUR_BY_B};
// ******************************* //


// ****** PULSE DEF ****** //
#define PULSE_A_MIN (uint16_t)(3400)
#define PULSE_A_MAX (uint16_t)(25000)

#define PULSE_B_MIN (uint16_t)(28400)
#define PULSE_B_MAX (uint16_t)(50000)
// ******************************* //

// ****** PULSE API ****** //
extern volatile enum BRAVO_PULSE_TYPE_A pA;
extern volatile enum BRAVO_PULSE_TYPE_B pB;

extern volatile uint32_t pA_Duty;
extern volatile uint32_t pB_Duty;

void bravoCalcA(void);
void bravoCalcB(void);

void bravo_A_Cap_V(void);
void bravo_A_Cap_I(void);
// ******************************* //

#endif /* SRC_BRAVOINV_BRAVOPULSE_H_ */
