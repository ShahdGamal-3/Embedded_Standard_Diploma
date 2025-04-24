/******************************************************************************
 * Module: LED
 * File Name: led.c
 * Author: Shahd Gamal
 *******************************************************************************/

#include "gpio.h"          /* To control the GPIO pins */
#include "led.h"           /* To use the LED module APIs */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void LEDS_init(void)
{
    /* Set Red, Green, and Blue LED pins as output */
    GPIO_setupPinDirection(RED_LED_PORT_ID, RED_LED_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, PIN_OUTPUT);

    /* Turn off all LEDs at the beginning */
    LED_off(RED);
    LED_off(GREEN);
    LED_off(BLUE);
}

void LED_on(LED_ID id)
{
#if (LED_CONFIGURATION == POSITIVE_LOGIC)
    /* If the LEDs are configured as positive logic (HIGH = ON) */
    switch (id) {
        case RED:
            GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_HIGH);
            break;
        case GREEN:
            GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_HIGH);
            break;
        case BLUE:
            GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_HIGH);
            break;
    }

#elif (LED_CONFIGURATION == NEGATIVE_LOGIC)
    /* If the LEDs are configured as negative logic (LOW = ON) */
    switch (id) {
        case RED:
            GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_LOW);
            break;
        case GREEN:
            GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_LOW);
            break;
        case BLUE:
            GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_LOW);
            break;
    }
#endif
}

void LED_off(LED_ID id)
{
#if (LED_CONFIGURATION == POSITIVE_LOGIC)
    /* If the LEDs are configured as positive logic (LOW = OFF) */
    switch (id) {
        case RED:
            GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_LOW);
            break;
        case GREEN:
            GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_LOW);
            break;
        case BLUE:
            GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_LOW);
            break;
    }

#elif (LED_CONFIGURATION == NEGATIVE_LOGIC)
    /* If the LEDs are configured as negative logic (HIGH = OFF) */
    switch (id) {
        case RED:
            GPIO_writePin(RED_LED_PORT_ID, RED_LED_PIN_ID, LOGIC_HIGH);
            break;
        case GREEN:
            GPIO_writePin(GREEN_LED_PORT_ID, GREEN_LED_PIN_ID, LOGIC_HIGH);
            break;
        case BLUE:
            GPIO_writePin(BLUE_LED_PORT_ID, BLUE_LED_PIN_ID, LOGIC_HIGH);
            break;
    }
#endif
}
