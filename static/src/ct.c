/*
 * ct.c
 *
 *  Created on: 23.12.2017
 *      Author: sobriodev
 */

#include "../inc/ct.h"

void Timer_Reset(LPC_TIMER_T *timer) {
    timer->TC = 1;
    timer->TCR |= TIMER_RESET_MASK;
    while (timer->TC != 0) {}
    timer->TCR &= ~(TIMER_RESET_MASK);
}
