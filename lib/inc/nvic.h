/*
 * nvic.h
 *
 *  Created on: Feb 28, 2018
 *      Author: sobriodev
 */

#ifndef NVIC_H_
#define NVIC_H_

#include "board.h"

/**
 * @brief Clear pending and enable particular interrupt
 * @param irq : NVIC interrupt number
 */
void NVIC_Int(IRQn_Type irq);

#endif /* NVIC_H_ */
