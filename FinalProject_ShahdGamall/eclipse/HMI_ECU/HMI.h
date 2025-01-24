/*******************************************************************************
 * HMI.h
 *
 *  Created on: Nov 5, 2024
 *      Author: Shahd Gamal
 *******************************************************************************/


#ifndef HMI_H_
#define HMI_H_

#include "Keypad.h"
#include "timer.h"
#include "uart.h"
#include "LCD.h"

// Password related constants
#define PASS_CORRECT  0x00  // Correct password received
#define PASS_WRONG    0x01  // Incorrect password received
#define PASS_WRONG_3  0x05  // Incorrect password received 3 times (lockout)

// Key actions for controlling the door
#define OPEN_DOOR     '+'   // Key for opening the door
#define CHANGE_PASS   '-'   // Key for changing the password

// Password length definition
#define PASS_LENGTH   5     // Number of characters in the password

// States for PIR sensor detection
#define PEOPLE_ENTERING  0x02  // People detected (motion detected)
#define NO_PEOPLE        0x03  // No people detected

// Global variables (ensure to declare 'extern' in other files where needed)
extern uint8 pass[PASS_LENGTH];       // Buffer to hold the password
extern uint8 receiveData;             // Data received from Control ECU
extern uint8 i;                       // Loop index
extern volatile uint16 counter;       // Timer interrupt counter

// Function prototypes
void initSystem(void);                // Initialize system components
void delay(uint16 timeMs);            // Time delay function based on Timer1 interrupt
void enterPassword(void);             // Prompt user to enter password
void verifyPassword(void);            // Verify entered password with stored password
void lockSystem(void);                // Lock the system after incorrect attempts
void unlockDoor(void);                // Unlock the door if password is correct
void changePassword(void);            // Change the password if verified
void timer1_interruptHandle(void);    // Timer interrupt handler

#endif /* HMI_H_ */
