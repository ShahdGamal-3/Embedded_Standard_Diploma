/******************************************************************************
 * Module: Flame Sensor
 * File Name: flame_sensor.c
 * Author: Shahd Gamal
 *******************************************************************************/

#include "flame_sensor.h"
#include "gpio.h"
#include "avr/io.h"        /* To use the I/O Ports Registers */
#include "common_macros.h" /* To use macros like GET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void FlameSensor_init(void)
{
    /* Configure the flame sensor pin as an input */
    GPIO_setupPinDirection(FLAME_SENSOR_PORT_ID, FLAME_SENSOR_PIN_ID, PIN_INPUT);
}

uint8 FlameSensor_getValue(void)
{
    /* Return the digital value of the flame sensor pin (1 for flame, 0 for no flame) */
    return GET_BIT(PIND, PD2);
}
