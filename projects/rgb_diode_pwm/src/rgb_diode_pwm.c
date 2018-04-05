/*
 Name        : rgb_diode_pwm.c
 Author      : sobriodev
 Description : Simple program used to control common anode RGB diode.
               It has customizable period per each color sequence and sequence of colors to display
*/

#include "board.h"
#include <cr_section_macros.h>
#include "../inc/pwm.h"

int main(void) {
    // Generic initialization
    SystemCoreClockUpdate();
    Board_Init();

    const COLORS_T ARRAY[10] = {RED, GREEN, BLUE, BLUE, GREEN, RED, BLUE, BLUE, BLUE, GREEN};

    PWMInit(1200);
    createSequenceFromArray(ARRAY, 10);
    sequenceStart(1);
    destroySequence();

    while(1) {}
    return 0 ;
}
