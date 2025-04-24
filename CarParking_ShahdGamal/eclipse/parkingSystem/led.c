/******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.c
 *
 * Description: Source file for the AVR LED driver
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/

#include "gpio.h"  /* Include the GPIO library to control GPIO pins */
#include "led.h"   /* Include the LED header file for accessing LED APIs */

/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/

/*
 * Global configuration for the Red LED.
 * The Red LED is connected to PORTC, PIN0, and uses positive logic.
 */
LED_ConfigType g_LED_red_configrations =
  {.LED_port = PORTC_ID, .LED_pin = PIN0_ID, .LED_logic = LED_POSITIVE_LOGIC };

/*
 * Global configuration for the Green LED.
 * The Green LED is connected to PORTC, PIN1, and uses positive logic.
 */
LED_ConfigType g_LED_green_configrations =
  {.LED_port = PORTC_ID, .LED_pin = PIN1_ID, .LED_logic = LED_POSITIVE_LOGIC };

/*
 * Global configuration for the Blue LED.
 * The Blue LED is connected to PORTC, PIN2, and uses positive logic.
 */
LED_ConfigType g_LED_blue_configrations =
  {.LED_port = PORTC_ID, .LED_pin = PIN2_ID, .LED_logic = LED_POSITIVE_LOGIC };

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the LED by configuring the pin direction.
 * - This function sets the LED pin as an output pin.
 */
void LEDS_init(const LED_ConfigType * LED_Config_Ptr)
{
    /* Configure the specified LED pin as output */
    GPIO_setupPinDirection(LED_Config_Ptr->LED_port, LED_Config_Ptr->LED_pin, PIN_OUTPUT);
}

/*
 * Description :
 * Function to turn on the LED.
 * - For positive logic, a HIGH signal turns the LED on.
 * - For negative logic, a LOW signal turns the LED on.
 */
void LED_on(const LED_ConfigType * LED_Config_Ptr)
{
    /* Turn on the LED according to its logic configuration */
    GPIO_writePin(LED_Config_Ptr->LED_port, LED_Config_Ptr->LED_pin, LED_Config_Ptr->LED_logic);
}

/*
 * Description :
 * Function to turn off the LED.
 * - For positive logic, a LOW signal turns the LED off.
 * - For negative logic, a HIGH signal turns the LED off.
 */
void LED_off(const LED_ConfigType * LED_Config_Ptr)
{
    /* Turn off the LED by inverting its logic configuration */
    GPIO_writePin(LED_Config_Ptr->LED_port, LED_Config_Ptr->LED_pin, !LED_Config_Ptr->LED_logic);
}
