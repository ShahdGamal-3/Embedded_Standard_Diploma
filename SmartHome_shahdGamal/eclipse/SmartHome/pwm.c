/******************************************************************************
 * Module: PWM
 * File Name: pwm.c
 * Author: Shahd Gamal
 *******************************************************************************/

#include "pwm.h"
#include "avr/io.h"  /* To use the AVR IO Registers */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void PWM_Init (void)
{
	 TCNT0 = 0;  // Set Timer Initial Value to 0

	// Set initial compare value for the duty cycle
	OCR0 = 0;

	// Configure PB3/OC0 as output pin for PWM signal
	DDRB |= (1 << PB3); // Set PB3 (OC0) as output

	/* Configure Timer Control Register (TCCR0)
	 * 1. Fast PWM mode: FOC0 = 0 (no force output compare)
	 * 2. Fast PWM Mode: WGM01 = 1 & WGM00 = 1 (select Fast PWM mode)
	 * 3. Clear OC0 on compare match (non-inverting mode): COM00 = 0 & COM01 = 1
	 * 4. Clock source: F_CPU/1024: CS00 = 1, CS01 = 0, CS02 = 1 (prescaler of 1024)
	 */
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS00) | (1 << CS02);
}

void PWM_Timer0_Start(uint8 duty_cycle)
{
	// Calculate and set the Compare value for the duty cycle
	OCR0 = (duty_cycle * MAX_COMPARE_VALUE) / SET_MAX_DUTY_CYCLE; // Set Compare value
}
