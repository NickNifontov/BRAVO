/*
 * bravoFirstRunTask.h
 *
 *  Created on: Apr 4, 2020
 *      Author: Nick Nifontov
 */

#ifndef SRC_BRAVOINV_BRAVOFIRSTRUNTASK_H_
#define SRC_BRAVOINV_BRAVOFIRSTRUNTASK_H_

#include "bravoINC.h"

extern qTask_t FirstRunTask;

// ****** FirstRun Task ****** //
void FirstRunTask_Callback(qEvent_t e);
// ******************************* //


#endif /* SRC_BRAVOINV_BRAVOFIRSTRUNTASK_H_ */
