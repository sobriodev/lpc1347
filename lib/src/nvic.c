/*
 * nvic.c
 *
 *  Created on: Feb 28, 2018
 *      Author: sobriodev
 */

#include "nvic.h"

void NVIC_Int(IRQn_Type irq) {
    NVIC->ICPR[0] = _BIT(irq);
    NVIC->ISER[0] = _BIT(irq);
}

