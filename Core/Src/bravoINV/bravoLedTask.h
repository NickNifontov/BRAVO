/*
 * bravoLedTask.h
 *
 *  Created on: Apr 4, 2020
 *      Author: Nick Nifontov
 */

#ifndef SRC_BRAVOINV_BRAVOLEDTASK_H_
#define SRC_BRAVOINV_BRAVOLEDTASK_H_

#include "bravoINC.h"

extern qTask_t LedTask;

// ****** LED Task ****** //
void LedTask_Callback(qEvent_t e);
// ******************************* //

#endif /* SRC_BRAVOINV_BRAVOLEDTASK_H_ */
