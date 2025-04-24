 /******************************************************************************
 * Module: ADC
 * File Name: adc.h
 * Author: Shahd Gamal
 *******************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*
 * Maximum digital value the ADC can produce (10-bit resolution).
 */
#define ADC_MAXIMUM_VALUE    1023

/*
 * Reference voltage value for the ADC in Volts.
 */
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for initialize the ADC driver.
 */
void ADC_init(void);

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 channel_num);

#endif /* ADC_H_ */
