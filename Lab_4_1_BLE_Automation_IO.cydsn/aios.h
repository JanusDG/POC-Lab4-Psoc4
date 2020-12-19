/*******************************************************************************
* File Name: aios.h
*
* Version 1.10
*
* Description:
*  AIOS service related code header.
*
* Hardware Dependency:
*  CY8CKIT-042 BLE
* 
********************************************************************************
* Copyright 2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(AIOSS_H)
#define AIOSS_H

#include <project.h>
#include <stdio.h>

/*******************************************************************************
* Enumerations
*******************************************************************************/
typedef enum
{
    AUTHENTICATION_NOT_CONNECTED,
    AUTHENTICATION_WAITING_FOR_PASSKEY,
    AUTHENTICATION_PASSKEY_ENTERED,
    AUTHENTICATION_PASSKEY_YES_NO,    
    AUTHENTICATION_COMPLETE_BONDING_REQD,
    AUTHENTICATION_BONDING_COMPLETE
} AUTHENTICATION_STATE;

/***************************************
*           API Constants
***************************************/
#define LED_ON                  (0u)
#define LED_OFF                 (1u)

/* Constants for buttonState */
#define BUTTON_IS_CHANGED       (1u)
#define BUTTON_IS_NOT_CHANGED   (0u)
#define BUTTON_IS_PRESSED       (0u)
#define BUTTON_IS_NOT_PRESSED   (1u)
#define BUTTON_START_DEBOUNCE   (100u)
#define BUTTON_SW2_MASK         (0x08u)

#define INSTANCE_SLIDER         (0u)
#define INSTANCE_PWM            (1u)
#define INSTANCE_ADC            (2u)
#define INSTANCE_DISPLAY        (3u)
#define INSTANCE_DIGITAL_INPUT  (4u)
#define INSTANCE_DIGITAL_INPUT_1  (4u)
#define INSTANCE_DIGITAL_INPUT_2  (5u)
#define INSTANCE_DIGITAL_INPUT_3  (6u)
#define INSTANCE_DIGITAL_LED_D1 (0u)
#define INSTANCE_DIGITAL_LED_D2 (1u)
#define INSTANCE_DIGITAL_LED_D3 (2u)
#define INSTANCE_DIGITAL_LED_D4 (3u)
#define N_OF_LEDS               (4u)

#define IDAC_MAX_VALUE          (0x7Fu)
#define CYBLE_CONN_INTRV_TO_MS  (5.0 / 4.0)

#define LED_D1_MASK             (0x01u)
#define LED_D2_MASK             (0x04u)
#define LED_D3_MASK             (0x10u)
#define LED_D4_MASK             (0x40u)

#define ADC_VREF_MASK               (0x000000F0Lu)
#define BATTERY_TIMEOUT             (600u)        /* Counts of 0.005 second */
#define ADC_BATTERY_CHANNEL         (0x00u)


/***************************************
*      External variables
***************************************/
extern CYBLE_API_RESULT_T apiResult;

/***************************************
*      Function prototypes
***************************************/
void AiosInit(void);
void AiosCallBack(uint32 event, void* eventParam);
void PrintCharacteristic(CYBLE_AIOS_CHAR_INDEX_T charIndex);
void PrintDescriptor(CYBLE_AIOS_DESCR_INDEX_T descrIndex);
void StartAdvertisement(void);
void out7seg(uint16);

#endif /* AIOSS_H  */

/* [] END OF FILE */
