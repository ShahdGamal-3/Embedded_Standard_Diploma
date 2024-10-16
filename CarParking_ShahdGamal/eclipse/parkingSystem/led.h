/******************************************************************************
 *
 * Module: LED
 *
 * File Name: led.h
 *
 * Description: Header file for the AVR LED driver
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * Macro to define the LED configuration.
 * - POSITIVE_LOGIC: LED turns ON when the signal is HIGH.
 * - NEGATIVE_LOGIC: LED turns ON when the signal is LOW.
 * This macro allows easy switching between positive and negative logic configurations.
 */
#define LED_CONFIGURATION       POSITIVE_LOGIC

/*******************************************************************************
 *                              Types Declaration                              *
 *******************************************************************************/

/*
 * Description: Enumeration for the LED logic states.
 * - LED_NEGATIVE_LOGIC: Represents an LED connected with negative logic (active low).
 * - LED_POSITIVE_LOGIC: Represents an LED connected with positive logic (active high).
 */
typedef enum {
	LED_NEGATIVE_LOGIC,    /* LED logic for negative logic (active low) */
    LED_POSITIVE_LOGIC     /* LED logic for positive logic (active high) */
} LED_logic_state;

/*
 * Description: Structure to hold the configuration parameters for an LED.
 * - LED_port: The port number where the LED is connected (2 bits).
 * - LED_pin: The pin number where the LED is connected (3 bits).
 * - LED_logic: The logic type used to control the LED (positive or negative).
 */
typedef struct {
  uint8 LED_port :2; /* Port number where the LED is connected (2 bits) */
  uint8 LED_pin :3;  /* Pin number where the LED is connected (3 bits) */
  LED_logic_state LED_logic :1; /* Logic type for the LED */
} LED_ConfigType;

/* External declarations for the configuration of Red, Green, and Blue LEDs */
extern LED_ConfigType g_LED_red_configrations;
extern LED_ConfigType g_LED_green_configrations;
extern LED_ConfigType g_LED_blue_configrations;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * Description:
 * Function to initialize the LED.
 * 	1. Set the direction of the LED pin as output.
 * 	2. Ensure the LED is off initially.
 */
void LEDS_init(const LED_ConfigType * LED_Config_Ptr);

/**
 * Description:
 * Function to turn on the specified LED based on its configuration.
 * 	The function checks the logic configuration and sets the pin accordingly.
 */
void LED_on(const LED_ConfigType * LED_Config_Ptr);

/**
 * Description:
 * Function to turn off the specified LED based on its configuration.
 * 	The function checks the logic configuration and clears the pin accordingly.
 */
void LED_off(const LED_ConfigType * LED_Config_Ptr);

#endif /* LED_H_ */
