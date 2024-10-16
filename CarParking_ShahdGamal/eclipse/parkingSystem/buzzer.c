/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the AVR Buzzer driver
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/

#include "buzzer.h"  /* Include the buzzer header file for accessing Buzzer APIs */
#include "gpio.h"    /* Include the GPIO library to control GPIO pins */

/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/

/*
 * Global configuration for the Buzzer.
 * The Buzzer is connected to PORTC, PIN5.
 */
BUZZER_ConfigType g_BUZZER_configrations = {.BUZZER_port = PORTC_ID, .BUZZER_pin = PIN5_ID};

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the Buzzer by configuring the pin direction.
 * - This function sets the Buzzer pin as an output pin.
 */
void Buzzer_init(const BUZZER_ConfigType * BUZZER_Config_Ptr){
    /* Configure the specified Buzzer pin as output */
    GPIO_setupPinDirection(BUZZER_Config_Ptr->BUZZER_port, BUZZER_Config_Ptr->BUZZER_pin, PIN_OUTPUT);
}

/*
 * Description :
 * Function to turn on the Buzzer.
 * - Sets the Buzzer pin to a HIGH logic level to activate the Buzzer.
 */
void Buzzer_on(const BUZZER_ConfigType * BUZZER_Config_Ptr){
    /* Set the Buzzer pin to high to turn it on */
    GPIO_writePin(BUZZER_Config_Ptr->BUZZER_port, BUZZER_Config_Ptr->BUZZER_pin, LOGIC_HIGH);
}

/*
 * Description :
 * Function to turn off the Buzzer.
 * - Sets the Buzzer pin to a LOW logic level to deactivate the Buzzer.
 */
void Buzzer_off(const BUZZER_ConfigType * BUZZER_Config_Ptr){
    /* Set the Buzzer pin to low to turn it off */
    GPIO_writePin(BUZZER_Config_Ptr->BUZZER_port, BUZZER_Config_Ptr->BUZZER_pin, LOGIC_LOW);
}
