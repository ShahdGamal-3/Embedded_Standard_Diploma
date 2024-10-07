/******************************************************************************
 * Module: LDR Sensor
 * File Name: ldr_sensor.h
 * Author: Shahd Gamal
 *******************************************************************************/

#ifndef LDR_SENSOR_H_
#define LDR_SENSOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * Definitions for the LDR sensor.
 * The sensor is connected to a specific ADC channel and has maximum voltage
 * and light intensity values that need to be used for calculations.
 */
#define LDR_SENSOR_CHANNEL_ID             0     /* ADC channel connected to LDR */
#define LDR_SENSOR_MAX_VOLT_VALUE         2.56  /* Maximum voltage output by LDR */
#define LDR_SENSOR_MAX_LIGHT_INTENSITY    100   /* Light intensity percentage (0-100%) */

/* Thresholds for various light intensity ranges (in percentage) */
#define FIRST_INTENSITY_RANGE    15
#define SECOND_INTENSITY_RANGE   50
#define THIRD_INTENSITY_RANGE    70

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * Description :
 * This function reads the analog output from the LDR sensor using the ADC and
 * converts it into a light intensity percentage (0-100%).
 */
uint16 LDR_getLightIntensity(void);

#endif /* LDR_SENSOR_H_ */
