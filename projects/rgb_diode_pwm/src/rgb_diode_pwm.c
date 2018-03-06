/*
 Name        : rgb_diode_pwm.c
 Author      : sobriodev
 Description : Simple program used to control RGB diode.
               It has customizable period per each color sequence and sequence of colors to display
*/

#include "board.h"
#include <cr_section_macros.h>

int main(void) {
    // Generic initialization
    SystemCoreClockUpdate();
    Board_Init();

    while(1) {}
    return 0 ;
}
