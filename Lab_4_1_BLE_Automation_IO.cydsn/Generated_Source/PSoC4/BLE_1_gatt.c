/***************************************************************************//**
* \file CYBLE_gatt.c
* \version 3.66
* 
* \brief
*  This file contains the source code for the GATT API of the BLE Component.
* 
********************************************************************************
* \copyright
* Copyright 2014-2020, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#include "BLE_1_eventHandler.h"


/***************************************
* Global variables
***************************************/

CYBLE_STATE_T cyBle_state;

#if ((CYBLE_MODE_PROFILE) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES))
    
#if(CYBLE_MODE_PROFILE)
    #if defined(__ARMCC_VERSION)
        CY_ALIGN(CYDEV_FLS_ROW_SIZE) const CY_BLE_FLASH_STORAGE cyBle_flashStorage CY_SECTION(".cy_checksum_exclude") =
    #elif defined (__GNUC__)
        const CY_BLE_FLASH_STORAGE cyBle_flashStorage CY_SECTION(".cy_checksum_exclude")
            CY_ALIGN(CYDEV_FLS_ROW_SIZE) =
    #elif defined (__ICCARM__)
        #pragma data_alignment=CY_FLASH_SIZEOF_ROW
        #pragma location=".cy_checksum_exclude"
        const CY_BLE_FLASH_STORAGE cyBle_flashStorage =
    #endif  /* (__ARMCC_VERSION) */
    {
        { 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
        0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u }, 
        {{
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        },
        {
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        },
        {
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        },
        {
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        },
        {
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
            0x00u, 0x00u,
        }}, 
        0x0Eu, /* CYBLE_GATT_DB_CCCD_COUNT */ 
        0x05u, /* CYBLE_GAP_MAX_BONDED_DEVICE */ 
    };
#endif /* (CYBLE_MODE_PROFILE) */

#endif  /* (CYBLE_MODE_PROFILE) && (CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES) */

#if(CYBLE_GATT_ROLE_SERVER)
    
    const CYBLE_GATTS_T cyBle_gatts =
{
    0x000Au,    /* Handle of the GATT service */
    0x000Cu,    /* Handle of the Service Changed characteristic */
    0x000Du,    /* Handle of the Client Characteristic Configuration descriptor */
};
    
    static uint8 cyBle_attValues[0x0159u] = {
    /* Device Name */
    (uint8)'A', (uint8)'u', (uint8)'t', (uint8)'o', (uint8)'m', (uint8)'a', (uint8)'t', (uint8)'i', (uint8)'o',
    (uint8)'n', (uint8)' ', (uint8)'I', (uint8)'O',

    /* Appearance */
    0x00u, 0x00u,

    /* Peripheral Preferred Connection Parameters */
    0x06u, 0x00u, 0x28u, 0x00u, 0x00u, 0x00u, 0xE8u, 0x03u,

    /* Central Address Resolution */
    0x00u,

    /* Service Changed */
    0x00u, 0x00u, 0x00u, 0x00u,

    /* Digital LED D1 */
    0x00u,

    /* Characteristic Presentation Format */
    0x1Bu, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u, 0x00u,

    /* Characteristic User Description */
    (uint8)'D', (uint8)'i', (uint8)'g', (uint8)'i', (uint8)'t', (uint8)'a', (uint8)'l', (uint8)' ', (uint8)'O',
    (uint8)'u', (uint8)'t', (uint8)'p', (uint8)'u', (uint8)'t', (uint8)'.', (uint8)' ', (uint8)'L', (uint8)'E',
    (uint8)'D', (uint8)' ', (uint8)'D', (uint8)'1',

    /* Number of Digitals */
    0x01u,

    /* Digital LED D2 */
    0x00u,

    /* Characteristic Presentation Format */
    0x1Bu, 0x00u, 0x00u, 0x00u, 0x01u, 0x02u, 0x00u,

    /* Characteristic User Description */
    (uint8)'D', (uint8)'i', (uint8)'g', (uint8)'i', (uint8)'t', (uint8)'a', (uint8)'l', (uint8)' ', (uint8)'O',
    (uint8)'u', (uint8)'t', (uint8)'p', (uint8)'u', (uint8)'t', (uint8)'.', (uint8)' ', (uint8)'L', (uint8)'E',
    (uint8)'D', (uint8)' ', (uint8)'D', (uint8)'2',

    /* Number of Digitals */
    0x01u,

    /* Digital LED D3 */
    0x00u,

    /* Characteristic Presentation Format */
    0x1Bu, 0x00u, 0x00u, 0x00u, 0x01u, 0x03u, 0x00u,

    /* Characteristic User Description */
    (uint8)'D', (uint8)'i', (uint8)'g', (uint8)'i', (uint8)'t', (uint8)'a', (uint8)'l', (uint8)' ', (uint8)'O',
    (uint8)'u', (uint8)'t', (uint8)'p', (uint8)'u', (uint8)'t', (uint8)'.', (uint8)' ', (uint8)'L', (uint8)'E',
    (uint8)'D', (uint8)' ', (uint8)'D', (uint8)'3',

    /* Number of Digitals */
    0x01u,

    /* Digital LED D4 */
    0x00u,

    /* Characteristic Presentation Format */
    0x1Bu, 0x00u, 0x00u, 0x00u, 0x01u, 0x04u, 0x00u,

    /* Characteristic User Description */
    (uint8)'D', (uint8)'i', (uint8)'g', (uint8)'i', (uint8)'t', (uint8)'a', (uint8)'l', (uint8)' ', (uint8)'O',
    (uint8)'u', (uint8)'t', (uint8)'p', (uint8)'u', (uint8)'t', (uint8)'.', (uint8)' ', (uint8)'L', (uint8)'E',
    (uint8)'D', (uint8)' ', (uint8)'D', (uint8)'4',

    /* Number of Digitals */
    0x01u,

    /* Digital S1 */
    0x00u,

    /* Characteristic Presentation Format */
    0x1Bu, 0x00u, 0x00u, 0x00u, 0x01u, 0x05u, 0x00u,

    /* Characteristic User Description */
    (uint8)'D', (uint8)'i', (uint8)'d', (uint8)'i', (uint8)'t', (uint8)'a', (uint8)'l', (uint8)' ', (uint8)'I',
    (uint8)'n', (uint8)'p', (uint8)'u', (uint8)'t', (uint8)' ', (uint8)'S', (uint8)'1',

    /* Number of Digitals */
    0x01u,

    /* Digital S2 */
    0x00u,

    /* Characteristic Presentation Format */
    0x1Bu, 0x00u, 0x00u, 0x00u, 0x01u, 0x06u, 0x00u,

    /* Characteristic User Description */
    (uint8)'D', (uint8)'i', (uint8)'d', (uint8)'i', (uint8)'t', (uint8)'a', (uint8)'l', (uint8)' ', (uint8)'I',
    (uint8)'n', (uint8)'p', (uint8)'u', (uint8)'t', (uint8)' ', (uint8)'S', (uint8)'2',

    /* Number of Digitals */
    0x01u,

    /* Digital S3 */
    0x00u,

    /* Characteristic Presentation Format */
    0x1Bu, 0x00u, 0x00u, 0x00u, 0x01u, 0x07u, 0x00u,

    /* Characteristic User Description */
    (uint8)'D', (uint8)'i', (uint8)'d', (uint8)'i', (uint8)'t', (uint8)'a', (uint8)'l', (uint8)' ', (uint8)'I',
    (uint8)'n', (uint8)'p', (uint8)'u', (uint8)'t', (uint8)' ', (uint8)'S', (uint8)'3',

    /* Number of Digitals */
    0x01u,

    /* Analog Slider */
    0x00u, 0x00u,

    /* Characteristic Presentation Format */
    0x06u, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u, 0x00u,

    /* Characteristic User Description */
    (uint8)'S', (uint8)'l', (uint8)'i', (uint8)'d', (uint8)'e', (uint8)'r', (uint8)' ', (uint8)'P', (uint8)'o',
    (uint8)'s', (uint8)'i', (uint8)'t', (uint8)'i', (uint8)'o', (uint8)'n',

    /* Value Trigger Setting */
    0x05u, 0xE8u, 0x03u, 0x00u, 0x00u,

    /* Time Trigger Setting */
    0x01u, 0x03u, 0x00u, 0x00u,

    /* Valid Range */
    0x00u, 0x00u, 0x64u, 0x00u,

    /* Analog 2 LED */
    0x00u, 0x00u,

    /* Characteristic Presentation Format */
    0x04u, 0x00u, 0x33u, 0x27u, 0x01u, 0x02u, 0x00u,

    /* Characteristic User Description */
    (uint8)'P', (uint8)'W', (uint8)'M', (uint8)' ', (uint8)'L', (uint8)'E', (uint8)'D', (uint8)' ', (uint8)'V',
    (uint8)'a', (uint8)'l', (uint8)'u', (uint8)'e',

    /* Value Trigger Setting */
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u,

    /* Time Trigger Setting */
    0x00u, 0x00u, 0x00u, 0x00u,

    /* Valid Range */
    0x00u, 0x00u, 0x64u, 0x00u,

    /* Analog ADC */
    0x00u, 0x00u,

    /* Characteristic Presentation Format */
    0x06u, 0x00u, 0x28u, 0x27u, 0x01u, 0x03u, 0x00u,

    /* Characteristic User Description */
    (uint8)'A', (uint8)'D', (uint8)'C',

    /* Valid Range */
    0xE8u, 0x03u, 0xD0u, 0x07u,

    /* Aggregate */
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,

    /* Analog DISPLAY */
    0x00u, 0x00u,

    /* Characteristic Presentation Format */
    0x04u, 0x00u, 0x33u, 0x27u, 0x01u, 0x04u, 0x00u,

    /* Characteristic User Description */
    (uint8)'D', (uint8)'I', (uint8)'S', (uint8)'P', (uint8)'L', (uint8)'A', (uint8)'Y',

    /* Valid Range */
    0xE8u, 0x03u, 0xD0u, 0x07u,

};
#if(CYBLE_GATT_DB_CCCD_COUNT != 0u)
uint8 cyBle_attValuesCCCD[CYBLE_GATT_DB_CCCD_COUNT];
#endif /* CYBLE_GATT_DB_CCCD_COUNT != 0u */

CYBLE_GATTS_ATT_GEN_VAL_LEN_T cyBle_attValuesLen[CYBLE_GATT_DB_ATT_VAL_COUNT] = {
    { 0x000Du, (void *)&cyBle_attValues[0] }, /* Device Name */
    { 0x0002u, (void *)&cyBle_attValues[13] }, /* Appearance */
    { 0x0008u, (void *)&cyBle_attValues[15] }, /* Peripheral Preferred Connection Parameters */
    { 0x0001u, (void *)&cyBle_attValues[23] }, /* Central Address Resolution */
    { 0x0004u, (void *)&cyBle_attValues[24] }, /* Service Changed */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[0] }, /* Client Characteristic Configuration */
    { 0x0001u, (void *)&cyBle_attValues[28] }, /* Digital LED D1 */
    { 0x0007u, (void *)&cyBle_attValues[29] }, /* Characteristic Presentation Format */
    { 0x0016u, (void *)&cyBle_attValues[36] }, /* Characteristic User Description */
    { 0x0001u, (void *)&cyBle_attValues[58] }, /* Number of Digitals */
    { 0x0001u, (void *)&cyBle_attValues[59] }, /* Digital LED D2 */
    { 0x0007u, (void *)&cyBle_attValues[60] }, /* Characteristic Presentation Format */
    { 0x0016u, (void *)&cyBle_attValues[67] }, /* Characteristic User Description */
    { 0x0001u, (void *)&cyBle_attValues[89] }, /* Number of Digitals */
    { 0x0001u, (void *)&cyBle_attValues[90] }, /* Digital LED D3 */
    { 0x0007u, (void *)&cyBle_attValues[91] }, /* Characteristic Presentation Format */
    { 0x0016u, (void *)&cyBle_attValues[98] }, /* Characteristic User Description */
    { 0x0001u, (void *)&cyBle_attValues[120] }, /* Number of Digitals */
    { 0x0001u, (void *)&cyBle_attValues[121] }, /* Digital LED D4 */
    { 0x0007u, (void *)&cyBle_attValues[122] }, /* Characteristic Presentation Format */
    { 0x0016u, (void *)&cyBle_attValues[129] }, /* Characteristic User Description */
    { 0x0001u, (void *)&cyBle_attValues[151] }, /* Number of Digitals */
    { 0x0001u, (void *)&cyBle_attValues[152] }, /* Digital S1 */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[2] }, /* Client Characteristic Configuration */
    { 0x0007u, (void *)&cyBle_attValues[153] }, /* Characteristic Presentation Format */
    { 0x0010u, (void *)&cyBle_attValues[160] }, /* Characteristic User Description */
    { 0x0001u, (void *)&cyBle_attValues[176] }, /* Number of Digitals */
    { 0x0001u, (void *)&cyBle_attValues[177] }, /* Digital S2 */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[4] }, /* Client Characteristic Configuration */
    { 0x0007u, (void *)&cyBle_attValues[178] }, /* Characteristic Presentation Format */
    { 0x0010u, (void *)&cyBle_attValues[185] }, /* Characteristic User Description */
    { 0x0001u, (void *)&cyBle_attValues[201] }, /* Number of Digitals */
    { 0x0001u, (void *)&cyBle_attValues[202] }, /* Digital S3 */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[6] }, /* Client Characteristic Configuration */
    { 0x0007u, (void *)&cyBle_attValues[203] }, /* Characteristic Presentation Format */
    { 0x0010u, (void *)&cyBle_attValues[210] }, /* Characteristic User Description */
    { 0x0001u, (void *)&cyBle_attValues[226] }, /* Number of Digitals */
    { 0x0002u, (void *)&cyBle_attValues[227] }, /* Analog Slider */
    { 0x0007u, (void *)&cyBle_attValues[229] }, /* Characteristic Presentation Format */
    { 0x000Fu, (void *)&cyBle_attValues[236] }, /* Characteristic User Description */
    { 0x0005u, (void *)&cyBle_attValues[251] }, /* Value Trigger Setting */
    { 0x0004u, (void *)&cyBle_attValues[256] }, /* Time Trigger Setting */
    { 0x0004u, (void *)&cyBle_attValues[260] }, /* Valid Range */
    { 0x0002u, (void *)&cyBle_attValues[264] }, /* Analog 2 LED */
    { 0x0007u, (void *)&cyBle_attValues[266] }, /* Characteristic Presentation Format */
    { 0x000Du, (void *)&cyBle_attValues[273] }, /* Characteristic User Description */
    { 0x0001u, (void *)&cyBle_attValues[286] }, /* Value Trigger Setting */
    { 0x0001u, (void *)&cyBle_attValues[291] }, /* Time Trigger Setting */
    { 0x0004u, (void *)&cyBle_attValues[295] }, /* Valid Range */
    { 0x0002u, (void *)&cyBle_attValues[299] }, /* Analog ADC */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[8] }, /* Client Characteristic Configuration */
    { 0x0007u, (void *)&cyBle_attValues[301] }, /* Characteristic Presentation Format */
    { 0x0003u, (void *)&cyBle_attValues[308] }, /* Characteristic User Description */
    { 0x0004u, (void *)&cyBle_attValues[311] }, /* Valid Range */
    { 0x000Au, (void *)&cyBle_attValues[315] }, /* Aggregate */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[10] }, /* Client Characteristic Configuration */
    { 0x0002u, (void *)&cyBle_attValues[325] }, /* Analog DISPLAY */
    { 0x0002u, (void *)&cyBle_attValuesCCCD[12] }, /* Client Characteristic Configuration */
    { 0x0007u, (void *)&cyBle_attValues[327] }, /* Characteristic Presentation Format */
    { 0x0007u, (void *)&cyBle_attValues[334] }, /* Characteristic User Description */
    { 0x0004u, (void *)&cyBle_attValues[341] }, /* Valid Range */
};

const CYBLE_GATTS_DB_T cyBle_gattDB[0x51u] = {
    { 0x0001u, 0x2800u /* Primary service                     */, 0x00000001u /*           */, 0x0009u, {{0x1800u, NULL}}                           },
    { 0x0002u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0003u, {{0x2A00u, NULL}}                           },
    { 0x0003u, 0x2A00u /* Device Name                         */, 0x01020001u /* rd        */, 0x0003u, {{0x000Du, (void *)&cyBle_attValuesLen[0]}} },
    { 0x0004u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0005u, {{0x2A01u, NULL}}                           },
    { 0x0005u, 0x2A01u /* Appearance                          */, 0x01020001u /* rd        */, 0x0005u, {{0x0002u, (void *)&cyBle_attValuesLen[1]}} },
    { 0x0006u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0007u, {{0x2A04u, NULL}}                           },
    { 0x0007u, 0x2A04u /* Peripheral Preferred Connection Par */, 0x01020001u /* rd        */, 0x0007u, {{0x0008u, (void *)&cyBle_attValuesLen[2]}} },
    { 0x0008u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x0009u, {{0x2AA6u, NULL}}                           },
    { 0x0009u, 0x2AA6u /* Central Address Resolution          */, 0x01020001u /* rd        */, 0x0009u, {{0x0001u, (void *)&cyBle_attValuesLen[3]}} },
    { 0x000Au, 0x2800u /* Primary service                     */, 0x00000001u /*           */, 0x000Du, {{0x1801u, NULL}}                           },
    { 0x000Bu, 0x2803u /* Characteristic                      */, 0x00200001u /* ind       */, 0x000Du, {{0x2A05u, NULL}}                           },
    { 0x000Cu, 0x2A05u /* Service Changed                     */, 0x01200000u /* ind       */, 0x000Du, {{0x0004u, (void *)&cyBle_attValuesLen[4]}} },
    { 0x000Du, 0x2902u /* Client Characteristic Configuration */, 0x010A0101u /* rd,wr     */, 0x000Du, {{0x0002u, (void *)&cyBle_attValuesLen[5]}} },
    { 0x000Eu, 0x2800u /* Primary service                     */, 0x00000001u /*           */, 0x0051u, {{0x1815u, NULL}}                           },
    { 0x000Fu, 0x2803u /* Characteristic                      */, 0x000E0001u /* rd,wr,wwr */, 0x0013u, {{0x2A56u, NULL}}                           },
    { 0x0010u, 0x2A56u /* Digital LED D1                      */, 0x010E1313u /* rd,wr,wwr */, 0x0013u, {{0x0001u, (void *)&cyBle_attValuesLen[6]}} },
    { 0x0011u, 0x2904u /* Characteristic Presentation Format  */, 0x01020013u /* rd        */, 0x0011u, {{0x0007u, (void *)&cyBle_attValuesLen[7]}} },
    { 0x0012u, 0x2901u /* Characteristic User Description     */, 0x01020013u /* rd        */, 0x0012u, {{0x0016u, (void *)&cyBle_attValuesLen[8]}} },
    { 0x0013u, 0x2909u /* Number of Digitals                  */, 0x01020013u /* rd        */, 0x0013u, {{0x0001u, (void *)&cyBle_attValuesLen[9]}} },
    { 0x0014u, 0x2803u /* Characteristic                      */, 0x000E0001u /* rd,wr,wwr */, 0x0018u, {{0x2A56u, NULL}}                           },
    { 0x0015u, 0x2A56u /* Digital LED D2                      */, 0x010E1313u /* rd,wr,wwr */, 0x0018u, {{0x0001u, (void *)&cyBle_attValuesLen[10]}} },
    { 0x0016u, 0x2904u /* Characteristic Presentation Format  */, 0x01020001u /* rd        */, 0x0016u, {{0x0007u, (void *)&cyBle_attValuesLen[11]}} },
    { 0x0017u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0017u, {{0x0016u, (void *)&cyBle_attValuesLen[12]}} },
    { 0x0018u, 0x2909u /* Number of Digitals                  */, 0x01020001u /* rd        */, 0x0018u, {{0x0001u, (void *)&cyBle_attValuesLen[13]}} },
    { 0x0019u, 0x2803u /* Characteristic                      */, 0x000E0001u /* rd,wr,wwr */, 0x001Du, {{0x2A56u, NULL}}                           },
    { 0x001Au, 0x2A56u /* Digital LED D3                      */, 0x010E1313u /* rd,wr,wwr */, 0x001Du, {{0x0001u, (void *)&cyBle_attValuesLen[14]}} },
    { 0x001Bu, 0x2904u /* Characteristic Presentation Format  */, 0x01020001u /* rd        */, 0x001Bu, {{0x0007u, (void *)&cyBle_attValuesLen[15]}} },
    { 0x001Cu, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x001Cu, {{0x0016u, (void *)&cyBle_attValuesLen[16]}} },
    { 0x001Du, 0x2909u /* Number of Digitals                  */, 0x01020001u /* rd        */, 0x001Du, {{0x0001u, (void *)&cyBle_attValuesLen[17]}} },
    { 0x001Eu, 0x2803u /* Characteristic                      */, 0x000E0001u /* rd,wr,wwr */, 0x0022u, {{0x2A56u, NULL}}                           },
    { 0x001Fu, 0x2A56u /* Digital LED D4                      */, 0x010E1313u /* rd,wr,wwr */, 0x0022u, {{0x0001u, (void *)&cyBle_attValuesLen[18]}} },
    { 0x0020u, 0x2904u /* Characteristic Presentation Format  */, 0x01020001u /* rd        */, 0x0020u, {{0x0007u, (void *)&cyBle_attValuesLen[19]}} },
    { 0x0021u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0021u, {{0x0016u, (void *)&cyBle_attValuesLen[20]}} },
    { 0x0022u, 0x2909u /* Number of Digitals                  */, 0x01020001u /* rd        */, 0x0022u, {{0x0001u, (void *)&cyBle_attValuesLen[21]}} },
    { 0x0023u, 0x2803u /* Characteristic                      */, 0x00220001u /* rd,ind    */, 0x0028u, {{0x2A56u, NULL}}                           },
    { 0x0024u, 0x2A56u /* Digital S1                          */, 0x01220013u /* rd,ind    */, 0x0028u, {{0x0001u, (void *)&cyBle_attValuesLen[22]}} },
    { 0x0025u, 0x2902u /* Client Characteristic Configuration */, 0x010A1301u /* rd,wr     */, 0x0025u, {{0x0002u, (void *)&cyBle_attValuesLen[23]}} },
    { 0x0026u, 0x2904u /* Characteristic Presentation Format  */, 0x01020013u /* rd        */, 0x0026u, {{0x0007u, (void *)&cyBle_attValuesLen[24]}} },
    { 0x0027u, 0x2901u /* Characteristic User Description     */, 0x01020707u /* rd        */, 0x0027u, {{0x0010u, (void *)&cyBle_attValuesLen[25]}} },
    { 0x0028u, 0x2909u /* Number of Digitals                  */, 0x01020013u /* rd        */, 0x0028u, {{0x0001u, (void *)&cyBle_attValuesLen[26]}} },
    { 0x0029u, 0x2803u /* Characteristic                      */, 0x00220001u /* rd,ind    */, 0x002Eu, {{0x2A56u, NULL}}                           },
    { 0x002Au, 0x2A56u /* Digital S2                          */, 0x01220013u /* rd,ind    */, 0x002Eu, {{0x0001u, (void *)&cyBle_attValuesLen[27]}} },
    { 0x002Bu, 0x2902u /* Client Characteristic Configuration */, 0x010A1301u /* rd,wr     */, 0x002Bu, {{0x0002u, (void *)&cyBle_attValuesLen[28]}} },
    { 0x002Cu, 0x2904u /* Characteristic Presentation Format  */, 0x01020001u /* rd        */, 0x002Cu, {{0x0007u, (void *)&cyBle_attValuesLen[29]}} },
    { 0x002Du, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x002Du, {{0x0010u, (void *)&cyBle_attValuesLen[30]}} },
    { 0x002Eu, 0x2909u /* Number of Digitals                  */, 0x01020001u /* rd        */, 0x002Eu, {{0x0001u, (void *)&cyBle_attValuesLen[31]}} },
    { 0x002Fu, 0x2803u /* Characteristic                      */, 0x00220001u /* rd,ind    */, 0x0034u, {{0x2A56u, NULL}}                           },
    { 0x0030u, 0x2A56u /* Digital S3                          */, 0x01220013u /* rd,ind    */, 0x0034u, {{0x0001u, (void *)&cyBle_attValuesLen[32]}} },
    { 0x0031u, 0x2902u /* Client Characteristic Configuration */, 0x010A1301u /* rd,wr     */, 0x0031u, {{0x0002u, (void *)&cyBle_attValuesLen[33]}} },
    { 0x0032u, 0x2904u /* Characteristic Presentation Format  */, 0x01020001u /* rd        */, 0x0032u, {{0x0007u, (void *)&cyBle_attValuesLen[34]}} },
    { 0x0033u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0033u, {{0x0010u, (void *)&cyBle_attValuesLen[35]}} },
    { 0x0034u, 0x2909u /* Number of Digitals                  */, 0x01020001u /* rd        */, 0x0034u, {{0x0001u, (void *)&cyBle_attValuesLen[36]}} },
    { 0x0035u, 0x2803u /* Characteristic                      */, 0x00020001u /* rd        */, 0x003Bu, {{0x2A58u, NULL}}                           },
    { 0x0036u, 0x2A58u /* Analog Slider                       */, 0x01020013u /* rd        */, 0x003Bu, {{0x0002u, (void *)&cyBle_attValuesLen[37]}} },
    { 0x0037u, 0x2904u /* Characteristic Presentation Format  */, 0x01020013u /* rd        */, 0x0037u, {{0x0007u, (void *)&cyBle_attValuesLen[38]}} },
    { 0x0038u, 0x2901u /* Characteristic User Description     */, 0x01021313u /* rd        */, 0x0038u, {{0x000Fu, (void *)&cyBle_attValuesLen[39]}} },
    { 0x0039u, 0x290Au /* Value Trigger Setting               */, 0x010A1313u /* rd,wr     */, 0x0039u, {{0x0005u, (void *)&cyBle_attValuesLen[40]}} },
    { 0x003Au, 0x290Eu /* Time Trigger Setting                */, 0x010A1313u /* rd,wr     */, 0x003Au, {{0x0004u, (void *)&cyBle_attValuesLen[41]}} },
    { 0x003Bu, 0x2906u /* Valid Range                         */, 0x01020013u /* rd        */, 0x003Bu, {{0x0004u, (void *)&cyBle_attValuesLen[42]}} },
    { 0x003Cu, 0x2803u /* Characteristic                      */, 0x000E0001u /* rd,wr,wwr */, 0x0042u, {{0x2A58u, NULL}}                           },
    { 0x003Du, 0x2A58u /* Analog 2 LED                        */, 0x010E1313u /* rd,wr,wwr */, 0x0042u, {{0x0002u, (void *)&cyBle_attValuesLen[43]}} },
    { 0x003Eu, 0x2904u /* Characteristic Presentation Format  */, 0x01020013u /* rd        */, 0x003Eu, {{0x0007u, (void *)&cyBle_attValuesLen[44]}} },
    { 0x003Fu, 0x2901u /* Characteristic User Description     */, 0x01020013u /* rd        */, 0x003Fu, {{0x000Du, (void *)&cyBle_attValuesLen[45]}} },
    { 0x0040u, 0x290Au /* Value Trigger Setting               */, 0x010A1313u /* rd,wr     */, 0x0040u, {{0x0005u, (void *)&cyBle_attValuesLen[46]}} },
    { 0x0041u, 0x290Eu /* Time Trigger Setting                */, 0x010A1313u /* rd,wr     */, 0x0041u, {{0x0004u, (void *)&cyBle_attValuesLen[47]}} },
    { 0x0042u, 0x2906u /* Valid Range                         */, 0x01020013u /* rd        */, 0x0042u, {{0x0004u, (void *)&cyBle_attValuesLen[48]}} },
    { 0x0043u, 0x2803u /* Characteristic                      */, 0x00220001u /* rd,ind    */, 0x0048u, {{0x2A58u, NULL}}                           },
    { 0x0044u, 0x2A58u /* Analog ADC                          */, 0x01220013u /* rd,ind    */, 0x0048u, {{0x0002u, (void *)&cyBle_attValuesLen[49]}} },
    { 0x0045u, 0x2902u /* Client Characteristic Configuration */, 0x010A1301u /* rd,wr     */, 0x0045u, {{0x0002u, (void *)&cyBle_attValuesLen[50]}} },
    { 0x0046u, 0x2904u /* Characteristic Presentation Format  */, 0x01020001u /* rd        */, 0x0046u, {{0x0007u, (void *)&cyBle_attValuesLen[51]}} },
    { 0x0047u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0047u, {{0x0003u, (void *)&cyBle_attValuesLen[52]}} },
    { 0x0048u, 0x2906u /* Valid Range                         */, 0x01020001u /* rd        */, 0x0048u, {{0x0004u, (void *)&cyBle_attValuesLen[53]}} },
    { 0x0049u, 0x2803u /* Characteristic                      */, 0x00220001u /* rd,ind    */, 0x004Bu, {{0x2A5Au, NULL}}                           },
    { 0x004Au, 0x2A5Au /* Aggregate                           */, 0x01220013u /* rd,ind    */, 0x004Bu, {{0x000Au, (void *)&cyBle_attValuesLen[54]}} },
    { 0x004Bu, 0x2902u /* Client Characteristic Configuration */, 0x010A1313u /* rd,wr     */, 0x004Bu, {{0x0002u, (void *)&cyBle_attValuesLen[55]}} },
    { 0x004Cu, 0x2803u /* Characteristic                      */, 0x000A0001u /* rd,wr     */, 0x0051u, {{0x2A58u, NULL}}                           },
    { 0x004Du, 0x2A58u /* Analog DISPLAY                      */, 0x010A1313u /* rd,wr     */, 0x0051u, {{0x0002u, (void *)&cyBle_attValuesLen[56]}} },
    { 0x004Eu, 0x2902u /* Client Characteristic Configuration */, 0x010A1301u /* rd,wr     */, 0x004Eu, {{0x0002u, (void *)&cyBle_attValuesLen[57]}} },
    { 0x004Fu, 0x2904u /* Characteristic Presentation Format  */, 0x01020001u /* rd        */, 0x004Fu, {{0x0007u, (void *)&cyBle_attValuesLen[58]}} },
    { 0x0050u, 0x2901u /* Characteristic User Description     */, 0x01020001u /* rd        */, 0x0050u, {{0x0007u, (void *)&cyBle_attValuesLen[59]}} },
    { 0x0051u, 0x2906u /* Valid Range                         */, 0x01020001u /* rd        */, 0x0051u, {{0x0004u, (void *)&cyBle_attValuesLen[60]}} },
};


#endif /* (CYBLE_GATT_ROLE_SERVER) */

#if(CYBLE_GATT_ROLE_CLIENT)
    
CYBLE_CLIENT_STATE_T cyBle_clientState;
CYBLE_GATTC_T cyBle_gattc;
CYBLE_GATT_ATTR_HANDLE_RANGE_T cyBle_gattcDiscoveryRange;
    
#endif /* (CYBLE_GATT_ROLE_CLIENT) */


#if(CYBLE_GATT_ROLE_SERVER)

/****************************************************************************** 
* Function Name: CyBle_GattsReInitGattDb
***************************************************************************//**
* 
*  Reinitializes the GATT database.
* 
*  \return
*  CYBLE_API_RESULT_T: A function result states if it succeeded or failed with
*  error codes:

*  Errors codes                          | Description
*  ------------                          | -----------
*  CYBLE_ERROR_OK						 | GATT database was reinitialized successfully.
*  CYBLE_ERROR_INVALID_STATE             | If the function is called in any state except CYBLE_STATE_DISCONNECTED.
*  CYBLE_ERROR_INVALID_PARAMETER         | If the Database has zero entries or is a NULL pointer.
* 
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattsReInitGattDb(void)
{
    CYBLE_API_RESULT_T apiResult;
    
    if(CyBle_GetState() == CYBLE_STATE_DISCONNECTED)
    {
        apiResult = CyBle_GattsDbRegister(cyBle_gattDB, CYBLE_GATT_DB_INDEX_COUNT, CYBLE_GATT_DB_MAX_VALUE_LEN);
    }
    else
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    
    return(apiResult);
}


/****************************************************************************** 
* Function Name: CyBle_GattsWriteEventHandler
***************************************************************************//**
* 
*  Handles the Write Request Event for GATT service.
* 
*  \param eventParam: The pointer to the data structure specified by the event.
* 
*  \return
*  CYBLE_GATT_ERR_CODE_T: A function returns one of the following status 
*  values.

*  Errors codes                          | Description
*  --------------------                  | -----------
*  CYBLE_GATT_ERR_NONE                   | Write is successful.
* 
******************************************************************************/
CYBLE_GATT_ERR_CODE_T CyBle_GattsWriteEventHandler(CYBLE_GATTS_WRITE_REQ_PARAM_T *eventParam)
{
    CYBLE_GATT_ERR_CODE_T gattErr = CYBLE_GATT_ERR_NONE;
    
    /* Client Characteristic Configuration descriptor write request */
    if(eventParam->handleValPair.attrHandle == cyBle_gatts.cccdHandle)
    {
        /* Store value to database */
        gattErr = CyBle_GattsWriteAttributeValue(&eventParam->handleValPair, 0u, 
                        &eventParam->connHandle, CYBLE_GATT_DB_PEER_INITIATED);
        
        if(gattErr == CYBLE_GATT_ERR_NONE)
        {
            if(CYBLE_IS_INDICATION_ENABLED_IN_PTR(eventParam->handleValPair.value.val))
            {
                CyBle_ApplCallback((uint32)CYBLE_EVT_GATTS_INDICATION_ENABLED, eventParam);
            }
            else
            {
                CyBle_ApplCallback((uint32)CYBLE_EVT_GATTS_INDICATION_DISABLED, eventParam);
            }
        }
        cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
    }
    return (gattErr);
}


#endif /* (CYBLE_GATT_ROLE_SERVER) */

#if(CYBLE_GATT_ROLE_CLIENT)

/****************************************************************************** 
* Function Name: CyBle_GattcStartDiscovery
***************************************************************************//**
* 
*  Starts the automatic server discovery process. 
*   
*   Discovery procedure is based on the user configuration. It discovers only services, characteristics, 
*   descriptors which were declared in the GATT database.
*   Discovery procedure has the following flow:
*   - discovering primary services by BLE Stack function CyBle_GattcDiscoverAllPrimaryServices();
*   - discovering included services by BLE Stack function CyBle_GattcFindIncludedServices();
*   - discovering characteristics for available services by BLE Stack function CyBle_GattcDiscoverAllCharacteristics();
*   - discovering characteristic descriptors by BLE Stack function CyBle_GattcDiscoverAllCharacteristicDescriptors();
*
*   During the discovery procedure the discovery-specific stack events are handled by the component 
*   and thus aren’t passed to the application callback: CYBLE_EVT_GATTC_READ_BY_GROUP_TYPE_RSP,
*   CYBLE_EVT_GATTC_READ_BY_TYPE_RSP, CYBLE_EVT_GATTC_FIND_INFO_RSP, CYBLE_EVT_GATTC_ERROR_RSP.              
*   
*   After the discovery procedure all information about available services is stored in CYBLE_DISC_SRVC_INFO_T structures,
*   and discovered attributes handles are stored in service-specific client structures, such as CYBLE_BASC_T for 
*   Battery Service or CYBLE_HRSC_T for Heart Rate Service.
*
*  \param connHandle: The handle which consists of the device ID and ATT connection ID.
* 
*  \return
*  CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*                        failed. Following are the possible error codes.
*
*   <table>	
*   <tr>
*	  <th>Errors codes</th>
*	  <th>Description</th>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_OK</td>
*	  <td>On successful operation</td>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*	  <td>'connHandle' value does not represent any existing entry.</td>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_INVALID_OPERATION</td>
*	  <td>The operation is not permitted</td>
*	</tr>
*   <tr>
*	  <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*	  <td>Memory allocation failed</td>
*	</tr>
*   <tr>
*	  <td>CYBLE_ERROR_INVALID_STATE</td>
*	  <td>If the function is called in any state except connected or discovered</td>
*	</tr>
*   </table>
*
*  \events
*   The following events may be generated after calling this function:
*   * CYBLE_EVT_GATTC_DISCOVERY_COMPLETE  - event is generated when the remote device was successfully discovered. 
*   * CYBLE_EVT_GATTC_ERROR_RSP  		- is generated if the device discovery has failed.
*   * CYBLE_EVT_GATTC_SRVC_DUPLICATION 	- is generated if duplicate service record was found during the server device
*        								  discovery.
*   * CYBLE_EVT_GATTC_CHAR_DUPLICATION 	- is generated if duplicate service's characteristic descriptor record was found
*        								  during the server device discovery.
*   * CYBLE_EVT_GATTC_DESCR_DUPLICATION - is generated if duplicate service's characteristic descriptor record was found
*        								  during the server device discovery.
*  
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcStartDiscovery(CYBLE_CONN_HANDLE_T connHandle)
{
    uint8 j;
    CYBLE_API_RESULT_T apiResult;
    
    if((CyBle_GetState() != CYBLE_STATE_CONNECTED) || 
       ((CyBle_GetClientState() != CYBLE_CLIENT_STATE_CONNECTED) && 
        (CyBle_GetClientState() != CYBLE_CLIENT_STATE_DISCOVERED))) 
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    else
    {
        /* Clean old discovery information */
        for(j = 0u; j < (uint8) CYBLE_SRVI_COUNT; j++)
        {
            (void)memset(&cyBle_serverInfo[j].range, 0, sizeof(cyBle_serverInfo[0].range));
        }

        cyBle_connHandle = connHandle;
        cyBle_gattcDiscoveryRange.startHandle = CYBLE_GATT_ATTR_HANDLE_START_RANGE;
        cyBle_gattcDiscoveryRange.endHandle = CYBLE_GATT_ATTR_HANDLE_END_RANGE;
        
        CyBle_ServiceInit();
        
        apiResult = CyBle_GattcDiscoverAllPrimaryServices(connHandle);

        if(apiResult == CYBLE_ERROR_OK)
        {
            CyBle_SetClientState(CYBLE_CLIENT_STATE_SRVC_DISCOVERING);
            cyBle_eventHandlerFlag |= CYBLE_AUTO_DISCOVERY;
        }
    }
    
    return (apiResult);
}


/****************************************************************************** 
* Function Name: CyBle_GattcStartPartialDiscovery
***************************************************************************//**
* 
*  Starts the automatic server discovery process as per the range provided
*  on a GATT Server to which it is connected. This function could be used for 
*  partial server discovery after indication received to the Service Changed
*  Characteristic Value. 
* 
*  \param connHandle: The handle which consists of the device ID and ATT connection ID.
*  \param startHandle: Start of affected attribute handle range.
*  \param endHandle: End of affected attribute handle range.
* 
*  \return
*	CYBLE_API_RESULT_T : Return value indicates if the function succeeded or
*                        failed. Following are the possible error codes.
*
*   <table>	
*   <tr>
*	  <th>Errors codes</th>
*	  <th>Description</th>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_OK</td>
*	  <td>On successful operation</td>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_INVALID_PARAMETER</td>
*	  <td>'connHandle' value does not represent any existing entry.</td>
*	</tr>
*	<tr>
*	  <td>CYBLE_ERROR_INVALID_OPERATION</td>
*	  <td>The operation is not permitted</td>
*	</tr>
*   <tr>
*	  <td>CYBLE_ERROR_MEMORY_ALLOCATION_FAILED</td>
*	  <td>Memory allocation failed</td>
*	</tr>
*   <tr>
*	  <td>CYBLE_ERROR_INVALID_STATE</td>
*	  <td>If the function is called in any state except connected or discovered</td>
*	</tr>
*   </table>
* 
*  \events
*  Two events may be generated after calling this function:
*  CYBLE_EVT_GATTC_DISCOVERY_COMPLETE or CYBLE_EVT_GATTC_ERROR_RSP.
*  The CYBLE_EVT_GATTC_DISCOVERY_COMPLETE event is 
*  generated when the remote device was successfully discovered. The
*  CYBLE_EVT_GATTC_ERROR_RSP is generated if the device discovery is failed.
*
******************************************************************************/
CYBLE_API_RESULT_T CyBle_GattcStartPartialDiscovery(CYBLE_CONN_HANDLE_T connHandle,
                        CYBLE_GATT_DB_ATTR_HANDLE_T startHandle, CYBLE_GATT_DB_ATTR_HANDLE_T endHandle)
{
    uint8 j;
    CYBLE_API_RESULT_T apiResult;
    
    if((CyBle_GetState() != CYBLE_STATE_CONNECTED) || 
       ((CyBle_GetClientState() != CYBLE_CLIENT_STATE_CONNECTED) && 
        (CyBle_GetClientState() != CYBLE_CLIENT_STATE_DISCOVERED))) 
    {
        apiResult = CYBLE_ERROR_INVALID_STATE;
    }
    else
    {
        /* Clean old discovery information of affected attribute range */
        for(j = 0u; j < (uint8) CYBLE_SRVI_COUNT; j++)
        {
            if((cyBle_serverInfo[j].range.startHandle >= startHandle) &&
               (cyBle_serverInfo[j].range.startHandle <= endHandle))
            {
                (void)memset(&cyBle_serverInfo[j].range, 0, sizeof(cyBle_serverInfo[0].range));
            }
        }

        cyBle_connHandle = connHandle;
        cyBle_gattcDiscoveryRange.startHandle = startHandle;
        cyBle_gattcDiscoveryRange.endHandle = endHandle;

        CyBle_ServiceInit();

        apiResult = CyBle_GattcDiscoverPrimaryServices(connHandle, &cyBle_gattcDiscoveryRange);

        if(apiResult == CYBLE_ERROR_OK)
        {
            CyBle_SetClientState(CYBLE_CLIENT_STATE_SRVC_DISCOVERING);
            cyBle_eventHandlerFlag |= CYBLE_AUTO_DISCOVERY;
        }
    }
    
    return (apiResult);
}


/******************************************************************************
* Function Name: CyBle_GattcDiscoverCharacteristicsEventHandler
***************************************************************************//**
* 
*  This function is called on receiving a CYBLE_EVT_GATTC_READ_BY_TYPE_RSP
*  event. Based on the service UUID, an appropriate data structure is populated
*  using the data received as part of the callback.
* 
*  \param discCharInfo: The pointer to a characteristic information structure.
* 
* \return
*  None
* 
******************************************************************************/
void CyBle_GattcDiscoverCharacteristicsEventHandler(CYBLE_DISC_CHAR_INFO_T *discCharInfo)
{
    if(discCharInfo->uuid.uuid16 == CYBLE_UUID_CHAR_SERVICE_CHANGED)
    {
        CyBle_CheckStoreCharHandle(cyBle_gattc.serviceChanged);
    }
}


/******************************************************************************
* Function Name: CyBle_GattcDiscoverCharDescriptorsEventHandler
***************************************************************************//**
* 
*  This function is called on receiving a "CYBLE_EVT_GATTC_FIND_INFO_RSP" event.
*  Based on the descriptor UUID, an appropriate data structure is populated 
*  using the data received as part of the callback.
* 
*  \param discDescrInfo: The pointer to a descriptor information structure.
*  \param discoveryService: The index of the service instance
* 
* \return
*  None
* 
******************************************************************************/
void CyBle_GattcDiscoverCharDescriptorsEventHandler(CYBLE_DISC_DESCR_INFO_T *discDescrInfo)
{
    if(discDescrInfo->uuid.uuid16 == CYBLE_UUID_CHAR_CLIENT_CONFIG)
    {
        CyBle_CheckStoreCharDescrHandle(cyBle_gattc.cccdHandle);
    }
}


/******************************************************************************
* Function Name: CyBle_GattcIndicationEventHandler
***************************************************************************//**
* 
*  Handles the Indication Event.
* 
*  \param eventParam: The pointer to the data structure specified by the event.
* 
* \return
*  None.
* 
******************************************************************************/
void CyBle_GattcIndicationEventHandler(CYBLE_GATTC_HANDLE_VALUE_IND_PARAM_T *eventParam)
{
    if(cyBle_gattc.serviceChanged.valueHandle == eventParam->handleValPair.attrHandle)
    {
        CyBle_ApplCallback((uint32)CYBLE_EVT_GATTC_INDICATION, eventParam);
        cyBle_eventHandlerFlag &= (uint8)~CYBLE_CALLBACK;
    }
}


#endif /* (CYBLE_GATT_ROLE_CLIENT) */


/* [] END OF FILE */
