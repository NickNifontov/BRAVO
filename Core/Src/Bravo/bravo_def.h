/*
 * bravo_def.h
 *
 *  Created on: Mar 27, 2020
 *      Author: Nick Nifontov
 */

#ifndef SRC_BRAVO_BRAVO_DEF_H_
#define SRC_BRAVO_BRAVO_DEF_H_

// *** RTOS *** //
#define TIMER_TICK 0.001 /* 1ms */

// *** GLOBAL *** //
#define WAVE_PARTS 461 // 0..460
#define WAVE_DT_PULSES_R 457 // 461.460.459.458.457

#define MIN_PULSE 3420
#define MAX_PULSE 25000

enum BRAVO_STATE {NOAC, AC, SD, BOOT, FLT};
enum BRAVO_WAVE_50HZ {AA,BB};

#endif /* SRC_BRAVO_BRAVO_DEF_H_ */
