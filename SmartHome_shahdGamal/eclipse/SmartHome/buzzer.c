/******************************************************************************
 * Module: Buzzer
 * File Name: buzzer.c
 * Author: Shahd Gamal
 *******************************************************************************/

#include "buzzer.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void Buzzer_init(void){
    /* Configure the buzzer pin as output */
    GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_LED_PIN_ID, PIN_OUTPUT);

    /* Ensure the buzzer is initially off */
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_LED_PIN_ID, LOGIC_LOW);
}

void Buzzer_on(void){
    /* Set the buzzer pin to high to turn on the buzzer */
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_LED_PIN_ID, LOGIC_HIGH);
}

void Buzzer_off(void){
    /* Set the buzzer pin to low to turn off the buzzer */
    GPIO_writePin(BUZZER_PORT_ID, BUZZER_LED_PIN_ID, LOGIC_LOW);
}
