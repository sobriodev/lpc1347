/*
 * pwm.c
 *
 *  Created on: Mar 5, 2018
 *      Author: sobriodev
 */

#include "board.h"
#include "stdlib.h"
#include "../inc/pwm.h"

uint8_t seqLength = 0;  /* Sequence length */
COLORS_T *seq = NULL;   /* Sequence's first step address */

uint32_t cycleLength;   /* PWM cycle length (period) */
COLORS_T currentColor;  /* Current color */
int8_t direction;       /* Variable specifying whether PWM duty cycle will be incremented or decremented */

/* Create sequence */
void createSequence(uint8_t length) {
    destroySequence();
    seq = malloc(length * sizeof(COLORS_T));
    seqLength = (seq == NULL) ? 0 : length;
}

/* Add sequence step */
void addSequenceStep(COLORS_T step, uint8_t position) {
    if (position >= 0 && position < seqLength) {
        seq[position] = step;
    }
}

/* Create sequence from array */
void createSequenceFromArray(const COLORS_T *array, uint8_t steps) {
    createSequence(steps);
    for (int8_t i = 0; i < seqLength; ++i) {
        seq[i] = array[i];
    }
}

/* Destroy sequence */
void destroySequence(void) {
    free(seq);
    seq = NULL;
    seqLength = 0;
}

/* Configure PWM pins */
void configureOutputPins(void) {
    LPC_IOCON->PIO1[RED_PIN] = IOCON_FUNC1;
    LPC_IOCON->PIO1[GREEN_PIN] = IOCON_FUNC1;
    LPC_IOCON->PIO1[BLUE_PIN] = IOCON_FUNC1;
}

/* Initialize PWM */
void PWMInit(uint32_t period) {
    configureOutputPins();
    LPC_SYSCTL->SYSAHBCLKCTRL |= _BIT(SYSCTL_CLOCK_CT32B0);
    Chip_TIMER_Reset(TIMER);
    TIMER->PR = PRESCALER;
    // Set PWM cycle length by subtracting one from the period (PWM output will always consist of a one clock tick wide positive pulse)
    TIMER->MR[CLEAR_INDEX] =  period - 1;
    cycleLength = period;
    TIMER->MCR = TIMER_RESET_ON_MATCH(CLEAR_INDEX);
    TIMER->PWMC = _BIT(RED) | _BIT(GREEN) | _BIT(BLUE);
    // Enable interrupt in NVIC
    NVIC->ICPR[0] = _BIT(TIMER_32_0_IRQn);
    NVIC->ISER[0] = _BIT(TIMER_32_0_IRQn);
}

/* Start sequence */
void sequenceStart(int8_t repeat) {
    int8_t step = 0;
    while (step < seqLength) {
        currentColor = seq[step];
        TIMER->IR = _BIT(CLEAR_INDEX);
        TIMER->MR[currentColor] = 0;
        // Setting duty cycle to 1 will prevent from interrupt (zero would change PWM direction) */
        TIMER->MR[currentColor] = 1;
        /* Set direction to decreasing duty cycle  */
        direction = 1;
        TIMER->MCR |= TIMER_INT_ON_MATCH(CLEAR_INDEX);

        TIMER->TCR = TIMER_ENABLE;
        /* Wait for current color step's end */
        while (TIMER->MR[currentColor] != 0) {}
        ++step;
        /* If repeat mode is chosen start sequence again */
        if (repeat && step == seqLength) {
            step = 0;
        }
    }
    TIMER->TCR = 0;
}

/* Timer IRQ Handler */
void TIMER32_0_IRQHandler(void) {
    if (TIMER->IR & TIMER_MATCH_INT(CLEAR_INDEX)) {
        // Increase or decrease PWM duty cycle
        TIMER->MR[currentColor] += direction;
        // Change direction if PWM duty cycle is 100% or
        // disable interrupt when duty cycle reaches 0% to prevent subtracting one from zero (what would cause 100% duty cycle)
        if (TIMER->MR[currentColor] == 0) {
            TIMER->MCR &= ~TIMER_INT_ON_MATCH(CLEAR_INDEX);
        } else if (TIMER->MR[currentColor] == cycleLength) {
            direction = -direction;
        }
        TIMER->IR = TIMER_MATCH_INT(CLEAR_INDEX);
    }
}
