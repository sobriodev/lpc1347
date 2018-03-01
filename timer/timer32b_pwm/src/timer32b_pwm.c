/*
===============================================================================
 Name        : timer32b_pwm.c
 Author      : sobriodev
 Description : 32 bit timer PWM
===============================================================================
*/

#define IOCON                   LPC_IOCON
#define GPIO                    LPC_GPIO_PORT
#define TIMER                   LPC_TIMER32_0
#define SYSCTL                  LPC_SYSCTL

#define PWM_PORT                0
#define PWM_PIN                 18

#define MATCH0                  0
#define MATCH3                  3

#define PWM_CYCLE_LENGTH        2000            /* Cycle length */
#define PWM_DUTY_CYCLE          1               /* Duty cycle in percentage */

#define PRESCALE_VAL            36000           /* f = 72MHz, output T = 0.5ms => output f = 2kHz, 72MHz / 2kHZ = 36000 */

#include "board.h"
#include "../../lib/inc/timer.h"
#include <cr_section_macros.h>

int main(void) {
    // Generic initialization
    SystemCoreClockUpdate();
    Board_Init();

    IOCON->PIO0[PWM_PIN] = IOCON_FUNC2;

    SYSCTL->SYSAHBCLKCTRL |= CT32B0_CLOCK_MASK;
    Chip_TIMER_Reset(TIMER);
    TIMER->PR = PRESCALE_VAL - 1;
    TIMER->MR[MATCH0] = PWM_CYCLE_LENGTH * (100 - PWM_DUTY_CYCLE) / 100;
    TIMER->MR[MATCH3] = PWM_CYCLE_LENGTH - 1;
    TIMER->MCR |= TIMER_RESET_ON_MATCH(MATCH3);
    TIMER->PWMC |= (PWM_EN0 | PWM_EN3);
    TIMER->TCR = TIMER_ENABLE;

    while(1) {}
    return 0 ;
}
