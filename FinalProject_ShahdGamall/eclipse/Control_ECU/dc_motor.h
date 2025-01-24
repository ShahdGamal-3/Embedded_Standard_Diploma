/******************************************************************************
 * Module: DC Motor
 * File Name: dc_motor.h
 * Author: Shahd Gamal
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * Definitions for DC motor control pins.
 * The motor uses two control pins (IN1 and IN2) and an enable pin connected to H-bridge.
 */
#define DC_MOTOR_IN1_PORT_ID            PORTD_ID
#define DC_MOTOR_IN1_PIN_ID             PIN6_ID

#define DC_MOTOR_IN2_PORT_ID            PORTD_ID
#define DC_MOTOR_IN2_PIN_ID             PIN7_ID

#define DC_MOTOR_E_PORT_ID              PORTB_ID
#define DC_MOTOR_E_PIN_ID               PIN3_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/**
 * Description :
 * DC_MOTOR_CW: Clockwise rotation.
 * DC_MOTOR_ACW: Anti-clockwise rotation.
 * DC_MOTOR_STOP: Stop the motor.
 */
typedef enum
{
    DC_MOTOR_CW,      /* Clockwise rotation */
    DC_MOTOR_ACW,     /* Anti-clockwise rotation */
    DC_MOTOR_STOP     /* Stop motor */
} DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * Description :
 * This function sets the control pins (IN1 and IN2) as outputs and the enable pin
 * of the H-bridge as an input. It also ensures the motor is stopped initially.
 */
void DcMotor_Init(void);

/**
 * Description :
 * This function controls the motor's rotation direction (clockwise, anti-clockwise, or stop)
 * and adjusts the motor's speed by using PWM to control the duty cycle.
 */
void DcMotor_Rotate(DcMotor_State state);

#endif /* DC_MOTOR_H_ */
