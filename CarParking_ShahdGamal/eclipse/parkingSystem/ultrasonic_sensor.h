/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic_sensor.h
 *
 * Description: Header file for the AVR Ultrasonic sensor driver
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/

#ifndef ULTRASONIC_SENSOR_H_
#define ULTRASONIC_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*
 * Description: Structure to hold the configuration parameters for the Ultrasonic sensor.
 *              - Ultrasonic_trigger_port: The port number for the trigger pin (2 bits).
 *              - Ultrasonic_trigger_pin: The pin number for the trigger (4 bits).
 *              - Ultrasonic_echo_port: The port number for the echo pin (2 bits).
 *              - Ultrasonic_echo_pin: The pin number for the echo (4 bits).
 */
typedef struct {
	uint8 Ultrasonic_trigger_port:2;
	uint8 Ultrasonic_trigger_pin:4;
	uint8 Ultrasonic_echo_port:2;
	uint8 Ultrasonic_echo_pin:4;
} Ultrasonic_ConfigType;

/* External declaration of the global variable to hold the Ultrasonic sensor configurations */
extern Ultrasonic_ConfigType g_Ultrasonic_configrations;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to initialize the Ultrasonic sensor driver.
 * 	1. Set the direction of the trigger pin as output.
 * 	2. Set the direction of the echo pin as input.
 * 	3. Set up any necessary Timer configuration.
 */
void Ultrasonic_init(const Ultrasonic_ConfigType * Ultrasonic_Config_ptr);

/*
 * Description : Function to trigger the Ultrasonic sensor by sending a 10µs pulse
 *               on the trigger pin.
 */
void Ultrasonic_Trigger(const Ultrasonic_ConfigType * Ultrasonic_Config_ptr);

/*
 * Description: Function to read the distance measured by the Ultrasonic sensor.
 *              The function sends a trigger and waits for the echo to measure
 *              the time, which is then converted to distance.
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description: Function to handle the edge detection for the echo pin.
 *              This is typically called in the ICU ISR to process rising
 *              and falling edges of the echo signal.
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_SENSOR_H_ */
