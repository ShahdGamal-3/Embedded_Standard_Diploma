/*******************************************************************************
 * Control.c
 *
 * Created on: Nov 5, 2024
 * Author: Shahd Gamal
 *
 *******************************************************************************/

#include "Control.h"

/*
 * Function: timer1_interruptHandle
 * Description: This interrupt service routine (ISR) handles the timer1 interrupt,
 *              incrementing the counter each time the timer overflows.
 * Parameters: None
 * Returns: None
 */
void timer1_interruptHandle(void) {
    counter++;  // Increment counter on timer interrupt
}

/*
 * Function: delay
 * Description: Creates a delay in milliseconds by using a timer interrupt.
 *              The delay time is adjusted by dividing it by 500,
 *              as the timer is configured to increment the counter every 500 ms.
 * Parameters: timeMs - The delay duration in milliseconds.
 * Returns: None
 */
void delay(uint16 timeMs) {
    timeMs /= 500;  // Convert milliseconds to the timer unit
    TIMER_reset(TIMER1_ID);  // Reset the timer to start counting from 0
    counter = 0;  // Reset the counter
    while (counter < timeMs);  // Wait until the counter reaches the desired time
}

/*
 * Function: initializeSystem
 * Description: Initializes all system components including the timer, UART,
 *              buzzer, motor, and PIR sensor. It also enables global interrupts.
 * Parameters: None
 * Returns: None
 */
void initializeSystem(void) {
    // Initialize the timer and set the interrupt callback
    TIMER_init(&g_timer1);
    TIMER_setCallBack(timer1_interruptHandle, TIMER1_ID);

    // Initialize UART for communication
    UART_init(&g_uart);

    // Initialize peripherals: buzzer, DC motor, PIR sensor
    Buzzer_init(&g_buzzer);
    DcMotor_Init();
    PIR_init(g_pir1);

    __asm__("SEI");  // Enable global interrupts
}

/*
 * Function: getPasswordFromUser
 * Description: Receives a password from the user via UART and stores it in the
 *              provided buffer.
 * Parameters: passBuffer - Pointer to a buffer to store the received password.
 * Returns: None
 */
void getPasswordFromUser(uint8* passBuffer) {
    UART_receiveString(passBuffer, PASS_LENGTH);  // Receive password string from UART
}

/*
 * Function: storePassword
 * Description: Stores the password in EEPROM and copies it to the `passCorrect`
 *              buffer for future verification.
 * Parameters: password - Pointer to the password to be stored.
 * Returns: None
 */
void storePassword(uint8* password) {
    // Write the password to EEPROM
    EEPROM_writeString(PASS_ADDR, password, PASS_LENGTH);

    // Store the password in the `passCorrect` buffer for future verification
    for (uint8 i = 0; i < PASS_LENGTH; i++) {
        passCorrect[i] = password[i];
    }
}

/*
 * Function: loadPasswordFromEEPROM
 * Description: Loads the stored password from EEPROM into the `passCorrect` buffer.
 * Parameters: None
 * Returns: None
 */
void loadPasswordFromEEPROM(void) {
    EEPROM_readString(PASS_ADDR, passCorrect, PASS_LENGTH);  // Read password from EEPROM
}

/*
 * Function: verifyPassword
 * Description: Compares two password buffers and returns TRUE if they match.
 * Parameters: password1 - The first password to compare.
 *             password2 - The second password to compare.
 * Returns: TRUE if the passwords match, FALSE otherwise.
 */
uint8 verifyPassword(uint8* password1, uint8* password2) {
    for (uint8 i = 0; i < PASS_LENGTH; i++) {
        if (password1[i] != password2[i]) {
            return FALSE;  // Passwords do not match
        }
    }
    return TRUE;  // Passwords match
}

/*
 * Function: handlePasswordSetup
 * Description: Handles the password setup process, prompting the user to enter
 *              a new password and confirm it. The password is stored if both
 *              entries match.
 * Parameters: None
 * Returns: None
 */
void PasswordSetup(void) {
    while (matchedPassword == FALSE) {
        // Get the first and second password from the user for confirmation
        getPasswordFromUser(pass);
        getPasswordFromUser(pass2);

        // Verify if the passwords match
        matchedPassword = verifyPassword(pass, pass2);

        if (matchedPassword) {
            // If passwords match, store the new password and send confirmation
            UART_sendByte(PASS_CORRECT);
            storePassword(pass);
        } else {
            // If passwords do not match, send an error and prompt again
            UART_sendByte(PASS_WRONG);
        }
    }
}

/*
 * Function: handlePasswordVerification
 * Description: Prompts the user for a password and verifies it. If the password
 *              is correct, the system proceeds. If incorrect, it counts failed
 *              attempts and triggers a buzzer if the user exceeds the limit.
 * Parameters: None
 * Returns: None
 */
void PasswordVerification(void) {
    // Get the password from the user for verification
    getPasswordFromUser(pass);

    // Verify the password entered by the user
    matchedPassword = verifyPassword(pass, passCorrect);

    if (matchedPassword) {
        // If password is correct, send confirmation and reset attempt counter
        UART_sendByte(PASS_CORRECT);
        wrongPassCount = 0;
    } else {
        // Increment failed attempts
        wrongPassCount++;

        // If more than 2 incorrect attempts, lock system and sound buzzer
        if (wrongPassCount > 2) {
            UART_sendByte(PASS_WRONG_3);
            Buzzer_on(&g_buzzer);  // Turn on the buzzer
            delay(60000);  // Wait for 1 minute (delay in ms)
            Buzzer_off(&g_buzzer);  // Turn off the buzzer
            UART_sendByte(PASS_1_MIN);  // Inform user of 1 minute lock
        } else {
            // If password is incorrect but under 3 attempts, notify the user
            UART_sendByte(PASS_WRONG);
        }
    }
}

/*
 * Function: handleDoorOperation
 * Description: Handles the door operation by rotating the DC motor to open and
 *              close the door. It also detects motion using the PIR sensor to
 *              confirm if people are entering or not.
 * Parameters: None
 * Returns: None
 */
void handleDoorOperation(void) {
    // Rotate the motor to open the door
    DcMotor_Rotate(DC_MOTOR_CW);
    delay(15000);  // Wait for 15 seconds (adjust based on door operation time)

    // Stop the motor after opening
    DcMotor_Rotate(DC_MOTOR_STOP);

    // Check if a person is entering (motion detected by PIR sensor)
    if (PIR_getState(g_pir1) == PIR_STATE_MOTION) {
        UART_sendByte(PEOPLE_ENTERING);
        // Wait until no motion is detected
        while (PIR_getState(g_pir1) == PIR_STATE_MOTION);
    }

    // If no motion detected, notify that no one is entering
    UART_sendByte(NO_PEOPLE);

    // Rotate the motor to close the door
    DcMotor_Rotate(DC_MOTOR_ACW);
    delay(15000);  // Wait for 15 seconds (adjust based on door closing time)

    // Stop the motor after closing
    DcMotor_Rotate(DC_MOTOR_STOP);

    // Send confirmation that the door is closed
    UART_sendByte(DOOR_CLOSED);
}

/*
 * Function: handlePasswordChange
 * Description: Prompts the user to enter the old and new passwords for changing
 *              the current password. If the old password is correct, it updates
 *              the password.
 * Parameters: None
 * Returns: None
 */
void handlePasswordChange(void) {
    // Get the old and new passwords from the user for verification and change
    getPasswordFromUser(pass);
    getPasswordFromUser(pass2);

    // Verify if the old and new passwords match
    matchedPassword = verifyPassword(pass, pass2);

    if (matchedPassword) {
        // If passwords match, store the new password and confirm
        UART_sendByte(PASS_CORRECT);
        storePassword(pass);
    } else {
        // If passwords do not match, notify the user
        UART_sendByte(PASS_WRONG);
    }
}
