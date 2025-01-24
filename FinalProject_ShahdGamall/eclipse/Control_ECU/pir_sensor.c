/******************************************************************************
 *
 * Module Name: PIR Sensor
 *
 * File Name: PIRsensor.c
 *
 * Description: Source file for the PIR (Passive Infrared) sensor driver,
 *              providing initialization and state-checking functions to detect
 *              motion within the sensor’s range.
 *
 * Author: Shahd Gamal
 * Created on: Nov 5, 2024
 *
 *******************************************************************************/

#include "pir_sensor.h"
#include <avr/io.h>
#include "gpio.h"
#include "common_macros.h"

/*
 * Global instance for the PIR sensor configuration with
 * specific port and pin settings for motion detection.
 */
PIR_t g_pir1 = { .port = PORTC_ID, .pin = PIN2_ID };

/*
 * Initializes the specified PIR sensor by setting the pin as an input.
 */
void PIR_init(PIR_t pir) {
    /* Set the PIR sensor pin as input */
    GPIO_setupPinDirection(pir.port, pir.pin, PIN_INPUT);
}

/*
 * Reads the state of the PIR sensor to check for motion.
 */
uint8 PIR_getState(PIR_t pir) {
    /* Check if the PIR sensor pin is HIGH (motion detected) */
    if (LOGIC_HIGH == GPIO_readPin(pir.port, pir.pin)) {
        return PIR_STATE_MOTION;
    } else {
        return PIR_STATE_NO_MOTION;
    }
}
