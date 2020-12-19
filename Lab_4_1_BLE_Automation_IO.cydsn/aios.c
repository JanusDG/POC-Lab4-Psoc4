/*******************************************************************************
* File Name: aios.c
*
* Version 1.10
*
* Description:
*  This file contains AIO service related code.
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

#include "aios.h"
#include "debug.h"

/******************************************************************************
* Function Name: AiosInit
*******************************************************************************
*
* Summary:
*    Registers the AIOS CallBack.
*
******************************************************************************/
void AiosInit(void)
{
    CyBle_AiosRegisterAttrCallback(AiosCallBack);
}

/*******************************************************************************
* Function Name: AiosCallBack()
********************************************************************************
*
* Summary:
*   This is an event callback function to receive service specific events from
*   Autonation IO Service.
*
* Parameters:
*  event - the event code
*  *eventParam - the event parameters
*
* Return:
*  None.
*
********************************************************************************/
void AiosCallBack(uint32 event, void* eventParam)
{
    CYBLE_AIOS_CHAR_VALUE_T *locCharValue;
    CYBLE_AIOS_DESCR_VALUE_T *locDescrValue;
    uint8 i, ledValue;
    
    if(0u != eventParam)
    {
        /* This dummy operation is to avoid warning about unused eventParam */
    }

    switch(event)
    {
    case CYBLE_EVT_AIOSS_NOTIFICATION_ENABLED:
        DBG_PRINTF("CYBLE_EVT_AIOSS_NOTIFICATION_ENABLED: ");
        PrintCharacteristic(((CYBLE_AIOS_CHAR_VALUE_T *) eventParam)->charIndex);
        DBG_PRINTF(" characteristic, instance: %d",((CYBLE_AIOS_CHAR_VALUE_T *) eventParam)->charInstance);
        DBG_PRINTF(" notification is Enabled \r\n");
        break;
                
    case CYBLE_EVT_AIOSS_NOTIFICATION_DISABLED:
        DBG_PRINTF("CYBLE_EVT_AIOSS_NOTIFICATION_DISABLED: ");
        PrintCharacteristic(((CYBLE_AIOS_CHAR_VALUE_T *)eventParam)->charIndex);
        DBG_PRINTF(" characteristic, instance: %d",((CYBLE_AIOS_CHAR_VALUE_T *) eventParam)->charInstance);
        DBG_PRINTF(" notification is Disabled \r\n");
        break;

    case CYBLE_EVT_AIOSS_INDICATION_ENABLED:
        DBG_PRINTF("CYBLE_EVT_AIOSS_INDICATION_ENABLED: ");
        PrintCharacteristic(((CYBLE_AIOS_CHAR_VALUE_T *) eventParam)->charIndex);
        DBG_PRINTF(" characteristic, instance: %d",((CYBLE_AIOS_CHAR_VALUE_T *) eventParam)->charInstance);
        DBG_PRINTF(" indication is Enabled \r\n");
        if ((((CYBLE_AIOS_CHAR_VALUE_T *) eventParam)->charIndex == CYBLE_AIOS_ANALOG)
        && (((CYBLE_AIOS_CHAR_VALUE_T *) eventParam)->charInstance == INSTANCE_ADC)){
            ledValue = LED_D_Read();
            ledValue |= 1; //&= ~ledMask[i];
            ledValue |= 2; //&= ~ledMask[i];
            LED_D_Write(ledValue);
            CyDelay(400);
            ledValue &= ~2; //&= ~ledMask[i];
            LED_D_Write(ledValue);
        }
        
        break;
        
    case CYBLE_EVT_AIOSS_INDICATION_DISABLED:
        DBG_PRINTF("CYBLE_EVT_AIOSS_INDICATION_DISABLED: ");
        PrintCharacteristic(((CYBLE_AIOS_CHAR_VALUE_T *)eventParam)->charIndex);
        DBG_PRINTF(" characteristic, instance: %d",((CYBLE_AIOS_CHAR_VALUE_T *) eventParam)->charInstance);
        DBG_PRINTF(" indication is Disabled \r\n");
        if ((((CYBLE_AIOS_CHAR_VALUE_T *) eventParam)->charIndex == CYBLE_AIOS_ANALOG)
        && (((CYBLE_AIOS_CHAR_VALUE_T *) eventParam)->charInstance == INSTANCE_ADC)){
            ledValue = LED_D_Read();
            ledValue &= ~1; //&= ~ledMask[i];
            LED_D_Write(ledValue);
        }
        break;
    
    case CYBLE_EVT_AIOSS_INDICATION_CONFIRMED:
        DBG_PRINTF("CYBLE_EVT_AIOSS_INDICATION_CONFIRMED: ");
        PrintCharacteristic(((CYBLE_AIOS_CHAR_VALUE_T *)eventParam)->charIndex);
        DBG_PRINTF(" characteristic, instance: %d",((CYBLE_AIOS_CHAR_VALUE_T *) eventParam)->charInstance);
        DBG_PRINTF(" indication is Confirmed \r\n");
        break;

    case CYBLE_EVT_AIOSS_CHAR_WRITE:
        locCharValue=eventParam;
        DBG_PRINTF("CYBLE_EVT_AIOSS_CHAR_WRITE charIndex - "); 
        PrintCharacteristic(locCharValue->charIndex);        
        DBG_PRINTF(", charInstance - %d, ", locCharValue->charInstance);
        DBG_PRINTF("value - %d (0x%2.2X)  len - %d\r\n",(locCharValue->value->len == 1) ? locCharValue->value->val[0]:CyBle_AiosGet16ByPtr(locCharValue->value->val),
                                                    (locCharValue->value->len == 1) ? locCharValue->value->val[0]:CyBle_AiosGet16ByPtr(locCharValue->value->val),
                                                     locCharValue->value->len);
        break;
        
    case CYBLE_EVT_AIOSS_DESCR_WRITE:
        locDescrValue=eventParam;
        DBG_PRINTF("CYBLE_EVT_AIOSS_DESCR_WRITE charIndex - "); 
        PrintCharacteristic(locDescrValue->charIndex);        
        DBG_PRINTF(", charInstance -  %d,",locDescrValue->charInstance);
        DBG_PRINTF(" descrIndex - ");
        PrintDescriptor(locDescrValue->descrIndex);
        DBG_PRINTF(", ");
        
        if (locDescrValue->value->len <= 2)
        {
            DBG_PRINTF("value - %d (0x%2.2X)  ", (locDescrValue->value->len == 1) ? locDescrValue->value->val[0]:CyBle_AiosGet16ByPtr(locDescrValue->value->val),
                                      (locDescrValue->value->len == 1) ? locDescrValue->value->val[0]:CyBle_AiosGet16ByPtr(locDescrValue->value->val));
        }
        else
        {   
            DBG_PRINTF("value - ");
            for(i = 0; i < locDescrValue->value->len; i++)
            {
                DBG_PRINTF("%2.2X ", locDescrValue->value->val[i]);
            }    
            DBG_PRINTF(" (");
            for(i = 0; i < locDescrValue->value->len; i++)
            {
                DBG_PRINTF("%c", (locDescrValue->value->val[i] >= 0x20) ? locDescrValue->value->val[i] : '*');
            }    
            DBG_PRINTF(")  ");
        }
        DBG_PRINTF("len - %d\r\n", locDescrValue->value->len);
        break;
        
    default:
        DBG_PRINTF("unknown AIOS event: 0x%lx \r\n", event);
        break;
    }
}

/*******************************************************************************
* Function Name: PrintCharacteristic
********************************************************************************
*
* Summary:
*  Prints the characteristic name of Automation IO service.
*
* Parameters:  
*  charIndex: Characteristic index.
*
* Return: 
*  None
*
*******************************************************************************/
void PrintCharacteristic(CYBLE_AIOS_CHAR_INDEX_T charIndex)
{
    switch(charIndex)
    {
    case CYBLE_AIOS_DIGITAL:
        DBG_PRINTF("DIGITAL");
        break;
    case CYBLE_AIOS_ANALOG:
        DBG_PRINTF("ANALOG");
        break;
    case CYBLE_AIOS_AGGREGATE:
        DBG_PRINTF("AGGREGATE");
        break;
    default:
        break;
    }
}


/*******************************************************************************
* Function Name: PrintDescriptor
********************************************************************************
*
* Summary:
*  Prints the characteristic descriptor name of Automation IO service.
*
* Parameters:  
*  descrIndex: Characteristic index.
*
* Return: 
*  None
*
*******************************************************************************/
void PrintDescriptor(CYBLE_AIOS_DESCR_INDEX_T descrIndex)
{
    switch(descrIndex)
    {
    case CYBLE_AIOS_CCCD:
        DBG_PRINTF("CCCD");
        break;
    case CYBLE_AIOS_CHAR_PRESENTATION_FORMAT:
        DBG_PRINTF("CHAR_PRESENTATION_FORMAT");
        break;
    case CYBLE_AIOS_CHAR_USER_DESCRIPTION_DESCR:
        DBG_PRINTF("CHAR_USER_DESCRIPTION_DESCR");
        break;
    case CYBLE_AIOS_CHAR_EXTENDED_PROPERTIES:
        DBG_PRINTF("CHAR_EXTENDED_PROPERTIES");
        break;
    case CYBLE_AIOS_VALUE_TRIGGER_SETTINGS:
        DBG_PRINTF("VALUE_TRIGGER_SETTINGS");
        break;
    case CYBLE_AIOS_TIME_TRIGGER_SETTINGS:
        DBG_PRINTF("TIME_TRIGGER_SETTINGS");
        break;
    case CYBLE_AIOS_VRD:
        DBG_PRINTF("VRD");
        break;
    default:
        break;
    }
}

/*******************************************************************************
* Function Name: StartAdvertisement
********************************************************************************
*
* Summary:
*   Initiates the advertisement procedure. 
*   Prints the Device Address.
*
* Parameters:  
*   None.
*
* Return:
*   None.
*
*******************************************************************************/
void StartAdvertisement(void)
{
    CYBLE_GAP_BD_ADDR_T localAddr;
    uint16 i;
    apiResult = CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
    if(apiResult != CYBLE_ERROR_OK)
    {
        DBG_PRINTF("StartAdvertisement API Error: ");
        PrintApiResult();
    }
    else
    {
        DBG_PRINTF("Start Advertisement with addr: ");
        CyBle_GetDeviceAddress(&localAddr);
        for(i = CYBLE_GAP_BD_ADDR_SIZE; i > 0u; i--)
        {
            DBG_PRINTF("%2.2x", localAddr.bdAddr[i-1]);
        }
        DBG_PRINTF("\r\n");
        Advertising_LED_Write(LED_ON);
    }
}
/* [] END OF FILE */
