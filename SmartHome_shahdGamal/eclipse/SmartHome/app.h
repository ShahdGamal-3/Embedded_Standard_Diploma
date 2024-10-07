/******************************************************************************
 *
 * Module: Application
 *
 * File Name: app.h
 *
 * Description: Header file for the main application, including function
 *              prototypes for controlling the system components such as
 *              LEDs, PWM, LCD display, and various sensors.
 *
 * Author: Shahd Gamal
 *
 * Created on: Oct 4, 2024
 *
 *******************************************************************************/

#ifndef APP_H_
#define APP_H_

#include <avr/io.h>           // Include AVR I/O definitions for hardware access
#include <util/delay.h>      // Include delay functions for timing control
#include "lcd.h"             // Include the LCD driver for display functions
#include "ldr_sensor.h"      // Include the LDR sensor driver for light detection
#include "pwm.h"             // Include the PWM driver for fan speed control
#include "buzzer.h"          // Include the buzzer driver for alert notifications
#include "led.h"             // Include the LED driver for lighting control
#include "dc_motor.h"        // Include the DC motor driver for movement control
#include "flame_sensor.h"    // Include the flame sensor driver for fire detection
#include "lm35_sensor.h"     // Include the LM35 temperature sensor driver
#include "adc.h"             // Include the ADC driver for analog to digital conversion

/*******************************************************************************
 *                      Function Prototypes                                   *
 *******************************************************************************/

/*
 * Function: LED_controlLighting
 * Description: Adjusts the lighting of LEDs based on the detected light intensity.
 * Parameters:
 *      light_intensity - The current light intensity value from the LDR sensor.
 */
void LED_controlLighting(uint16 light_intensity);

/*
 * Function: PWM_adjustFanSpeed
 * Description: Adjusts the PWM signal to control the fan speed based on temperature.
 * Parameters:
 *      temperature - The current temperature value from the LM35 sensor.
 */
void PWM_adjustFanSpeed(uint16 temperature);

/*
 * Function: LCD_displayFanState
 * Description: Displays the current state of the fan on the LCD.
 * Parameters:
 *      fan_state - The state of the fan (ON/OFF).
 */
void LCD_displayFanState(uint8 fan_state);

/*
 * Function: LCD_displayTemperature
 * Description: Displays the current temperature on the LCD.
 * Parameters:
 *      temperature - The current temperature value to be displayed.
 */
void LCD_displayTemperature(uint16 temperature);

/*
 * Function: LCD_displayLight
 * Description: Displays the current light intensity on the LCD.
 * Parameters:
 *      light_intensity - The current light intensity value to be displayed.
 */
void LCD_displayLight(uint16 light_intensity);

#endif /* APP_H_ */
