/*
 * bravoDefines.h
 *
 *  Created on: Apr 4, 2020
 *      Author: Nick Nifontov
 */

#ifndef SRC_BRAVOINV_BRAVODEFINES_H_
#define SRC_BRAVOINV_BRAVODEFINES_H_

#include "bravoINC.h"

// ****** RTOS ****** //
#define TIMER_TICK 0.001 /* 1ms */
// ******************************* //

// ****** BRAVO ****** //
enum BRAVO_STATE {NOAC, AC, SD, BOOT, FLT};

extern volatile enum BRAVO_STATE bravoSTATE;
// ******************************* //


#endif /* SRC_BRAVOINV_BRAVODEFINES_H_ */
