/*
 * bravoINC.h
 *
 *  Created on: Apr 4, 2020
 *      Author: Nick Nifontov
 */

#ifndef SRC_BRAVOINV_BRAVOINC_H_
#define SRC_BRAVOINV_BRAVOINC_H_

// *** RTOS *** //
#include "QuarkTS.h"

// ****** GLOBAL PERIPH INC ****** //
#include "main.h"
#include "adc.h"
#include "comp.h"
#include "dac.h"
#include "dma.h"
#include "hrtim.h"
#include "iwdg.h"
#include "tim.h"
#include "gpio.h"
// ******************************* //

// ****** BRAVO INC ****** //
#include "bravoDefines.h"
#include "bravoGLOBAL.h"
#include "bravoPULSE.h"
#include "bravo50HZ.h"
#include "bravoIdleTask.h"
#include "bravoLedTask.h"
#include "bravoFirstRunTask.h"
#include "bravoSinTable.h"
// ******************************* //

#endif /* SRC_BRAVOINV_BRAVOINC_H_ */
