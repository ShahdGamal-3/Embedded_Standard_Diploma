/*
 * Name        : Interfacing1_project
 * Author      : Shahd Gamal
 * Date        : 12/9/2024
 * Description : StopWatch with Dual Mode (Increment and Decrement)
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Button and display macros
#define MODE_BUTTON_PRESSED              (!(PINB & (1<<PB7))) // Mode toggle button (Decrement mode)
#define BUTTON_INCREMENT_SECONDS_PRESSED (!(PINB & (1<<PB6))) // Increment seconds button
#define BUTTON_DECREMENT_SECONDS_PRESSED (!(PINB & (1<<PB5))) // Decrement seconds button
#define BUTTON_INCREMENT_MINUTES_PRESSED (!(PINB & (1<<PB4))) // Increment minutes button
#define BUTTON_DECREMENT_MINUTES_PRESSED (!(PINB & (1<<PB3))) // Decrement minutes button
#define BUTTON_INCREMENT_HOURS_PRESSED   (!(PINB & (1<<PB1))) // Increment hours button
#define BUTTON_DECREMENT_HOURS_PRESSED   (!(PINB & (1<<PB0))) // Decrement hours button

// Display and buzzer control macros
#define DISABLE_ALL_SEGMENTS             (PORTA & (0xC0))     // Disable all 7-segment displays
#define DISPLAY_ZERO                     (PORTC & (0xF0))     // Clear display
#define DISABLE_BUZZER                   (PORTD &= ~(1<<PD0)) // Turn off buzzer
#define ENABLE_BUZZER                    (PORTD |= (1<<PD0))  // Activate buzzer

// Timer-related constants
#define COMPARE_VALUE                    15624 // Using pre-scaler = 1024 to count 1 second at 16MHz
#define DELAY_FOR_SEGMENTS               2     // 2 ms delay for segment display multiplexing
#define GLOBAL_INTERRUPT_ENABLE_BIT      7
#define INITIAL_VALUE_FOR_TIMER1         0
#define INCREMENT_MODE                   0
#define DECREMENT_MODE                   1

// Display calculations
#define DISPLAY_UNITS(x) ((x) % 10)
#define DISPLAY_TENS(x)  ((x) / 10)

// Flags for button states and modes
unsigned char seconds_Increment_flag = 0;
unsigned char seconds_Decrement_flag = 0;
unsigned char minutes_Increment_flag = 0;
unsigned char minutes_Decrement_flag = 0;
unsigned char hours_Increment_flag = 0;
unsigned char hours_Decrement_flag = 0;
unsigned char mode_flag = 0;
unsigned char pause_flag = 0;
unsigned char tick_Timer1 = 0;
unsigned char mode = 0;

// Structure to hold stopwatch time values
struct stopWatch {
    unsigned char hours, minutes, seconds;
} time;

/***************************************************************
 * Functions declarations.
 ***************************************************************/
void Increment_Time(void);
void Decrement_Time(void);
void Timer1_stopWatchTime_Init (void);
void Reset_INT0_Init (void);
void Pause_INT1_Init (void);
void Resume_INT2_Init (void);
void Seven_Segment_Init (void);
void Time_Adjustment_Buttons_Init (void);
void Count_Mode_Buttons_Init (void);
void Count_Mode_Leds_Init (void);
void Buzzer_Init (void);
void Display_Time(void);
void Timer_Mode(void);
void Update_Time (void);
void Seconds_Adjustment(void);
void Minutes_Adjustment(void);
void Hours_Adjustment(void);

/***************************************************************
 * Main Function
 ***************************************************************/
int main(void) {
    // Initialize all components
    Timer1_stopWatchTime_Init();
    Reset_INT0_Init();
    Pause_INT1_Init();
    Resume_INT2_Init();
    Seven_Segment_Init();
    Time_Adjustment_Buttons_Init();
    Count_Mode_Buttons_Init();
    Count_Mode_Leds_Init();
    Buzzer_Init();

    // Enable global interrupts
    SREG |= (1 << GLOBAL_INTERRUPT_ENABLE_BIT);

    // Main loop
    while (1) {
        Display_Time();            // Update the 7-segment display
        if (pause_flag) {
        	Seconds_Adjustment(); // Adjust seconds
			Minutes_Adjustment(); // Adjust minutes
			Hours_Adjustment();   // Adjust hours
        }
        Timer_Mode();            // Handle mode switching

        // Handle Timer1 tick to avoid overflow
		if (tick_Timer1) {
			Update_Time ();
			tick_Timer1--;
		}
    }

    return 0;
}

/***************************************************************
 * Interrupt Service Routines (ISRs) for external events.
 ***************************************************************/

// ISR for Reset (INT0)
ISR(INT0_vect) {
    // Reset time to (00:00:00)
    time.hours = 0;
    time.minutes = 0;
    time.seconds = 0;
}

// ISR for Pause (INT1)
ISR(INT1_vect) {
	pause_flag =1;                                  // Indicates that time is paused
    TCCR1B &= ~(1<<CS10) & ~(1<<CS11) & ~(1<<CS12); // Stop timer (no clock source)
    DISABLE_BUZZER;                                 // Turn off the buzzer
}

// ISR for Resume (INT2)
ISR(INT2_vect) {
	pause_flag =0;                   // Indicates that time is resumed
    TCCR1B |= (1<<CS10) | (1<<CS12); // Resume timer with pre-scaler = 1024
}

// ISR for Timer1 Compare Match A
ISR(TIMER1_COMPA_vect) {
    tick_Timer1++;
}

/***************************************************************
 * Initialization functions.
 ***************************************************************/

void Timer1_stopWatchTime_Init (void)
{
	TCCR1B = (1<<WGM12) | (1<<CS10) | (1<<CS12); // Set CTC mode, and pre-scaler = 1024
	OCR1A = COMPARE_VALUE;
	TCNT1 = INITIAL_VALUE_FOR_TIMER1;            // Initial value of timer
	TIMSK |= (1<<OCIE1A);                        // Compare A Match Interrupt Enable
}

void Reset_INT0_Init (void)
{
	DDRD &= ~(1<<PD2);   // Set input pin for bush button
	PORTD |= (1<<PD2);   // Enable internal pull-up resistor
	MCUCR |= (1<<ISC01); // Set that falling edge of INT0 generates an interrupt request
	GICR |= (1<<INT0);   // Enable external Interrupt Request INT0
	GIFR |= (1<<INTF0);  // Clear INT0 interrupt flag
}

void Pause_INT1_Init (void)
{
	DDRD &= ~(1<<PD3);               // Set input pin for bush button
	MCUCR = (1<<ISC10) | (1<<ISC11); // Set that rising edge of INT1 generates an interrupt request
	GICR |= (1<<INT1);               // Enable external Interrupt Request INT1
	GIFR |= (1<<INTF1);              // Clear INT1 interrupt flag
}

void Resume_INT2_Init (void)
{
	DDRB &= ~(1<<PB2);  // Set input pin for bush button
	PORTB |= (1<<PB2);  // Enable internal pull-up resistor
	GICR |= (1<<INT2);  // Enable external Interrupt Request INT2
	GIFR |= (1<<INTF2); // Clear INT2 interrupt flag
}

void Seven_Segment_Init (void)
{
	DDRC |= 0X0F;         // Set first 4-pins in PORTC output pins for decoder
	PORTC = DISPLAY_ZERO; // Initialize decoder to display 0
	DDRA |= 0X3F;         // Set first 6-pins in PORTA output pins for enable six 7-segments
	PORTA |= 0x3F;        // Enable all segments
}

void Time_Adjustment_Buttons_Init (void)
{
	DDRB &= 0X84;  // Set pins PB0,PB1,PB3,PB4,PB5,PB6 input pins for bush-buttons
	PORTB |= 0x7B; // Enable internal pull-up resistor
}

void Count_Mode_Buttons_Init (void)
{
	DDRB &= ~(1<<PB7); // Set input pin for toggle-mode button
	PORTB |= (1<<PB7); // Enable internal pull-up resistor
}

void Count_Mode_Leds_Init (void)
{
	DDRD |= (1<<PC4) | (1<<PC5);            //Set output pins for toggle-mode leds
	PORTD = (PORTD | (1<<PD4)) & ~(1<<PD5); // Turn on PD4 and turn off PD5
}

void Buzzer_Init (void)
{
	DDRD |= (1<<PD0); // Set output pin for buzzer
	DISABLE_BUZZER;   // Set buzzer off
}

/***************************************************************
 * Functions Definitions
 ***************************************************************/

/***************************************************************
 * Time display and adjustment functions
 ***************************************************************/

// Display time on 7-segment display
void Display_Time(void) {
    // Multiplex between segments and display the time values
    PORTA = DISABLE_ALL_SEGMENTS | 0x20; // 1st segment of seconds
    PORTC = DISPLAY_ZERO | DISPLAY_UNITS(time.seconds);
    _delay_ms(DELAY_FOR_SEGMENTS);

    PORTA = DISABLE_ALL_SEGMENTS | 0x10; // 2nd segment of seconds
    PORTC = DISPLAY_ZERO | DISPLAY_TENS(time.seconds);
    _delay_ms(DELAY_FOR_SEGMENTS);

    PORTA = DISABLE_ALL_SEGMENTS | 0x08; // 1st segment of minutes
    PORTC = DISPLAY_ZERO | DISPLAY_UNITS(time.minutes);
    _delay_ms(DELAY_FOR_SEGMENTS);

    PORTA = DISABLE_ALL_SEGMENTS | 0x04; // 2nd segment of minutes
    PORTC = DISPLAY_ZERO | DISPLAY_TENS(time.minutes);
    _delay_ms(DELAY_FOR_SEGMENTS);

    PORTA = DISABLE_ALL_SEGMENTS | 0x02; // 1st segment of hours
    PORTC = DISPLAY_ZERO | DISPLAY_UNITS(time.hours);
    _delay_ms(DELAY_FOR_SEGMENTS);

    PORTA = DISABLE_ALL_SEGMENTS | 0x01; // 2nd segment of hours
    PORTC = DISPLAY_ZERO | DISPLAY_TENS(time.hours);
    _delay_ms(DELAY_FOR_SEGMENTS);
}

/***************************************************************
 * Function: Toggles between Increment and Decrement modes.
 ***************************************************************/
void Timer_Mode(void) {
    if (MODE_BUTTON_PRESSED) {           // Check if mode toggle button is pressed
        if (mode_flag == 0) {            // Toggle only when the button is pressed once
            if (mode == INCREMENT_MODE) {
                mode = DECREMENT_MODE;
                PORTD |= (1<<PD5);       // Yellow LED on for Decrement Mode
                PORTD &= ~(1<<PD4);      // Red LED off for Increment Mode
            } else {
                mode = INCREMENT_MODE;
                PORTD |= (1<<PD4);       // Red LED on for Increment Mode
                PORTD &= ~(1<<PD5);      // Yellow LED off for Decrement Mode
            }
            mode_flag = 1;               // Prevent toggling until the button is released
        }
    } else {
        mode_flag = 0;                  // Reset flag when the button is released
    }
}

/***************************************************************
 * Function: Change Time with (Increment / Decrement) mode.
 ***************************************************************/
void Update_Time (void)
{
	if (mode == INCREMENT_MODE) {
		DISABLE_BUZZER; // Set buzzer off
		Increment_Time();
	} else if (mode == DECREMENT_MODE) {
		Decrement_Time();
	}
}

/***************************************************************
 * Function: Increments the stopwatch time.
 ***************************************************************/
void Increment_Time(void) {
    time.seconds++;
    if (time.seconds >= 60) {
        time.seconds = 0;
        time.minutes++;
        if (time.minutes >= 60) {
            time.minutes = 0;
            time.hours++;
        }
    }
}

/***************************************************************
 * Function: Decrements the stopwatch time.
 ***************************************************************/
void Decrement_Time(void) {
    if (time.seconds > 0) {
        time.seconds--;
    } else if (time.minutes > 0 || time.hours > 0) {
        time.seconds = 59;
        if (time.minutes > 0) {
            time.minutes--;
        } else if (time.hours > 0) {
            time.minutes = 59;
            time.hours--;
        }
    } else if (mode == DECREMENT_MODE) {
        ENABLE_BUZZER; // Buzzer on when countdown reaches 0
    }
}

/***************************************************************
 * Function: Seconds Buttons Handling
 ***************************************************************/
void Seconds_Adjustment(void) {
    if (BUTTON_INCREMENT_SECONDS_PRESSED) { // Check if increment button is pressed
        if (time.seconds >= 60) {
            time.seconds = 0;
            if (time.minutes <59)
                time.minutes++;
        } else if (seconds_Increment_flag == 0) {
            time.seconds++;
            seconds_Increment_flag = 1; // Prevent repeated increments
        }
    } else {
        seconds_Increment_flag = 0;
    }

    if (BUTTON_DECREMENT_SECONDS_PRESSED && time.seconds > 0) { // Check if decrement button is pressed
        if (seconds_Decrement_flag == 0) {
            time.seconds--;
            seconds_Decrement_flag = 1; // Prevent repeated decrements
        }
    } else {
        seconds_Decrement_flag = 0;
    }
}

/***************************************************************
 * Function: Minutes Buttons Handling
 ***************************************************************/
void Minutes_Adjustment(void) {
    if (BUTTON_INCREMENT_MINUTES_PRESSED) { // Check if increment button is pressed
        if (time.minutes >= 60) {
            time.minutes = 0;
            if (time.hours <23)
                time.hours++;
        } else if (minutes_Increment_flag == 0) {
            time.minutes++;
            minutes_Increment_flag = 1; // Prevent repeated increments
        }
    } else {
        minutes_Increment_flag = 0;
    }

    if (BUTTON_DECREMENT_MINUTES_PRESSED && time.minutes > 0) { // Check if decrement button is pressed
        if (minutes_Decrement_flag == 0) {
            time.minutes--;
            minutes_Decrement_flag = 1; // Prevent repeated decrements
        }
    } else {
        minutes_Decrement_flag = 0;
    }
}

/***************************************************************
 * Function: Hours Buttons Handling
 ***************************************************************/
void Hours_Adjustment(void) {
    if (BUTTON_INCREMENT_HOURS_PRESSED && time.hours <23) { // Check if increment button is pressed
        if (hours_Increment_flag == 0) {
            time.hours++;
            hours_Increment_flag = 1; // Prevent repeated increments
        }
    } else {
        hours_Increment_flag = 0;
    }

    if (BUTTON_DECREMENT_HOURS_PRESSED && time.hours >0) { // Check if decrement button is pressed
         if (hours_Decrement_flag == 0) {
            time.hours--;
            hours_Decrement_flag = 1; // Prevent repeated decrements
        }
    } else {
        hours_Decrement_flag = 0;
    }
}
