/******************************************************************************
 * Module: LED
 * File Name: led.h
 * Author: Shahd Gamal
 *******************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * LED Pin Configuration
 * Define the port and pin numbers for the Red, Green, and Blue LEDs.
 */
#define RED_LED_PORT_ID        PORTB_ID  /* Port for Red LED */
#define RED_LED_PIN_ID         PIN5_ID   /* Pin for Red LED */

#define GREEN_LED_PORT_ID      PORTB_ID  /* Port for Green LED */
#define GREEN_LED_PIN_ID       PIN6_ID   /* Pin for Green LED */

#define BLUE_LED_PORT_ID       PORTB_ID  /* Port for Blue LED */
#define BLUE_LED_PIN_ID        PIN7_ID   /* Pin for Blue LED */

/*
 * LED Configuration
 * Choose between positive or negative logic for LED control.
 * In positive logic, a HIGH signal turns the LED ON.
 * In negative logic, a LOW signal turns the LED ON.
 */
#define LED_CONFIGURATION       POSITIVE_LOGIC

/*******************************************************************************
 *                                Type Definitions                             *
 *******************************************************************************/

/*
 * LED_ID Enum
 * Enum for identifying LED colors.
 */
typedef enum
{
    RED,    /* Identifier for the Red LED */
    GREEN,  /* Identifier for the Green LED */
    BLUE    /* Identifier for the Blue LED */
} LED_ID;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * Description :
 * This function sets up the GPIO pins for the LEDs and turns them off initially.
 */
void LEDS_init(void);

/**
 * Description :
 * This function turns on the specified LED.
 */
void LED_on(LED_ID id);

/**
 * Description :
 * This function Ttrns off the specified LED.
 */
void LED_off(LED_ID id);

#endif /* LED_H_ */
