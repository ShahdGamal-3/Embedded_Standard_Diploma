/******************************************************************************
 *
 * Module: Ultrasonic Sensor
 *
 * File Name: ultrasonic_sensor.c
 *
 * Description: Source file for the AVR Ultrasonic sensor driver
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/

#include <util/delay.h>  /* Include delay function for triggering the sensor */
#include "ultrasonic_sensor.h"
#include "icu.h"
#include "gpio.h"

/* Global variable to hold the time between the rising and falling edges of the echo signal */
uint16 g_timePulse = 0;

/* Global variable to count the edges detected by the ICU */
uint8  g_edgeCount = 0;

/* Global Ultrasonic sensor configuration for the trigger and echo pins */
Ultrasonic_ConfigType g_Ultrasonic_configrations =
  {.Ultrasonic_trigger_port = PORTD_ID, .Ultrasonic_trigger_pin = PIN7_ID,
   .Ultrasonic_echo_port = PORTD_ID, .Ultrasonic_echo_pin = PIN6_ID};

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Speed of sound in air (cm/s) */
#define SPEED_OF_SOUND_CM 34000

/* Prescaler factor for F_CPU/8 and 16MHz clock */
#define TIME_INCREMENT_US 0.5

/* Constant derived from the distance formula (17000 * Time * TIMER value) */
#define DISTANCE_CONSTANT 117.6

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the Ultrasonic sensor.
 * 	1. Initialize the ICU module.
 * 	2. Set the callback function to handle edge processing.
 * 	3. Configure the trigger pin as output and the echo pin as input.
 */
void Ultrasonic_init(const Ultrasonic_ConfigType * Ultrasonic_Config_ptr)
{
	/* Initialize the ICU driver */
	ICU_init(&ICU_configrations);

	/* Set the callback function for ICU interrupts */
	ICU_setCallBack(Ultrasonic_edgeProcessing);

	/* Set trigger pin direction as output */
	GPIO_setupPinDirection(Ultrasonic_Config_ptr->Ultrasonic_trigger_port,
			               Ultrasonic_Config_ptr->Ultrasonic_trigger_pin, PIN_OUTPUT);

	/* Set echo pin direction as input */
	GPIO_setupPinDirection(Ultrasonic_Config_ptr->Ultrasonic_echo_port,
			               Ultrasonic_Config_ptr->Ultrasonic_echo_pin, PIN_INPUT);
}

/*
 * Description :
 * Function to trigger the Ultrasonic sensor.
 * 	1. Set the trigger pin high for 10µs to send a pulse.
 * 	2. Set the trigger pin low after the pulse is sent.
 */
void Ultrasonic_Trigger(const Ultrasonic_ConfigType * Ultrasonic_Config_ptr)
{
	/* Set trigger pin HIGH to start the pulse */
	GPIO_writePin(Ultrasonic_Config_ptr->Ultrasonic_trigger_port,
			      Ultrasonic_Config_ptr->Ultrasonic_trigger_pin, LOGIC_HIGH);

	/* Wait for 10 microseconds */
	_delay_us(10);

	/* Set trigger pin LOW after sending the pulse */
	GPIO_writePin(Ultrasonic_Config_ptr->Ultrasonic_trigger_port,
			      Ultrasonic_Config_ptr->Ultrasonic_trigger_pin, LOGIC_LOW);
}

/*
 * Description :
 * Function to read the distance measured by the Ultrasonic sensor.
 * 	1. Trigger the Ultrasonic sensor.
 * 	2. Use the recorded time between echo signal edges to calculate distance.
 * Return: The calculated distance in centimeters.
 */
uint16 Ultrasonic_readDistance(void)
{
	/* Trigger the Ultrasonic sensor to start measurement */
	Ultrasonic_Trigger(&g_Ultrasonic_configrations);

	/* Calculate the distance based on the timePulse value */
	uint16 distance = (uint16)(g_timePulse / DISTANCE_CONSTANT) + 1;

	return distance;
}

/*
 * Description :
 * Function to handle the ICU edge detection (rising and falling edges).
 * 	1. On the first edge (rising), reset the timer and switch to falling edge detection.
 * 	2. On the second edge (falling), capture the time, reset the timer, and switch back
 *     to rising edge detection.
 */
void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++; /* Increment the edge count */

	switch(g_edgeCount)
	{
	case 1:
		/* First edge (rising): Clear the timer and set the edge to falling */
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
		break;
	case 2:
		/* Second edge (falling): Capture the time, clear the timer, and set the edge to rising */
		g_timePulse = ICU_getInputCaptureValue();
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(RAISING);
		g_edgeCount = 0; /* Reset edge count for the next measurement */
		break;
	}
}
