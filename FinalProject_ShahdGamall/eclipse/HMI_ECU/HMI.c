/*******************************************************************************
 * HMI.c
 *
 *  Created on: Nov 5, 2024
 *      Author: Shahd Gamal
 *******************************************************************************/

#include "HMI.h"

// Timer1 interrupt handler, increments the global counter
void timer1_interruptHandle(void) {
    counter++;
}

// Delay function, based on Timer1 interrupt, to create a time delay
void delay(uint16 timeMs) {
    timeMs /= 500;  // Convert time to count units based on Timer1's interrupt rate
    TIMER_reset(TIMER1_ID);  // Reset Timer1
    counter = 0;  // Reset the counter
    while (counter < timeMs);  // Wait until the counter reaches the desired time
}

// Initialize system peripherals and display welcome message
void initSystem(void) {
    TIMER_init(&g_timer1);  // Initialize Timer1
    TIMER_setCallBack(timer1_interruptHandle, TIMER1_ID);  // Set interrupt callback
    UART_init(&g_uart);  // Initialize UART for communication
    LCD_init();  // Initialize LCD for display
    __asm__("SEI");  // Enable global interrupts

    LCD_displayString("Door Lock System");  // Display welcome message
    delay(1000);  // Wait for 1 second before proceeding
}

// Prompt user to enter password and send it via UART
void enterPassword(void) {

    // Read password from keypad
    for (i = 0; i < PASS_LENGTH; ++i) {
        do {
            pass[i] = KEYPAD_getPressedKey();
        } while (!(pass[i] >= 0 && pass[i] <= 9));  // Ensure valid key press

        LCD_displayCharacter('*');  // Display '*' on LCD for each entered character
        delay(500);  // Short delay between key presses
    }

    // Wait for '=' key press to finish password entry
    while (KEYPAD_getPressedKey() != '=');
    delay(500);  // Small delay after password entry
    UART_sendString(pass, PASS_LENGTH);  // Send password to Control ECU
}

// Verify entered password by comparing it with the stored one
void verifyPassword(void) {
	LCD_clearScreen();
	LCD_displayString("Plz Enter Pass:");
	LCD_moveCursor(1, 0);
    enterPassword();  // Prompt user to enter password
    LCD_clearScreen();
    LCD_displayString("Plz re-enter the");
    LCD_displayStringRowColumn(1, 0, "same pass:");

    // Re-enter the password to confirm
    for (i = 0; i < PASS_LENGTH; ++i) {
        pass[i] = KEYPAD_getPressedKey();
        LCD_displayCharacter('*');  // Display '*' for each character entered
        delay(500);
    }

    // Wait for '=' key press to finish password re-entry
    while (KEYPAD_getPressedKey() != '=');
    delay(500);
    UART_sendString(pass, PASS_LENGTH);  // Send re-entered password to Control ECU
    receiveData = UART_recieveByte();  // Receive response (PASS_CORRECT or PASS_WRONG) from Control ECU
}

// Lock the system and display appropriate message
void lockSystem(void) {
    LCD_clearScreen();
    LCD_displayString("System LOCKED");
    LCD_displayStringRowColumn(1, 0, "Wait for 1 min");
    UART_recieveByte();  // Wait for Control ECU to confirm lock
}

// Unlock the door, display messages, and handle motion detection
void unlockDoor(void) {
    LCD_clearScreen();
    LCD_displayString("Door Unlocking");
    LCD_moveCursor(1, 3);
    LCD_displayString("Please Wait");
    receiveData = UART_recieveByte();  // Receive data from Control ECU

    if (receiveData == PEOPLE_ENTERING) {
        LCD_clearScreen();
        LCD_displayString("Wait For People");
        LCD_displayStringRowColumn(1, 0, " To Enter");
        UART_recieveByte();  // Wait until no people are detected
    }

    // Lock the door after people have entered
    LCD_clearScreen();
    LCD_displayString("  Door Locking");
    UART_recieveByte();  // Wait for Control ECU to complete locking
}

// Change password functionality
void changePassword(void) {
	LCD_clearScreen();
	LCD_displayString("Plz Enter Pass:");
	LCD_moveCursor(1, 0);
    enterPassword();  // Prompt user to enter new password
    LCD_clearScreen();
    LCD_displayString("Plz re-enter the");
    LCD_displayStringRowColumn(1, 0, "same pass:");

    // Re-enter the new password
    for (i = 0; i < PASS_LENGTH; ++i) {
        pass[i] = KEYPAD_getPressedKey();
        LCD_displayCharacter('*');  // Display '*' for each key pressed
        delay(500);
    }

    // Wait for '=' key press to finish password re-entry
    while (KEYPAD_getPressedKey() != '=');
    delay(500);
    UART_sendString(pass, PASS_LENGTH);  // Send new password to Control ECU
    receiveData = UART_recieveByte();  // Receive response (PASS_CORRECT or PASS_WRONG) from Control ECU

    // Display result of password change attempt
    LCD_clearScreen();
    if (receiveData == PASS_CORRECT) {
        LCD_displayString("Pass changed");
    } else {
        LCD_displayString("Pass not changed");
    }
    delay(1000);  // Wait for 1 second before returning to main menu
}
