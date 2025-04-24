/******************************************************************************
 * Module: Flame Sensor
 * File Name: flame_sensor.h
 * Author: Shahd Gamal
 *******************************************************************************/

#ifndef FLAME_SENSOR_H_
#define FLAME_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * Definitions for the flame sensor's port and pin.
 * The flame sensor is connected to PORTD on PIN2.
 */
#define FLAME_SENSOR_PORT_ID            PORTD_ID
#define FLAME_SENSOR_PIN_ID             PIN2_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * Description :
 * This function configures the GPIO pin connected to the flame sensor as an input pin
 * to allow reading its digital output.
 */
void FlameSensor_init(void);

/**
 * Description :
 * This function reads the digital output from the flame sensor. A high value (1)
 * indicates flame detection, while a low value (0) indicates no flame detected.
 */
uint8 FlameSensor_getValue(void);

#endif /* FLAME_SENSOR_H_ */
