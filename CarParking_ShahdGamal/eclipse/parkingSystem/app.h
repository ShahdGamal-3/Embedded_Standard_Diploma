/*
 * app.h
 *
 *  Created on: Oct 14, 2024
 *      Author: shahd
 */

#ifndef APP_H_
#define APP_H_

#include "avr/io.h"            /* For AVR registers */
#include <util/delay.h>        /* For _delay_ms function */
#include <avr/interrupt.h>     /* For enabling global interrupts */
#include "lcd.h"               /* LCD driver */
#include "ultrasonic_sensor.h" /* Ultrasonic sensor driver */
#include "led.h"               /* LED driver */
#include "buzzer.h"            /* Buzzer driver */
#include "icu.h"               /* ICU driver for timing the ultrasonic signal */
#include "gpio.h"              /* GPIO driver for pin configurations */

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Define distance boundries */
#define DISTANCE_BOUNDRY_5     5
#define DISTANCE_BOUNDRY_10    10
#define DISTANCE_BOUNDRY_15    15
#define DISTANCE_BOUNDRY_20    20

#endif /* APP_H_ */
