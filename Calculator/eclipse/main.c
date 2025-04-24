/*
 * main.c
 *
 *  Created on: Oct 6, 2024
 *      Author: shahd
 */

#include "keypad.h"
#include "lcd.h"
#include <util/delay.h>

#define ASCII_OF_CLEAR_BUTTON  13

uint8 key ;
float32 num1 = 0 , num2 = 0 ;
float32 result = 0 ;
uint8 operator = 0 ;

void LCD_calcOperationResult (float32 num1, float32 num2,uint8 operator)
{
	switch(operator)
	{
	case '+':
		LCD_moveCursor(1,0);
		LCD_displayString("Ans = ");
		result = first_number + second_number ;
		break;

	case '-':
		LCD_moveCursor(1,0);
		LCD_displayString("Ans = ");
		result = first_number - second_number ;
		break;

	case '*':
		LCD_moveCursor(1,0);
		LCD_displayString("Ans = ");
		result = first_number * second_number ;
		break;

	case '/':
		if(second_number != 0 )
		{
			LCD_moveCursor(1,0);
			LCD_displayString("Ans = ");
			result = first_number / second_number ;
		}
		else
		{
			LCD_moveCursor(1,0);
			LCD_displayString("Error: Divide by 0 !!");
		}
		break;

	default:
		LCD_moveCursor(1,0);
		LCD_displayString("NO operator !!");
		break;
	}
}


int main (void)
{
	LCD_init();
	LCD_displayString(" Calculator ON ");
	_delay_ms(1000);
	LCD_clearScreen();

	while(1)
	{
		key = KEYPAD_getPressedKey();
		if ( (key >=0)  && (key <= 9) )
		{
			LCD_intgerToString(key) ;
			num2 = ( (num2 * 10) + key ) ;
		}

		else if ( key == '+' || key == '-' || key == '*' || key == '/' )
		{
			LCD_displayCharacter(key);
			operator = key ;
			num1 = num2 ;
			num2 = 0 ;
		}

		else if (key == '=')
		{
			LCD_calcOperationResult (num1, num2, operator);
			LCD_floatToString(result);
		}

		else if (key == ASCII_OF_CLEAR_BUTTON)
		{
			LCD_clearScreen();
			num1 = num2 = 0 ;
			operator = 0 ;
		}

			_delay_ms(500);
	}

}
