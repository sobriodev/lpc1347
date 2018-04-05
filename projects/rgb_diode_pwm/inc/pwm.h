/*
 * pwm.h
 *
 *  Created on: Mar 5, 2018
 *      Author: sobriodev
 */

#ifndef PWM_H_
#define PWM_H_

#define TIMER           LPC_TIMER32_0   /* Timer 16B0 will be used */
#define PRESCALER       71              /* Output timer tick will take exactly 100us */
#define PWM_PORT        1               /* PWM output port */
#define RED_PIN         24              /* Pin mapped to red color */
#define GREEN_PIN       25              /* Pin mapped to green color */
#define BLUE_PIN        26              /* Pin mapped to blue color */

#define CLEAR_INDEX     3               /* PWM cycle length registers' bit offset */



/* Enum containing timer's MATCH offsets for particular colors */
typedef enum COLORS {
    RED = 0,
    GREEN = 1,
    BLUE = 2
} COLORS_T;


/**
 * @brief   Create sequence of colors
 * @param   length : Sequence length
 * @return  Nothing
 */
void createSequence(uint8_t length);

/**
 * @brief   Insert particular sequence step (color)
 * @param   step     : Particular step
 * @param   position : Step position
 * @return  Nothing
 */
void addSequenceStep(COLORS_T step, uint8_t position);

/**
 * Create sequence from array
 * @param array : Array of colors (steps)
 * @param steps : Numbers of steps
 */
void createSequenceFromArray(const COLORS_T *array, uint8_t steps);

/**
 * @brief   Destroy sequence
 * @return  Nothing
 */
void destroySequence(void);

/**
 * Start sequence
 * @param repeat : If true sequence will repeat infinitely
 * @return Nothing
 */
void sequenceStart(int8_t repeat);

/**
 * Configure all required pins as PWM outputs
 * @return Nothing
 */
void configureOutputPins(void);

/**
 * Initialize basic PWM registers
 * @param period : PWM period
 * @return Nothing
 */
void PWMInit(uint32_t period);


#endif /* PWM_H_ */
