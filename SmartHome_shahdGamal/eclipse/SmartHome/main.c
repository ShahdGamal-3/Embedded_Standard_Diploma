/******************************************************************************
 *
 * Module: Main Application
 *
 * File Name: main.c
 *
 * Description: Main application file for controlling the system, including
 *              ADC initialization, PWM management, sensor readings, and
 *              actuator control.
 *
 * Author: Shahd Gamal
 *
 * Created on: Oct 4, 2024
 *
 *******************************************************************************/

#include "app.h"

int main(void) {
    // Initialize system components
    ADC_init();          // Initialize the ADC driver for analog readings
    LCD_init();          // Initialize the LCD for display purposes
    LEDS_init();         // Set up LED pins and initialize their states
    Buzzer_init();       // Initialize the buzzer for alert notifications
    DcMotor_Init();      // Initialize the DC motor driver
    FlameSensor_init();  // Initialize the flame sensor for fire detection
    PWM_Init ();         // Initialize the PWM signal

    // Start PWM with the fan turned off initially
    PWM_Timer0_Start(0);
    DcMotor_Rotate(DC_MOTOR_CW, SET_0_DUTY_CYCLE);  // Set the motor to rotate at 0 duty cycle (off)

    while (1) {
        // Continuously read sensor values and adjust system behavior
        uint16 lightIntensity = LDR_getLightIntensity();   // Get light intensity from LDR
        uint16 temperature = LM35_getTemperature();       // Get temperature from LM35 sensor

        // Adjust fan speed based on temperature reading
        PWM_adjustFanSpeed(temperature);

        // Control LEDs based on light intensity
        LED_controlLighting(lightIntensity);

        // Display sensor readings on the LCD
        LCD_displayLight(lightIntensity);                   // Display the light intensity
        LCD_displayTemperature(temperature);               // Display the temperature
        LCD_displayFanState(temperature >= 25);           // Display fan state based on temperature threshold

        // Check for flame detection
        while (FlameSensor_getValue()) {
            Buzzer_on();                                  // Activate buzzer for alert
            LCD_moveCursor(FIRST_ROW, FIRST_COLUMN);
            LCD_displayString("Critical alert!");        // Display alert message
            LCD_moveCursor(FIRST_ROW + 1, FIRST_COLUMN);
            LCD_displayString("                ");      // Clear the second line
        }
        Buzzer_off();  // Turn off the buzzer when no flame is detected
    }
}
