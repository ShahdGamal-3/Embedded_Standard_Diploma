/*******************************************************************************
 * Control.h
 *
 * Created on: Nov 5, 2024
 * Author: Shahd Gamal
 *
 *******************************************************************************/

#ifndef CONTROL_H_
#define CONTROL_H_

// Include necessary header files for the system's components
#include "external_eeprom.h"   // EEPROM functions for password storage
#include "pir_sensor.h"         // PIR sensor functions for motion detection
#include "dc_motor.h"           // DC motor functions for door operation
#include "buzzer.h"             // Buzzer functions for alerts
#include "timer.h"              // Timer functions for delays
#include "uart.h"               // UART functions for communication

// Define constants for various system states and operations
#define PASS_CORRECT    0x00    // Password is correct
#define PASS_WRONG      0x01    // Password is incorrect
#define PASS_WRONG_3    0x05    // Password incorrect 3 times
#define PASS_1_MIN      0x06    // System is locked for 1 minute due to failed attempts
#define OPEN_DOOR       '+'     // Command to open the door
#define CHANGE_PASS     '-'     // Command to change the password
#define PASS_ADDR       0x0000  // EEPROM address for storing the password
#define PASS_LENGTH     5       // Length of the password
#define PEOPLE_ENTERING 0x02    // People entering the door
#define NO_PEOPLE       0x03    // No people detected entering
#define DOOR_CLOSED     0x04    // Door closed status

// Declare global variables used in the system
extern uint8 passCorrect[PASS_LENGTH];   // Store the correct password
extern uint8 pass[PASS_LENGTH];           // Buffer for entered password
extern uint8 pass2[PASS_LENGTH];          // Buffer for confirming entered password
extern uint8 receiveData;                 // Received data for command processing
extern uint8 matchedPassword;             // Flag to indicate if passwords match
extern uint8 wrongPassCount;              // Counter for tracking wrong password attempts
extern volatile uint16 counter;           // Timer counter for delays

// Function prototypes for system operations

/*
 * Function: timer1_interruptHandle
 * Description: ISR for Timer1 interrupt to increment the counter.
 * Parameters: None
 * Returns: None
 */
void timer1_interruptHandle(void);

/*
 * Function: delay
 * Description: Creates a delay based on the provided time in milliseconds.
 * Parameters: timeMs - Time in milliseconds to delay.
 * Returns: None
 */
void delay(uint16 timeMs);

/*
 * Function: initializeSystem
 * Description: Initializes all system components, including the timer, UART,
 *              buzzer, motor, and PIR sensor.
 * Parameters: None
 * Returns: None
 */
void initializeSystem(void);

/*
 * Function: getPasswordFromUser
 * Description: Receives a password from the user via UART.
 * Parameters: passBuffer - Pointer to the buffer to store the received password.
 * Returns: None
 */
void getPasswordFromUser(uint8* passBuffer);

/*
 * Function: storePassword
 * Description: Stores the password in EEPROM and copies it to `passCorrect`
 *              for future verification.
 * Parameters: password - Pointer to the password to store.
 * Returns: None
 */
void storePassword(uint8* password);

/*
 * Function: loadPasswordFromEEPROM
 * Description: Loads the stored password from EEPROM into the `passCorrect`
 *              buffer.
 * Parameters: None
 * Returns: None
 */
void loadPasswordFromEEPROM(void);

/*
 * Function: verifyPassword
 * Description: Compares two passwords and returns TRUE if they match.
 * Parameters: password1 - The first password for comparison.
 *             password2 - The second password for comparison.
 * Returns: TRUE if passwords match, FALSE otherwise.
 */
uint8 verifyPassword(uint8* password1, uint8* password2);

/*
 * Function: handlePasswordSetup
 * Description: Handles the password setup process, prompting the user to
 *              enter and confirm a new password. If passwords match, they are
 *              stored; otherwise, an error is sent.
 * Parameters: None
 * Returns: None
 */
void PasswordSetup(void);

/*
 * Function: PasswordVerification
 * Description: Prompts the user for the old and new passwords to change the
 *              current password. If the old password is correct, the new
 *              password is stored.
 * Parameters: None
 * Returns: None
 */
void PasswordVerification(void);

/*
 * Function: handleDoorOperation
 * Description: Opens and closes the door by rotating the DC motor. It checks
 *              the PIR sensor to detect motion and determine if someone is
 *              entering the door.
 * Parameters: None
 * Returns: None
 */
void handleDoorOperation(void);

/*
 * Function: handlePasswordChange
 * Description: Verifies the entered password. If correct, the system proceeds
 *              to door operations or password change. If incorrect, it triggers
 *              a buzzer and locks the system after multiple wrong attempts.
 * Parameters: None
 * Returns: None
 */
void handlePasswordChange(void);

#endif /* CONTROL_H_ */
