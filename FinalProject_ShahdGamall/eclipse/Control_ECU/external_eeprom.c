 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.c
 *
 * Description: Source file for the External EEPROM Memory
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/
#include "external_eeprom.h"
#include "twi.h"
#include <util/delay.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_writeByte((uint8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR; 
		 
    /* Send the required memory location address */
    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;
		
    /* write byte to eeprom */
    TWI_writeByte(u8data);
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();
	
    return SUCCESS;
}

uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;
		
    /* Send the required memory location address */
    TWI_writeByte((uint8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;
		
    /* Send the Repeated Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_REP_START)
        return ERROR;
		
    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_writeByte((uint8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readByteWithNACK();
    if (TWI_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}

/*
 * Write String in EEPROM at a specific address
 */
uint8 EEPROM_writeString(uint16 u16addr, const uint8 *str, uint16 length)
{
    uint8 status;
    for (uint16 i = 0; i < length; i++)
    {
        status = EEPROM_writeByte(u16addr, str[i]);
        _delay_ms(20);
        if (status != SUCCESS)
            return ERROR;  /* Stop if there is an error */
        u16addr++;
    }

    return SUCCESS;
}

/*
 * Read String from EEPROM at a specific address
 */
uint8 EEPROM_readString(uint16 u16addr, uint8 *str, uint8 maxLen)
{
    uint8 data = 0;

    for (uint8 i = 0; i < maxLen; i++)
    {
        /* Read a byte from EEPROM */
        if (EEPROM_readByte(u16addr++, &data) != SUCCESS)
        {
            return ERROR;  // Return error if read operation fails
        }

        /* Store the read byte in the string buffer */
        str[i] = data;

        /* If null terminator is read, exit loop */
        if (data == '\0')
        {
            return SUCCESS;
        }
    }

    /* Ensure the last character is null-terminated if maxLen limit is reached */
    str[maxLen - 1] = '\0';

    return SUCCESS;
}

