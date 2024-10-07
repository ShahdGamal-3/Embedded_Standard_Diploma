/*
 * main.c
 *
 * Created on: Oct 6, 2024
 * Author: shahd
 *
 * This program implements a simple calculator using a keypad and LCD.
 */

#include "keypad.h"
#include "lcd.h"
#include <util/delay.h>

/* Define the ASCII code for the clear button */
#define ASCII_OF_CLEAR_BUTTON  13

/* Global variables for storing input numbers, result, and operator */
uint8 key;
float32 num1 = 0, num2 = 0;
float32 result = 0;
uint8 operator = 0;

/*
 * Function: LCD_calcOperationResult
 * ----------------------------------
 * This function calculates the result of the operation based on the
 * input numbers and operator.
 */
void LCD_calcOperationResult(float32 num1, float32 num2, uint8 operator)
{
    switch (operator)
    {
    case '+':
        LCD_moveCursor(1, 0);
        LCD_displayString("Ans = ");
        result = num1 + num2;  /* Perform addition */
        break;

    case '-':
        LCD_moveCursor(1, 0);
        LCD_displayString("Ans = ");
        result = num1 - num2;  /* Perform subtraction */
        break;

    case '*':
        LCD_moveCursor(1, 0);
        LCD_displayString("Ans = ");
        result = num1 * num2;  /* Perform multiplication */
        break;

    case '/':
        if (num2 != 0)
        {
            LCD_moveCursor(1, 0);
            LCD_displayString("Ans = ");
            result = num1 / num2;  /* Perform division */
        }
        else
        {
            LCD_moveCursor(1, 0);
            LCD_displayString("Error:Divide by0");  /* Handle division by zero */
        }
        break;

    default:
        LCD_moveCursor(1, 0);
        LCD_displayString("NO operator !!   ");  /* Handle invalid operator */
        break;
    }
}

/*
 * Function: main
 * --------------
 * Main function that initializes the LCD and implements the main loop
 * for the calculator. It continuously checks the pressed key from the
 * keypad and updates the input numbers and operators accordingly.
 */
int main(void)
{
    LCD_init();  /* Initialize the LCD */
    LCD_displayString(" Calculator ON ");  /* Display initial message */
    _delay_ms(1000);
    LCD_clearScreen();  /* Clear the screen after the message */

    while (1)
    {
        key = KEYPAD_getPressedKey();  /* Get the pressed key from the keypad */

        /* Handle number input */
        if ((key >= 0) && (key <= 9))
        {
            LCD_intgerToString(key);  /* Display the number on the LCD */
            num2 = ((num2 * 10) + key);  /* Update the second number */
        }

        /* Handle operator input */
        else if (key == '+' || key == '-' || key == '*' || key == '/')
        {
            LCD_displayCharacter(key);  /* Display the operator on the LCD */
            operator = key;  /* Store the operator */
            num1 = num2;  /* Move num2 to num1 for the next operation */
            num2 = 0;  /* Reset num2 for the next input */
        }

        /* Handle equals key to calculate and display the result */
        else if (key == '=')
        {
            LCD_calcOperationResult(num1, num2, operator);  /* Calculate result */
            LCD_floatToString(result);  /* Display the result */
        }

        /* Handle clear button to reset everything */
        else if (key == ASCII_OF_CLEAR_BUTTON)
        {
            LCD_clearScreen();  /* Clear the LCD screen */
            num1 = num2 = 0;  /* Reset both numbers */
            operator = 0;  /* Reset the operator */
        }

        _delay_ms(500);  /* Delay for debounce or user interaction */
    }
}
