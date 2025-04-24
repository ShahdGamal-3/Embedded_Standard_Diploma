/*******************************************************************************
 *
 * Module: Main Control Unit (Control_ECU)
 *
 * File Name: control_main.c
 *
 * Description: Main program for the Control_ECU in a dual microcontroller door
 *              locking system. This program handles password verification,
 *              door operations (open/close), and password change functionality.
 *
 * Created on: Nov 5, 2024
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/

#include "Control.h"

// Declare global variables used in the system
uint8 passCorrect[PASS_LENGTH];    // Store the correct password
uint8 pass[PASS_LENGTH];           // Buffer for entered password
uint8 pass2[PASS_LENGTH];          // Buffer for confirming entered password
uint8 receiveData;                 // Received data for command processing
uint8 matchedPassword;             // Flag to indicate if passwords match
uint8 wrongPassCount;              // Counter for tracking wrong password attempts
volatile uint16 counter;           // Timer counter for delays

/*
 * Function: main
 * Description: The main function initializes the control system, loads the
 *              password from EEPROM, and manages the core operations of the
 *              door locking system. It continuously listens for commands (open
 *              door or change password) and performs password verification
 *              before executing the requested action.
 * Parameters: None
 * Returns: 0 (Program does not return since it runs indefinitely in a loop)
 */
int main(void) {
    // Initialize system components (UART, peripherals, etc.)
    initializeSystem();

    // Load the stored password from EEPROM for future verification
    loadPasswordFromEEPROM();

    // Handle the initial password setup if needed
    PasswordSetup();

    // Main program loop: continuously listens for commands
    while (1) {
        // Receive a byte of data (command) from the user
        receiveData = UART_recieveByte();

        // If the received command is for opening the door or changing the password
        if (receiveData == OPEN_DOOR || receiveData == CHANGE_PASS) {
            // Perform password verification before proceeding with the operation
            PasswordVerification();

            // If the entered password matches the stored password
            if (matchedPassword == TRUE) {
                // Handle the specific operation based on the received command
                switch (receiveData) {
                    case OPEN_DOOR:
                        // Perform the operation to open the door
                    	handleDoorOperation();
                        break;

                    case CHANGE_PASS:
                        // Perform the operation to change the password
                    	handlePasswordChange();
                        break;
                }
            }
        }
    }

    return 0;  // Program does not return from this infinite loop
}
