/******************************************************************************
 *
 * Module: PIR Sensor
 *
 * File Name: pir_sensor.h
 *
 * Description: Header file for the PIR sensor driver, providing the necessary
 *              macros, type definitions, and function prototypes to initialize
 *              and retrieve the state of the PIR sensor.
 *
 * Author: Shahd Gamal
 * Created on: Nov 5, 2024
 *
 *******************************************************************************/

#ifndef PIR_SENSOR_H_
#define PIR_SENSOR_H_

#include "std_types.h"  // Include standard data types

/* Enumeration for PIR sensor states */
typedef enum {
    PIR_STATE_NO_MOTION = 0,  /* No motion detected */
    PIR_STATE_MOTION          /* Motion detected */
} PIR_State;

/* Structure to hold PIR sensor configuration settings */
typedef struct {
    uint8 port;  /* Port ID where the PIR sensor is connected */
    uint8 pin;   /* Pin ID for the PIR sensor */
} PIR_t;

extern PIR_t g_pir1;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/*
 * Initializes the PIR sensor by setting the sensor pin as an input.
 */
void PIR_init(PIR_t pir);

/*
 * Checks the state of the PIR sensor to determine if motion is detected.
 */
uint8 PIR_getState(PIR_t pir);

#endif /* PIR_SENSOR_H_ */
