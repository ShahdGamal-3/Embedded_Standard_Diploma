 /******************************************************************************
 *
 * Module: External EEPROM
 *
 * File Name: external_eeprom.h
 *
 * Description: Header file for the External EEPROM Memory
 *
 * Author: Shahd Gamal
 *
 *******************************************************************************/


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "std_types.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define ERROR 0
#define SUCCESS 1

#define PASSWORD_ADDRESS	(0x0311)
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

uint8 EEPROM_writeByte(uint16 u16addr,uint8 u8data);
uint8 EEPROM_readByte(uint16 u16addr,uint8 *u8data);
uint8 EEPROM_writeString(uint16 u16addr, const uint8 *str, uint16 length);
uint8 EEPROM_readString(uint16 u16addr, uint8 *str, uint8 maxLen);
#endif /* EXTERNAL_EEPROM_H_ */
