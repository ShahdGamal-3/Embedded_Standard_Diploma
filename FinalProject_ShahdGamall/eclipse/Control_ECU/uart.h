 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

typedef enum
{
	PARITY_DISABLE,ENABLE_EVEN_PARITY=0x20,ENABLE_ODD_PARITY=0x30
}UART_ParityType;

typedef enum
{
	ONE_BIT,TWO_BIT=0x08
}UART_StopBitType;

typedef enum
{
	FIVE_BIT,SEX_BIT=0x02,SEVEN_BIT=0x04,EIGHT_BIT=0x06,NINE_BIT=7
}UART_DataType;

typedef struct{
	uint32 baud_rate;
	uint8 parity_mode;
	uint8 stopbit_mode;
	uint8 data_mode;
}UART_ConfigType;

extern UART_ConfigType g_uart;    /* Extern declaration for global UART configuration */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType *Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str, uint8 len);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str, uint8 len); // Receive until #

#endif /* UART_H_ */
