/******************************************************************************
 *
 * Module: HMI (Human-Machine Interface)
 *
 * File Name: HMI_main.c
 *
 * Description: Main file for the Human-Machine Interface (HMI) system. This file
 *              handles the user interactions for controlling a door, verifying
 *              passwords, and changing the password. It provides an interface
 *              for the keypad and the LCD screen.
 *
 * Created on: Nov 5, 2024
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/

#include "HMI.h"

// Global variables (ensure to declare 'extern' in other files where needed)
uint8 pass[PASS_LENGTH];       // Buffer to hold the password
uint8 receiveData;             // Data received from Control ECU
uint8 i;                       // Loop index
volatile uint16 counter;       // Timer interrupt counter

/*
 * Function: main
 * Description: The main function initializes the system and continuously runs the
 *              door control interface. It verifies the password, provides options
 *              to open the door or change the password, and interacts with the
 *              keypad and LCD. The system locks after 3 failed password attempts.
 * Parameters: None
 * Returns: 0 (Program does not return since it enters an infinite loop)
 */
int main(void) {
    // Initialize the system components (LCD, keypad, UART, etc.)
    initSystem();

    // Initialize the password status to indicate incorrect password
    receiveData = PASS_WRONG;

    // Initial password verification loop
    // Continue prompting for password until it's correct
    while (receiveData == PASS_WRONG) {
        verifyPassword();
    }

    // Main interface loop: provides options to the user
    while (1) {
        // Clear the LCD and display the options
        LCD_clearScreen();
        LCD_displayString("+ : OPEN DOOR");
        LCD_displayStringRowColumn(1, 0, "- : CHANGE PASS");

        uint8 inputKey;
        // Wait for the user to press a valid key ('+' or '-')
        do {
            inputKey = KEYPAD_getPressedKey();
        } while (inputKey != '+' && inputKey != '-');

        // Reset the password verification status
        receiveData = PASS_WRONG;

        // Prompt user for password verification
        while (receiveData == PASS_WRONG) {
            // Send the user's choice ('+' for open door, '-' for change password)
            UART_sendByte(inputKey);

            // Clear the LCD and prompt for the old password
            LCD_clearScreen();
            LCD_displayString("Plz enter old");
            LCD_displayStringRowColumn(1, 0, "pass:");
            enterPassword();

            // Receive the password status (correct or wrong)
            receiveData = UART_recieveByte();
            if (receiveData == PASS_WRONG_3) {
                // Lock the system after 3 incorrect attempts
                lockSystem();
                break;
            }
        }

        // If the password is correct, perform the requested action
        if (receiveData == PASS_CORRECT) {
            switch (inputKey) {
                case OPEN_DOOR:
                    // Unlock the door if the user chose to open it
                    unlockDoor();
                    break;

                case CHANGE_PASS:
                    // Change the password if the user chose to do so
                    changePassword();
                    break;
            }
        }
    }

    return 0;  // Program will not return from the infinite loop
}
