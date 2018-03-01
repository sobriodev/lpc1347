/*
===============================================================================
 Name        : timer16b_cap.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#include "board.h"
#include <cr_section_macros.h>

int main(void) {
    // Generic initialization
    SystemCoreClockUpdate();
    Board_Init();

    volatile static int i = 0 ;
    while(1) {
        i++ ;
    }
    return 0 ;
}
