/*
 * pwm.c
 *
 *  Created on: Mar 5, 2018
 *      Author: sobriodev
 */

#include "board.h"
#include "stdlib.h"
#include "../inc/pwm.h"

static uint8_t seqLength = 0;
static COLORS_T *seq = NULL;

/* Create sequence */
void createSequence(uint8_t length) {
    seq = malloc(length * sizeof(COLORS_T));
    seqLength = (seq == NULL) ? 0 : length;
}

/* Create sequence step */
void createSequenceStep(COLORS_T step, uint8_t position) {
    if (position >= 0 && position < seqLength) {
        seq[position] = step;
    }
}

/* Destroy sequence */
void destroySequence(void) {
    free(seq);
    seq = NULL;
    seqLength = 0;
}
