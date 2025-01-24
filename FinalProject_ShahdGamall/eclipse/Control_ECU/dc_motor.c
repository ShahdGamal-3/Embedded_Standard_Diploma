/******************************************************************************
 * Module: DC Motor
 * File Name: dc_motor.c
 * Author: Shahd Gamal
 *******************************************************************************/

#include "dc_motor.h"
#include "avr/io.h"        /* To use the ADC and GPIO Registers */
#include "common_macros.h" /* To use macros like SET_BIT and CLEAR_BIT */
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void DcMotor_Init(void)
{
    /* Set IN1 and IN2 as output pins to control motor direction */
    GPIO_setupPinDirection(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, PIN_OUTPUT);
    GPIO_setupPinDirection(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, PIN_OUTPUT);

    /* Set the enable pin of the H-bridge as input */
    GPIO_setupPinDirection(DC_MOTOR_E_PORT_ID, DC_MOTOR_E_PIN_ID, PIN_OUTPUT);

    /* Ensure motor is stopped at initialization by clearing IN1 and IN2 */

    GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
    GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);

    GPIO_writePin(DC_MOTOR_E_PORT_ID, DC_MOTOR_E_PIN_ID, LOGIC_HIGH);


}

void DcMotor_Rotate(DcMotor_State state)
{
    /* Control motor direction based on the state */
    switch (state) {
        case DC_MOTOR_CW:
        	GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_HIGH);
            break;

        case DC_MOTOR_ACW:
        	GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_HIGH);
			GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
            break;

        case DC_MOTOR_STOP:
        default:
            /* Stop the motor by clearing both IN1 and IN2 */
        	GPIO_writePin(DC_MOTOR_IN1_PORT_ID, DC_MOTOR_IN1_PIN_ID, LOGIC_LOW);
			GPIO_writePin(DC_MOTOR_IN2_PORT_ID, DC_MOTOR_IN2_PIN_ID, LOGIC_LOW);
            break;
    }
}
