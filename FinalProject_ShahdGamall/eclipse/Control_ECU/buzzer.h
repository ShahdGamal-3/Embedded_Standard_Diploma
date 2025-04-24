/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the AVR Buzzer driver
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"  /* Include standard data types */

/*******************************************************************************
 *                              Types Declaration                              *
 *******************************************************************************/

/*
 * Buzzer Configuration Structure:
 * - This structure holds the port and pin number where the buzzer is connected.
 * - The port and pin fields are limited to the required bits to save memory.
 */
typedef struct {
  uint8 BUZZER_port :2; /* Port number where the buzzer is connected (2 bits) */
  uint8 BUZZER_pin :3;  /* Pin number where the buzzer is connected (3 bits) */
} BUZZER_ConfigType;

extern BUZZER_ConfigType g_buzzer;  /* Extern declaration for global buzzer configuration */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * Description :
 * Function to initialize the buzzer by configuring the GPIO pin as output.
 * - This function also ensures the buzzer is initially turned off.
 */
void Buzzer_init(const BUZZER_ConfigType * BUZZER_Config_Ptr);

/**
 * Description :
 * Function to turn on the buzzer.
 * - This function sets the buzzer pin to a high state, which activates the buzzer.
 */
void Buzzer_on(const BUZZER_ConfigType * BUZZER_Config_Ptr);

/**
 * Description :
 * Function to turn off the buzzer.
 * - This function sets the buzzer pin to a low state, which deactivates the buzzer.
 */
void Buzzer_off(const BUZZER_ConfigType * BUZZER_Config_Ptr);

#endif /* BUZZER_H_ */
