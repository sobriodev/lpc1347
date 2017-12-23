/*
 * ct.h
 *
 *  Created on: 23.12.2017
 *      Author: sobriodev
 */

#ifndef CT_H_
#define CT_H_

#include "chip.h"

#define TIMER_ENABLE_POS 	0						/* TCR : CEN position */
#define TIMER_ENABLE_MASK	_BIT(TIMER_ENABLE_POS)	/* TCR : CEN mask */
#define TIMER_RESET_POS 	1						/* TCR : CRST position */
#define TIMER_RESET_MASK 	_BIT(TIMER_RESET_POS)	/* TCR : CRST mask */

/**
 * @brief 	Resets the particular timer
 * @param 	timer	:  Pointer to timer
 * @return 	Nothing
 */
void Timer_Reset(LPC_TIMER_T *timer);

#endif /* CT_H_ */
