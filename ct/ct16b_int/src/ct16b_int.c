/*
===============================================================================
 Author      : sobriodev
 Description : Toggle pin's states using interrupt channels
===============================================================================
*/

#include "board.h"
#include "../../static/inc/ct.h"
#include <cr_section_macros.h>

#define TIMER           LPC_TIMER16_0
#define GPIO            LPC_GPIO_PORT
#define IOCON           LPC_IOCON
#define SYSCTL          LPC_SYSCTL

#define PRESCALE_VAL    36000           /* f = 72MHz, output T = 0.5ms => output f = 2kHz, 72MHz / 2kHZ = 36000 */

#define MATCH0          0               /* Match channel 0 */
#define MATCH1          1               /* Match channel 1 */
#define MATCH2          2               /* Match channel 2 */
#define MATCH3          3               /* Match channel 3 */

#define MATCH0_VAL      500             /* Interrupt 0 after 0.25s */
#define MATCH1_VAL      1000            /* Interrupt 1 after 0.5s */
#define MATCH2_VAL      2000            /* Interrupt 2 after 1s */
#define MATCH3_VAL      4000            /* Interrupt 3 after 2s */

#define GPIO_PORT       1               /* Output port */
#define GPIO_START_PIN  19              /* Output start pin */

/**
 * @brief   Timer interrupt handler
 * @return  Nothing
 * Check if particular match channel interrupt is pending. If yes, set corresponding output pin high, or set all pins low when MATCH3 interrupt flag is set.
 */
void TIMER16_0_IRQHandler(void) {
    if (TIMER->IR & TIMER_MATCH_INT(MATCH0)) {
        TIMER->IR = TIMER_MATCH_INT(MATCH0);
        GPIO->B[GPIO_PORT][GPIO_START_PIN] = 1;
    } else if (TIMER->IR & TIMER_MATCH_INT(MATCH1)) {
        TIMER->IR = TIMER_MATCH_INT(MATCH1);
        GPIO->B[GPIO_PORT][GPIO_START_PIN + 1] = 1;
    } else if (TIMER->IR & TIMER_MATCH_INT(MATCH2)) {
        TIMER->IR = TIMER_MATCH_INT(MATCH2);
        GPIO->B[GPIO_PORT][GPIO_START_PIN + 2] = 1;
    } else if (TIMER->IR & TIMER_MATCH_INT(MATCH3)) {
        TIMER->IR = TIMER_MATCH_INT(MATCH3);
        GPIO->PIN[GPIO_PORT] &= ~(_BIT(GPIO_START_PIN) | _BIT(GPIO_START_PIN + 1) | _BIT(GPIO_START_PIN + 2));
    }
}

/**
 * @brief   Main program routine
 * @return  Function should not return
 */
int main(void) {
    // Generic initialization
    SystemCoreClockUpdate();
    Board_Init();

    volatile static uint8_t i;
    for (i = 0; i < 4; ++i) {
        IOCON->PIO1[GPIO_START_PIN + i] = IOCON_FUNC0;
        GPIO->DIR[GPIO_PORT] |= _BIT(GPIO_START_PIN + i);
        GPIO->B[GPIO_PORT][GPIO_START_PIN + i] = 0;
    }

    SYSCTL->SYSAHBCLKCTRL |= CT16B0_CLOCK_MASK;

    Timer_Reset(TIMER);

    TIMER->MCR = TIMER_INT_ON_MATCH(MATCH0) | TIMER_INT_ON_MATCH(MATCH1) | TIMER_INT_ON_MATCH(MATCH2) | TIMER_INT_ON_MATCH(MATCH3) | TIMER_RESET_ON_MATCH(MATCH3);

    TIMER->MR[MATCH0] = MATCH0_VAL;
    TIMER->MR[MATCH1] = MATCH1_VAL;
    TIMER->MR[MATCH2] = MATCH2_VAL;
    TIMER->MR[MATCH3] = MATCH3_VAL;

    TIMER->PR = PRESCALE_VAL - 1;

    TIMER->TCR |= TIMER_ENABLE_MASK;

    NVIC->ICPR[0] = NVIC_CT16B0_MASK;
    NVIC->ISER[0] = NVIC_CT16B0_MASK;

    while(1) {}
    return 0 ;
}
