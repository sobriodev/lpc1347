/*
 * pwm.h
 *
 *  Created on: Mar 5, 2018
 *      Author: sobriodev
 */

#ifndef PWM_H_
#define PWM_H_

typedef enum COLORS {RED, GREEN, BLUE} COLORS_T;

/**
 * @brief   Create sequence of colors
 * @param   length : Sequence length
 * @return  Nothing
 */
void createSequence(uint8_t length);

/**
 * @brief   Insert particular sequence step (color)
 * @param   step     : Particular step (color)
 * @param   position : Step position
 * @return  Nothing
 */
void createSequenceStep(COLORS_T step, uint8_t position);

/**
 * @brief   Destroy sequence
 * @return  Nothing
 */
void destroySequence(void);

#endif /* PWM_H_ */
