/******************************************************************************
 *
 * Module: Application
 *
 * File Name: app.c
 *
 * Description: Implementation of application-level functions for controlling
 *              the system components, including LEDs, PWM for fan speed,
 *              and LCD display functions.
 *
 * Author: Shahd Gamal
 *
 * Created on: Oct 4, 2024
 *
 *******************************************************************************/

#include "app.h"

/*******************************************************************************
 *                      Functions Implementation                               *
 *******************************************************************************/

/*
 * Function: LED_controlLighting
 * Description: Controls the lighting of LEDs based on the detected light intensity.
 * Parameters:
 *      light_intensity - The current light intensity value from the LDR sensor.
 */
void LED_controlLighting(uint16 light_intensity) {
    if (light_intensity < FIRST_INTENSITY_RANGE) {
        // Turn on all LEDs (Red, Green, Blue)
        LED_on(RED);
        LED_on(GREEN);
        LED_on(BLUE);

    } else if (light_intensity < SECOND_INTENSITY_RANGE) {
        // Turn on Red and Green LEDs
        LED_on(RED);
        LED_on(GREEN);
        LED_off(BLUE);

    } else if (light_intensity < THIRD_INTENSITY_RANGE) {
        // Turn on Red LED
        LED_on(RED);
        LED_off(GREEN);
        LED_off(BLUE);

    } else {
        // Turn off all LEDs
        LED_off(RED);
        LED_off(GREEN);
        LED_off(BLUE);
    }
}

/*
 * Function: PWM_adjustFanSpeed
 * Description: Adjusts the PWM signal to control the fan speed based on temperature.
 * Parameters:
 *      temperature - The current temperature value from the LM35 sensor.
 */
void PWM_adjustFanSpeed(uint16 temperature) {
    if (temperature >= FOURTH_TEMP_RANGE) {
        PWM_Timer0_Start(SET_MAX_DUTY_CYCLE); // 100% duty cycle

    } else if (temperature >= THIRD_TEMP_RANGE) {
        PWM_Timer0_Start(SET_75_DUTY_CYCLE);  // 75% duty cycle

    } else if (temperature >= SECOND_TEMP_RANGE) {
        PWM_Timer0_Start(SET_50_DUTY_CYCLE);  // 50% duty cycle

    } else if (temperature >= FIRST_TEMP_RANGE) {
        PWM_Timer0_Start(SET_25_DUTY_CYCLE);  // 25% duty cycle

    } else {
        PWM_Timer0_Start(SET_0_DUTY_CYCLE);   // Fan OFF
    }
}

/*
 * Function: LCD_displayFanState
 * Description: Displays the current state of the fan on the LCD.
 * Parameters:
 *      fan_state - The state of the fan (1 for ON, 0 for OFF).
 */
void LCD_displayFanState(uint8 fan_state) {
    LCD_moveCursor(FIRST_ROW, FIRST_COLUMN); // Set cursor position for fan state display

    // Display the fan state centered
    if (fan_state) {
        LCD_displayString("   FAN is ON   ");
    } else {
        LCD_displayString("   FAN is OFF  ");
    }
}

/*
 * Function: LCD_displayTemperature
 * Description: Displays the current temperature on the LCD.
 * Parameters:
 *      temperature - The current temperature value to be displayed.
 */
void LCD_displayTemperature(uint16 temperature) {
    LCD_moveCursor(FIRST_ROW + 1, FIRST_COLUMN); // Set cursor position for temperature display
    LCD_displayString("Temp=");
    LCD_intgerToString(temperature); // Convert and display the integer temperature value
}

/*
 * Function: LCD_displayLight
 * Description: Displays the current light intensity on the LCD.
 * Parameters:
 *      light_intensity - The current light intensity value to be displayed.
 */
void LCD_displayLight(uint16 light_intensity) {
    LCD_moveCursor(FIRST_ROW + 1, FIRST_COLUMN + 9); // Set cursor position for light intensity display
    LCD_displayString("LDR=");
    LCD_intgerToString(light_intensity); // Convert and display the integer light intensity value
    LCD_displayString("%"); // Display the percentage symbol
    LCD_displayString("  "); // Clear extra characters
}
