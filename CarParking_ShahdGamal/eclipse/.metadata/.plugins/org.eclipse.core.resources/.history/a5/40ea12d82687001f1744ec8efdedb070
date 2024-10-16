/******************************************************************************
 * Module: Buzzer
 * File Name: buzzer.h
 * Author: Shahd Gamal
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/*
 * Definitions for the buzzer's port and pin.
 * The buzzer is connected to PORTD on PIN3.
 */
#define BUZZER_PORT_ID           PORTD_ID
#define BUZZER_LED_PIN_ID        PIN3_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/**
 * Description :
 * This function configures the GPIO pin connected to the buzzer as output
 * and ensures the buzzer is initially turned off.
 */
void Buzzer_init(void);

/**
 * Description :
 * This function sets the buzzer pin to a high state, activating the buzzer.
 */
void Buzzer_on(void);

/**
 * Description :
 * This function sets the buzzer pin to a low state, deactivating the buzzer.
 */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
