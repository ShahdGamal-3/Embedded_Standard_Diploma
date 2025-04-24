/******************************************************************************
 * Module: Main Application
 * File Name: main.c
 * Created on: Oct 11, 2024
 * Description: Main program that integrates the LCD, Ultrasonic sensor,
 *              LEDs, and Buzzer for distance measurement and warning system.
 * Author: Shahd Gamal
 *******************************************************************************/

#include "app.h"

int main(void)
{
    uint16 distance = 0; /* Variable to store the distance measured by the ultrasonic sensor */

    /* Initialize LCD, Ultrasonic sensor, Buzzer, and LEDs */
    LCD_init();
    Ultrasonic_init(&g_Ultrasonic_configrations);
    Buzzer_init(&g_BUZZER_configrations);
    Buzzer_off(&g_BUZZER_configrations); /* Ensure the buzzer is off initially */
    LEDS_init(&g_LED_red_configrations);
    LEDS_init(&g_LED_green_configrations);
    LEDS_init(&g_LED_blue_configrations);

    sei(); /* Enable global interrupts for ICU to work */

    /* Display the initial message on LCD */
    LCD_moveCursor(0, 0);
    LCD_displayString("Distance=     CM");

    /* Wait for a valid distance reading (non-zero value) */
    while (distance == 0)
    {
        distance = Ultrasonic_readDistance();
        _delay_ms(100); /* Add a small delay between retries */
    }

    while (1)
    {
        /* Read the distance from the Ultrasonic sensor */
        distance = Ultrasonic_readDistance();

        /* Display the distance on the LCD at position (0,9) */
        LCD_moveCursor(0, 9);
        LCD_intgerToString(distance);
        LCD_displayString("  "); /* Clear any previous values */

        /* Control LEDs and Buzzer based on the measured distance */
        if (distance <= DISTANCE_BOUNDRY_5)
        {
            Buzzer_on(&g_BUZZER_configrations);
            LED_on(&g_LED_red_configrations);
            LED_on(&g_LED_green_configrations);
            LED_on(&g_LED_blue_configrations);
            _delay_ms(500);

            Buzzer_off(&g_BUZZER_configrations);
            LED_off(&g_LED_red_configrations);
            LED_off(&g_LED_green_configrations);
            LED_off(&g_LED_blue_configrations);
            _delay_ms(500);

            /* Display "STOP!" message */
            LCD_moveCursor(1, 5);
            LCD_displayString("STOP!");
        }
        else if (distance <= DISTANCE_BOUNDRY_10)
        {
            Buzzer_off(&g_BUZZER_configrations);

            /* Flash all LEDs */
            LED_on(&g_LED_red_configrations);
            LED_on(&g_LED_green_configrations);
            LED_on(&g_LED_blue_configrations);

            /* Clear the "STOP!" message */
            LCD_moveCursor(1, 5);
            LCD_displayString("     ");
        }
        else if (distance <= DISTANCE_BOUNDRY_15)
        {
            Buzzer_off(&g_BUZZER_configrations);

            /* Turn on Red and Green LEDs, turn off Blue LED */
            LED_on(&g_LED_red_configrations);
            LED_on(&g_LED_green_configrations);
            LED_off(&g_LED_blue_configrations);

            /* Clear the "STOP!" message */
            LCD_moveCursor(1, 5);
            LCD_displayString("     ");
        }
        else if (distance <= DISTANCE_BOUNDRY_20)
        {
            Buzzer_off(&g_BUZZER_configrations);

            /* Turn on only the Red LED, turn off Green and Blue LEDs */
            LED_on(&g_LED_red_configrations);
            LED_off(&g_LED_green_configrations);
            LED_off(&g_LED_blue_configrations);

            /* Clear the "STOP!" message */
            LCD_moveCursor(1, 5);
            LCD_displayString("     ");
        }
        else
        {
            /* Turn off the buzzer and all LEDs */
            Buzzer_off(&g_BUZZER_configrations);
            LED_off(&g_LED_red_configrations);
            LED_off(&g_LED_green_configrations);
            LED_off(&g_LED_blue_configrations);

            /* Clear the "STOP!" message */
            LCD_moveCursor(1, 5);
            LCD_displayString("     ");
        }
    }

    return 0; /* Return statement in case of program termination */
}
