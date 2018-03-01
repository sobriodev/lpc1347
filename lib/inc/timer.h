/*
 * timer.h
 *
 *  Created on: Feb 28, 2018
 *      Author: sobriodev
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "board.h"

/* Clock numbers */
#define CT16B0_CLOCK_MASK   _BIT(SYSCTL_CLOCK_CT16B0)
#define CT16B1_CLOCK_MASK   _BIT(SYSCTL_CLOCK_CT16B1)
#define CT32B0_CLOCK_MASK   _BIT(SYSCTL_CLOCK_CT32B0)
#define CT32B1_CLOCK_MASK   _BIT(SYSCTL_CLOCK_CT32B1)

/* PWM channels enable mask */
#define PWM_EN0             _BIT(0)
#define PWM_EN1             _BIT(1)
#define PWM_EN2             _BIT(2)
#define PWM_EN3             _BIT(3)

#endif /* TIMER_H_ */
