/*
 * bravoGLOBAL.h
 *
 *  Created on: Apr 4, 2020
 *      Author: Nick Nifontov
 */

#ifndef SRC_BRAVOINV_BRAVOGLOBAL_H_
#define SRC_BRAVOINV_BRAVOGLOBAL_H_

#include "bravoINC.h"

// ****** System API ****** //
void bravoInitCOMP(void);
void bravoCheckPerek(void);
void bravoFltStartTask(void);
void bravoFltStopTask(void);
// ******************************* //

// ****** HRTIM INT ****** //
void bravoHRTIMintInit(void);
// ******************************* //

// ****** BRAVO Global API ****** //
void bravoInit(void);
void bravoRun(void);
void bravoOutputOFF(void);
void bravoOutputON(void);
// ******************************* //


// ****** VCC API ****** //
void bravoVccOn(void);
void bravoVccOff(void);
// ******************************* //


// ****** DRV API ****** //
void bravoDrvOn(void);
void bravoDrvOff(void);
// ******************************* //


// ****** DAC API ****** //
void bravoDacInit(void);
// ******************************* //


#endif /* SRC_BRAVOINV_BRAVOGLOBAL_H_ */
