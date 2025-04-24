/******************************************************************************
 * Module: PWM
 * File Name: pwm.h
 * Author: Shahd Gamal
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * Temperature Range Definitions
 * These constants define different temperature ranges for application-specific behavior.
 */
#define FIRST_TEMP_RANGE         25  /* Temperature range 1 threshold (°C) */
#define SECOND_TEMP_RANGE        30  /* Temperature range 2 threshold (°C) */
#define THIRD_TEMP_RANGE         35  /* Temperature range 3 threshold (°C) */
#define FOURTH_TEMP_RANGE        40  /* Temperature range 4 threshold (°C) */

/*
 * Duty Cycle Definitions
 * These constants define various duty cycle settings for PWM.
 */
#define SET_MAX_DUTY_CYCLE       100 /* Maximum duty cycle percentage */
#define SET_75_DUTY_CYCLE        75  /* 75% duty cycle */
#define SET_50_DUTY_CYCLE        50  /* 50% duty cycle */
#define SET_25_DUTY_CYCLE        25  /* 25% duty cycle */
#define SET_0_DUTY_CYCLE         0   /* 0% duty cycle */

/*
 * PWM Configuration Constants
 * Defines the maximum compare value for Timer0.
 */
#define MAX_COMPARE_VALUE        255 /* Maximum compare value for PWM generation */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * Description :
 * This function sets up Timer0 to generate a PWM signal.
 */
void PWM_Init (void);

/**
 * Description :
 * This function sets up Timer0 to generate a PWM signal with a specified duty cycle.
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
