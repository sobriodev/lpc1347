/*
 * ct.h
 *
 *  Created on: 23.12.2017
 *      Author: sobriodev
 */

#ifndef CT_H_
#define CT_H_

#include "chip.h"

#define TIMER_ENABLE_MASK   _BIT(0)     /* TCR : CEN Counter enable */
#define TIMER_RESET_MASK    _BIT(1)     /* TCR : CRST Counter reset */

#define CT16B0_CLOCK_MASK   _BIT(7)     /* SYSAHBCLKCTRL : CT16B0 Clock enable for CT16B0 */
#define CT16B1_CLOCK_MASK   _BIT(8)     /* SYSAHBCLKCTRL : CT16B1 Clock enable for CT16B1 */
#define CT32B0_CLOCK_MASK   _BIT(9)     /* SYSAHBCLKCTRL : CT32B0 Clock enable for CT32B0 */
#define CT32B1_CLOCK_MASK   _BIT(10)    /* SYSAHBCLKCTRL : CT32B1 Clock enable for CT32B1 */

#define NVIC_CT16B0_MASK    _BIT(16)    /* NVIC registers CT16B0 mask */
#define NVIC_CT16B1_MASK    _BIT(17)    /* NVIC registers CT16B1 mask */
#define NVIC_CT16B2_MASK    _BIT(18)    /* NVIC registers CT16B2 mask */
#define NVIC_CT16B3_MASK    _BIT(19)    /* NVIC registers CT16B3 mask */

/**
 * @brief   Resets the particular timer
 * @param   timer : Pointer to timer
 * @return  Nothing
 */
void Timer_Reset(LPC_TIMER_T *timer);

#endif /* CT_H_ */
