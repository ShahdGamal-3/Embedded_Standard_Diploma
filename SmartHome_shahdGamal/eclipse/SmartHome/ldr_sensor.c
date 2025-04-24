/******************************************************************************
 * Module: LDR Sensor
 * File Name: ldr_sensor.c
 * Author: Shahd Gamal
 *******************************************************************************/

#include "ldr_sensor.h"
#include "adc.h"  /* Include the ADC driver to read analog values */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

uint16 LDR_getLightIntensity(void)
{
    /* Read the analog value from the LDR sensor channel */
    uint16 adc_value = ADC_readChannel(LDR_SENSOR_CHANNEL_ID);

    /* Calculate the light intensity as a percentage based on the ADC reading */
    uint16 light_intensity = (uint16)(((uint32)adc_value * LDR_SENSOR_MAX_LIGHT_INTENSITY * ADC_REF_VOLT_VALUE)
                                      / (ADC_MAXIMUM_VALUE * LDR_SENSOR_MAX_VOLT_VALUE));

    /* Return the calculated light intensity */
    return light_intensity;
}
