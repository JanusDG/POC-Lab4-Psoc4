/*******************************************************************************
* File Name: main.c
*
* Version 1.10
*
* Description:
*  BLE example project that demonstrates how use BLE component’s
*  Automation IO profile feature and related APIs.
*
* Note:
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

#include "debug.h"
#include "aios.h"

/*******************************************************************************
* Global variables
*******************************************************************************/
AUTHENTICATION_STATE    authState = AUTHENTICATION_NOT_CONNECTED;
CYBLE_GAP_AUTH_INFO_T   peerAuthInfo;
CYBLE_API_RESULT_T      apiResult;
CYBLE_CONN_HANDLE_T     connHandle;
uint32  passkeyValue;
uint32  passkeyPow;
uint8   passkeyCounter;
uint8   buttonState = BUTTON_IS_NOT_CHANGED;
char8   command;
uint8   customCommand = 0u;
const   uint8 ledMask[N_OF_LEDS] = {0x08,0x02,0x01,0x04};
uint16 adcVAlue = 0;


uint16 indyk[4]         = {0x10FF,0x20FF,0x40FF,0x80FF};
const uint8 KOD7[10]    = {0x03,0x9F,0x25,0x0D,0x99,0x49,0x41,0x1F,0x01,0x09};

/* Add an explicit reference to the floating point printf library to allow
the usage of floating point conversion specifier */

#if defined (__GNUC__)
    /* Add an explicit reference to the floating point printf library */
    /* to allow the usage of floating point conversion specifiers. */
    /* This is not linked in by default with the newlib-nano library. */
    asm (".global _printf_float");
#endif

/*******************************************************************************
* Function Name: AppCallBack()
********************************************************************************
*
* Summary:
*   This is an event callback function to receive events from the BLE Component.
*
* Parameters:
*  event - the event code
*  *eventParam - the event parameters
*
* Return:
*   None
*
*******************************************************************************/
void AppCallBack(uint32 event, void* eventParam)
{
    CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T *connParameters;
    
    switch(event)
    {
    case CYBLE_EVT_STACK_ON:
        DBG_PRINTF("EVT_STACK_ON \r\n");
        StartAdvertisement();    
        break;
        
    case CYBLE_EVT_STACK_BUSY_STATUS:
        DBG_PRINTF("EVT_STACK_BUSY_STATUS \r\n");
        break;
        
    case CYBLE_EVT_TIMEOUT: 
        DBG_PRINTF("CYBLE_EVT_TIMEOUT: ");
        switch(*(CYBLE_TO_REASON_CODE_T *)eventParam)
        {
        case CYBLE_GAP_ADV_MODE_TO:
            DBG_PRINTF("CYBLE_GAP_ADV_MODE_TO");
            break;
        case CYBLE_GAP_SCAN_TO:
            DBG_PRINTF("CYBLE_GAP_SCAN_TO");
            break;
        case CYBLE_GATT_RSP_TO:
            DBG_PRINTF("CYBLE_GATT_RSP_TO");
            break;
        case CYBLE_GENERIC_TO:
            DBG_PRINTF("CYBLE_GENERIC_TO");
            break;
        default:    /* Not existing timeout reason */
            DBG_PRINTF("%x", *(uint8 *)eventParam);
            break;
        }
        DBG_PRINTF("\r\n");
        break;
        
	case CYBLE_EVT_HARDWARE_ERROR:    /* This event indicates that some internal HW error has occurred. */
        DBG_PRINTF("EVT_HARDWARE_ERROR \r\n");
		break;
        
    case CYBLE_EVT_HCI_STATUS:
        DBG_PRINTF("EVT_HCI_STATUS \r\n");
		break;
        
    /**********************************************************
    *                       GAP Events
    ***********************************************************/
    case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
        DBG_PRINTF("CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP\r\n");
        if(CYBLE_STATE_DISCONNECTED == CyBle_GetState())
        {   
            /* Fast and slow advertising period complete, go to low power  
             * mode (Hibernate mode) and wait for an external
             * user event to wake up the device again */
            DBG_PRINTF("Hibernate...\r\n");
            Advertising_LED_Write(LED_OFF);
            Digtal_Output_LED_Write(LED_OFF);
            SW2_ClearInterrupt();
            SW2_Interrupt_ClearPending();
            SW2_Interrupt_Start();

            /* Wait until debug info is sent */
            while((UART_DEB_SpiUartGetTxBufferSize() + UART_DEB_GET_TX_FIFO_SR_VALID) != 0);
            CySysPmHibernate();
        }
        break;
        
    case CYBLE_EVT_GAP_DEVICE_CONNECTED:
        connParameters = (CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T *)eventParam;
        DBG_PRINTF("CYBLE_EVT_GAP_DEVICE_CONNECTED: connIntv = %.2f ms.\r\n",   
            (float)connParameters->connIntv * CYBLE_CONN_INTRV_TO_MS);
    
        /* Initiate pairing process */
        if((cyBle_authInfo.security & CYBLE_GAP_SEC_LEVEL_MASK) > CYBLE_GAP_SEC_LEVEL_1)
        {
            apiResult = CyBle_GapAuthReq(cyBle_connHandle.bdHandle, &cyBle_authInfo);
            if(apiResult != CYBLE_ERROR_OK)
            {
                DBG_PRINTF(" CyBle_GapAuthReq API Error: ");
                PrintApiResult();
            }
        }
        else
        {
            authState = AUTHENTICATION_BONDING_COMPLETE;
        }
        Advertising_LED_Write(LED_OFF);
        break;
        
    case CYBLE_EVT_GAPC_CONNECTION_UPDATE_COMPLETE:       
        connParameters = (CYBLE_GAP_CONN_PARAM_UPDATED_IN_CONTROLLER_T *)eventParam;
        DBG_PRINTF("CYBLE_EVT_GAP_DEVICE_CONNECTED: connIntv = %.2f ms.\r\n",   
            (float)connParameters->connIntv * CYBLE_CONN_INTRV_TO_MS);
    
        break;
        
    case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP:
        DBG_PRINTF("CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_RSP: %s\r\n", 
            *(uint16 *)eventParam == 0u ? "Accepted" : "Rejected");
        break;    
        
    case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
        DBG_PRINTF("CYBLE_EVT_GAP_DEVICE_DISCONNECTED\r\n");
        DBG_PRINTF("Device disconnected. \r\n");
        StartAdvertisement();
        break;
                   
    case CYBLE_EVT_GAP_AUTH_REQ:
        peerAuthInfo = *(CYBLE_GAP_AUTH_INFO_T *)eventParam;
        DBG_PRINTF("EVT_AUTH_REQ: security=%x, bonding=%x, ekeySize=%x, err=%x \r\n", 
            peerAuthInfo.security, 
            peerAuthInfo.bonding, 
            peerAuthInfo.ekeySize, 
            peerAuthInfo.authErr);
        break;
        
    case CYBLE_EVT_GAP_PASSKEY_ENTRY_REQUEST:
        DBG_PRINTF("Enter the passkey shown in the peer device: \r\n");
        authState = AUTHENTICATION_WAITING_FOR_PASSKEY;
        passkeyValue = 0u;
        passkeyPow = 100000u;
        passkeyCounter = 0u;
        break;
        
    case CYBLE_EVT_GAP_NUMERIC_COMPARISON_REQUEST:
        DBG_PRINTF("Compare this passkey with displayed in your peer device and press 'y' or 'n': %6.6ld \r\n", 
            *(uint32 *)eventParam);
        authState = AUTHENTICATION_PASSKEY_YES_NO;
        break;
        
    case CYBLE_EVT_GAP_SMP_NEGOTIATED_AUTH_INFO:
        peerAuthInfo = *(CYBLE_GAP_AUTH_INFO_T *)eventParam;
        DBG_PRINTF("CYBLE_EVT_GAP_SMP_NEGOTIATED_AUTH_INFO: security:%x, bonding:%x, ekeySize:%x, authErr %x \r\n", 
            peerAuthInfo.security, 
            peerAuthInfo.bonding, 
            peerAuthInfo.ekeySize, 
            peerAuthInfo.authErr);
        break;

    case CYBLE_EVT_GAP_PASSKEY_DISPLAY_REQUEST:
        DBG_PRINTF("Enter this passkey in your peer device: %6.6ld \r\n", *(uint32 *)eventParam);
        break;
        
    case CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT:
        DBG_PRINTF("CYBLE_EVT_GAP_KEYINFO_EXCHNGE_CMPLT \r\n");
        break;
        
    case CYBLE_EVT_GAP_AUTH_COMPLETE:
        /* Authentication complete; initiate bonding */
        peerAuthInfo = *(CYBLE_GAP_AUTH_INFO_T *)eventParam;
        DBG_PRINTF("AUTH_COMPLETE: security:%x, bonding:%x, ekeySize:%x, authErr %x \r\n", 
            peerAuthInfo.security, 
            peerAuthInfo.bonding, 
            peerAuthInfo.ekeySize, 
            peerAuthInfo.authErr);
        authState = AUTHENTICATION_COMPLETE_BONDING_REQD;
        break;
        
    case CYBLE_EVT_PENDING_FLASH_WRITE:
        DBG_PRINTF("CYBLE_EVT_PENDING_FLASH_WRITE\r\n");
        break;
        
    case CYBLE_EVT_GAP_AUTH_FAILED:
        DBG_PRINTF("EVT_GAP_AUTH_FAILED, reason: ");
        switch(*(CYBLE_GAP_AUTH_FAILED_REASON_T *)eventParam)
        {
            case CYBLE_GAP_AUTH_ERROR_CONFIRM_VALUE_NOT_MATCH:
                DBG_PRINTF("CONFIRM_VALUE_NOT_MATCH\r\n");
                break;
                
            case CYBLE_GAP_AUTH_ERROR_INSUFFICIENT_ENCRYPTION_KEY_SIZE:
                DBG_PRINTF("INSUFFICIENT_ENCRYPTION_KEY_SIZE\r\n");
                break;
            
            case CYBLE_GAP_AUTH_ERROR_UNSPECIFIED_REASON:
                DBG_PRINTF("UNSPECIFIED_REASON\r\n");
                break;
                
            case CYBLE_GAP_AUTH_ERROR_AUTHENTICATION_TIMEOUT:
                DBG_PRINTF("AUTHENTICATION_TIMEOUT\r\n");
                break;
                
            default:
                DBG_PRINTF("0x%x  \r\n", *(CYBLE_GAP_AUTH_FAILED_REASON_T *)eventParam);
                break;
        }

        /* Update authentication state so that bond information could be 
         * removed later.
         */
        authState = AUTHENTICATION_BONDING_COMPLETE;
        break;
        
    case CYBLE_EVT_GAP_ENCRYPT_CHANGE:
        DBG_PRINTF("ENCRYPT_CHANGE: %x \r\n", *(uint8 *)eventParam);
        break;
         
    /**********************************************************
    *                       GATT Events
    ***********************************************************/
    case CYBLE_EVT_GATTC_ERROR_RSP:
        DBG_PRINTF("EVT_GATTC_ERROR_RSP: opcode: ");
        switch(((CYBLE_GATTC_ERR_RSP_PARAM_T *)eventParam)->opCode)
        {
            case CYBLE_GATT_FIND_INFO_REQ:
                DBG_PRINTF("FIND_INFO_REQ");
                break;
                
            case CYBLE_GATT_READ_BY_TYPE_REQ:
                DBG_PRINTF("READ_BY_TYPE_REQ");
                break;
                
            case CYBLE_GATT_READ_BY_GROUP_REQ:
                DBG_PRINTF("READ_BY_GROUP_REQ");
                break;
                
            default:
                DBG_PRINTF("%x", ((CYBLE_GATTC_ERR_RSP_PARAM_T *)eventParam)->opCode);
                break;
        }
        DBG_PRINTF(",  handle: %x,  ", ((CYBLE_GATTC_ERR_RSP_PARAM_T *)eventParam)->attrHandle);
        DBG_PRINTF("errorcode: ");
        switch(((CYBLE_GATTC_ERR_RSP_PARAM_T *)eventParam)->errorCode)
        {
            case CYBLE_GATT_ERR_ATTRIBUTE_NOT_FOUND:
                DBG_PRINTF("ATTRIBUTE_NOT_FOUND");
                break;
                
            default:
                DBG_PRINTF("%x", ((CYBLE_GATTC_ERR_RSP_PARAM_T *)eventParam)->errorCode);
                break;
        }
        DBG_PRINTF("\r\n");
        break;
        
    case CYBLE_EVT_GATT_CONNECT_IND:
        connHandle = *(CYBLE_CONN_HANDLE_T *)eventParam;
        DBG_PRINTF("EVT_GATT_CONNECT_IND: attId %x, bdHandle %x \r\n", connHandle.attId, connHandle.bdHandle);
        break;
        
    case CYBLE_EVT_GATT_DISCONNECT_IND:
        connHandle.attId = 0;
        DBG_PRINTF("EVT_GATT_DISCONNECT_IND \r\n");
        break;
        
    case CYBLE_EVT_GATTS_WRITE_REQ:
        DBG_PRINTF("CYBLE_EVT_GATTS_WRITE_REQ \r\n");
        break;
        
    case CYBLE_EVT_GATTS_WRITE_CMD_REQ:
        DBG_PRINTF("CYBLE_EVT_GATTS_WRITE_CMD_REQ \r\n");
        break;
    
    case CYBLE_EVT_GATTS_HANDLE_VALUE_CNF:
        DBG_PRINTF("CYBLE_EVT_GATTS_HANDLE_VALUE_CNF \r\n");
        break; 
            
    case CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ:
        DBG_PRINTF("CYBLE_EVT_GATTS_READ_CHAR_VAL_ACCESS_REQ, attr handle: 0x%4.4x \r\n",
            ((CYBLE_GATTS_CHAR_VAL_READ_REQ_T *)eventParam)->attrHandle);
        break;
        
     case CYBLE_EVT_GATTS_INDICATION_ENABLED:
        DBG_PRINTF("CYBLE_EVT_GATTS_INDICATION_ENABLED\r\n");
        break;
    
    case CYBLE_EVT_GATTS_INDICATION_DISABLED:
        DBG_PRINTF("CYBLE_EVT_GATTS_INDICATION_DISABLED\r\n");
        break;
        
    case CYBLE_EVT_GATTC_INDICATION:
        DBG_PRINTF("CYBLE_EVT_GATTS_INDICATION\r\n");
        break;
        
    case CYBLE_EVT_GATTS_XCNHG_MTU_REQ:
        { 
            uint16 mtu;
            CyBle_GattGetMtuSize(&mtu);
            DBG_PRINTF("CYBLE_EVT_GATTS_XCNHG_MTU_REQ, final mtu = %d \r\n", mtu);
        }
        break;

    /**********************************************************
    *                       L2CAP Events 
    ***********************************************************/    
        
    case CYBLE_EVT_L2CAP_CONN_PARAM_UPDATE_REQ:
        DBG_PRINTF("EVT_L2CAP_CONN_PARAM_UPDATE_REQ \r\n");
        break;
        
    /**********************************************************
    *                       Debug Events
    ***********************************************************/

    case CYBLE_DEBUG_EVT_BLESS_INT:
        break;
        
    /**********************************************************
    *                       Other Events
    ***********************************************************/
	default:
        DBG_PRINTF("OTHER event: 0x%lx \r\n", event);
		break;
    }
}

/*******************************************************************************
* Function Name: SW_Interrupt
********************************************************************************
*
* Summary:
*   Handles the mechanical button press.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(ButtonPressInt)
{
    buttonState = BUTTON_START_DEBOUNCE;
    SW2_ClearInterrupt();
    Pin_Buttons_ClearInterrupt();
}


/*******************************************************************************
* Function Name: isr_100Hz
********************************************************************************
*
* Summary:
*   Handles the 7-SEG display
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(isr_100Hz)
{
    static uint8 N_indyk   = 0u;
    static uint8 blinkTime = 0u;
    
    SPIM_WriteTxData(indyk[N_indyk]);
    
    N_indyk++;
    N_indyk &= 3;   
    
    if(CyBle_GetState() == CYBLE_STATE_ADVERTISING)
    {
        blinkTime++;
        if(blinkTime > 100)
        {
            Advertising_LED_Write(~Advertising_LED_Read());
            blinkTime = 0;
        }
    }
}

/*******************************************************************************
* Function Name: isr_100Hz
********************************************************************************
*
* Summary:
*   Outputs digit to the 7-SEG display
*
* Parameters:
*   uint16 data
*
* Return:
*   None
*
*******************************************************************************/
void out7seg(uint16 data)
{
    uint8 i;
    
    for (i = 0; i < 4; i++)
    {
        indyk[i] &= 0xFF00;
        indyk[i] |= (uint16)KOD7[data % 10];
        data /= 10;
        if (data == 0) break;
    }
    
    for (i++; i < 4; i++)
    {
        indyk[i] |= 0x00FF;
    }
}

/*******************************************************************************
* Function Name: CapSenseHandler
********************************************************************************
*
* Summary:
*   Handles the CapSense events.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void CapSenseHandler(void)
{
    static uint16 sliderPrevPosition = CapSense_SLIDER_NO_TOUCH;
    uint16 sliderPosition = 0;
    uint8 i;
    
    /* Do this only when a scan is done */
    if(CapSense_NOT_BUSY == CapSense_IsBusy())
    {
        /* Process all widgets */
        CapSense_ProcessAllWidgets();
        
        if( CapSense_GetCentroidPos(0u) != CapSense_SLIDER_NO_TOUCH)
        {   
            sliderPosition = CapSense_GetCentroidPos(0u);
    
            if ( sliderPrevPosition != sliderPosition )
            { 
                // code added
                CyBle_AiossSendNotification(connHandle, CYBLE_AIOS_ANALOG, INSTANCE_DISPLAY, sizeof(sliderPrevPosition), (uint8 *)&sliderPrevPosition);
                //
                
                
                sliderPrevPosition = sliderPosition;
            
                out7seg(sliderPosition);
                
                DBG_PRINTF("%4d (0x%02X) ", sliderPosition, sliderPosition);
            
                for(i = 0; i < 20 ; i++)
                {                   
                    if( i < (sliderPosition / 5u))
                    {
                        DBG_PRINTF("#");
                    }
                    else
                    {
                        DBG_PRINTF("-");
                    }
                }    
                DBG_PRINTF("\r");
                DBG_PRINTF("\n");

                apiResult = CyBle_AiossSetCharacteristicValue(CYBLE_AIOS_ANALOG,
                    INSTANCE_SLIDER, sizeof(sliderPosition), (uint8 *)&sliderPosition );
                
                if(apiResult != CYBLE_ERROR_OK)
                {
                    DBG_PRINTF("CyBle_AiossSetCharacteristicValue API Error - %x \r\n", apiResult);
                }
            }
        }
        else
        {
            if (sliderPrevPosition != CapSense_SLIDER_NO_TOUCH)
            {
                sliderPrevPosition = CapSense_SLIDER_NO_TOUCH;
                DBG_PRINTF("\r\n");
            }
        }
    }
}



/*******************************************************************************
* Function Name: IdacHandler
********************************************************************************
*
* Summary:
*   Handles the IDAC process.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void PWMHandler(void)
{
    static uint16 pwmPrevValue = 0;
    uint16 pwmValue = 0;
        
    apiResult = CyBle_AiossGetCharacteristicValue(CYBLE_AIOS_ANALOG,
                INSTANCE_PWM, sizeof(pwmValue), (uint8 *)&pwmValue );
            
    if(apiResult != CYBLE_ERROR_OK)
    {
        DBG_PRINTF("CyBle_AiossGetCharacteristicValue API Error - %x\r\n", apiResult);
    }
    else
    {   
        if (pwmPrevValue != pwmValue)
        {   
            PWM_WriteCompare(255 - pwmValue);
            DBG_PRINTF("PWM value changed. New periodt - %d \r\n", pwmValue);
            pwmPrevValue = pwmValue;
        }
    }
}

/*******************************************************************************
* Function Name: OutputLedHandler
********************************************************************************
*
* Summary:
*   Handles the output LED.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void OutputLedHandler(void)
{
    static uint8 ledPrevValue[N_OF_LEDS] = {3,3,3,3};
    
    uint8 ledValue = 0;
    uint8 i;
    
    for (i = 0; i < N_OF_LEDS; i++)
    {
        apiResult = CyBle_AiossGetCharacteristicValue(CYBLE_AIOS_DIGITAL,
                    INSTANCE_DIGITAL_LED_D1 + i, sizeof(ledValue), (uint8 *)&ledValue  );
                
        if(apiResult != CYBLE_ERROR_OK)
        {
            DBG_PRINTF("CyBle_AiossGetCharacteristicValue API Error - %x\r\n", apiResult);
        }
        else
        {   
            if (ledPrevValue[i] != ledValue)
            {
                ledPrevValue[i] = ledValue;
                
                if ((ledValue & 0x01) == 0u)
                {
                    ledValue = LED_D_Read();
                    ledValue |= ledMask[i];
                    LED_D_Write(ledValue);
                    DBG_PRINTF("LED D%d OFF\r\n",i+1);
                }
                else
                {   ledValue = LED_D_Read();
                    ledValue &= ~ledMask[i];
                    LED_D_Write(ledValue);
                    DBG_PRINTF("LED D%d ON\r\n",i+1);
                }
            }
        }
    }
   
}        

/*******************************************************************************
* Function Name: ButtonHandler
********************************************************************************
*
* Summary:
*   Handles the SW2 button.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void ButtonHandler(void)
{
    static uint8 buttonsPrevState = 0x0F;
    uint8 i;
    
    if (buttonState != BUTTON_IS_NOT_CHANGED)
    {   
        buttonState--;
    }
    
    if (buttonState == BUTTON_IS_CHANGED)
    {
        buttonState = (SW2_Read() << 3) | Pin_Buttons_Read();
        
        /* Accept displayed passkey */
        if(authState == AUTHENTICATION_PASSKEY_YES_NO)
        {   
            if(CyBle_GetState() == CYBLE_STATE_CONNECTED)
            {   
                if (((buttonsPrevState ^ buttonState) & BUTTON_SW2_MASK) == BUTTON_SW2_MASK)
                {
                    if ((buttonState & BUTTON_SW2_MASK) == BUTTON_IS_NOT_PRESSED)
                    {   
                        customCommand = 'y';
                    }
                }
            }
            buttonsPrevState = buttonState;
        }
        else
        {
            for (i = 0; i < 3; i++)
            {
                if (((buttonsPrevState ^ buttonState) & (1 << i)) != (1 << i))
                {
                    continue;
                }

                buttonsPrevState = buttonState;
                
                buttonState >>= i;
                buttonState &= 1;
               
                apiResult = CyBle_AiossSetCharacteristicValue(CYBLE_AIOS_DIGITAL,
                            INSTANCE_DIGITAL_INPUT + i, sizeof(buttonState), &buttonState);
            
                if(apiResult != CYBLE_ERROR_OK)
                {
                    DBG_PRINTF("CyBle_AiossSetCharacteristicValue API Error - %x \r\n", apiResult);
                }
                else
                {
                    if (buttonState == BUTTON_IS_PRESSED)
                    {
                        DBG_PRINTF("\n\rButton S%d is pressed. Digital input = 0.\r\n",i+1);
                    }
                    else
                    {
                        DBG_PRINTF("\n\rButton S%d is released. Digital input = 1.\r\n",i+1);
                    }
                }
           
                if(CyBle_GetState() == CYBLE_STATE_CONNECTED)
                {
                    if (i == 0){
                    
                        apiResult = CyBle_AiossSendIndication(cyBle_connHandle, CYBLE_AIOS_ANALOG, INSTANCE_ADC, sizeof(adcVAlue), (uint8 *)&adcVAlue);

                        if(apiResult != CYBLE_ERROR_OK)
                        {
                            DBG_PRINTF("Send Indication is failed: ");
                            PrintApiResult();
                        }
                        else
                        {   
                            DBG_PRINTF("Indication was sent successfully.\r\n");
                        }
                    }
                    else{
                        DBG_PRINTF("DIGITAL %d characteristic Indication. ",i+1);
                        DBG_PRINTF("Value - %d. ",buttonState);
                                           
                        apiResult = CyBle_AiossSendIndication(cyBle_connHandle, CYBLE_AIOS_DIGITAL, INSTANCE_DIGITAL_INPUT + i, sizeof(buttonState), &buttonState);

                        if(apiResult != CYBLE_ERROR_OK)
                        {
                            DBG_PRINTF("Send Indication is failed: ");
                            PrintApiResult();
                        }
                        else
                        {   
                            DBG_PRINTF("Indication was sent successfully.\r\n");
                        }
                    }
                }
                break;
            }
        }
        buttonState = BUTTON_IS_NOT_CHANGED;
    }
}

/*******************************************************************************
* Function Name: AuthenticationHandler
********************************************************************************
*
* Summary:
*   Handles the SW2 button.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void AuthenticationHandler(void)
{
    switch(authState)
    {
    case AUTHENTICATION_PASSKEY_YES_NO:
        
        if(((command = UART_DEB_GET_CHAR()) != 0u) || (customCommand != 0u))
        {
            if((command == 0u) && (customCommand != 0u))
            {
                command = customCommand;
                customCommand = 0u;
            }
            if(command == 'y')
            {
                DBG_PRINTF("Accept displayed passkey \r\n");
                apiResult = CyBle_GapAuthPassKeyReply(cyBle_connHandle.bdHandle, 0u, CYBLE_GAP_ACCEPT_PASSKEY_REQ);
                if(apiResult != CYBLE_ERROR_OK)
                {
                    DBG_PRINTF("CyBle_GapAuthPassKeyReply API Error : ");
                    PrintApiResult();
                }
                authState = AUTHENTICATION_PASSKEY_ENTERED;
            }
            else if(command == 'n')
            {
                DBG_PRINTF("Reject displayed passkey \r\n");
                apiResult = CyBle_GapAuthPassKeyReply(cyBle_connHandle.bdHandle, 0u, CYBLE_GAP_REJECT_PASSKEY_REQ);
                if(apiResult != CYBLE_ERROR_OK)
                {
                    DBG_PRINTF("CyBle_GapAuthPassKeyReply API Error : ");
                    PrintApiResult();
                }
               authState = AUTHENTICATION_PASSKEY_ENTERED;
            }
            else
            {
                DBG_PRINTF("Wrong key entered. Press 'y' or 'n'\r\n");
            }
        }
        break;
           
    case AUTHENTICATION_WAITING_FOR_PASSKEY:
     
        /* Get 6 digit number from UART terminal */

        if((command = UART_DEB_GET_CHAR()) != 0u)
        {   
            /* accept the digits that are in the range of '0' to '9' */
            if((command >= '0') && (command <= '9'))  
            {
                passkeyValue += (uint32)(command - '0') * passkeyPow;
                passkeyPow /= 10u;
                passkeyCounter++;
                UART_DEB_PUT_CHAR(command); 
            }
            else  /* If entered digit is not in the range of '0' to '9' */
            {
               DBG_PRINTF("Wrong key entered. \r\n");
            }

            if(passkeyCounter == CYBLE_GAP_USER_PASSKEY_SIZE)
            {
                DBG_PRINTF("\r\n");
                /* Send Pass key Response to create an Authenticated Link */
                apiResult = CyBle_GapAuthPassKeyReply(cyBle_connHandle.bdHandle, passkeyValue, CYBLE_GAP_ACCEPT_PASSKEY_REQ);
                if(apiResult != CYBLE_ERROR_OK)
                {
                    DBG_PRINTF("CyBle_GapAuthPassKeyReply API Error: ");
                    PrintApiResult();
                }
                authState = AUTHENTICATION_PASSKEY_ENTERED;
            }
        }
        break;

    case AUTHENTICATION_BONDING_COMPLETE:
        break;

    default:    /* Not supported state */
        break;
    }  
}

/*******************************************************************************
* Function Name: LowPowerImplementation()
********************************************************************************
* Summary:
* Implements low power in the project.
*
* Theory:
* The function tries to enter deep sleep as much as possible - whenever the 
* BLE is idle and the UART transmission/reception is not happening. At all other
* times, the function tries to enter CPU sleep.
*
*******************************************************************************/
static void LowPowerImplementation(void)
{
    CYBLE_LP_MODE_T bleMode;
    uint8 interruptStatus;
    
    /* For advertising and connected states, implement deep sleep 
     * functionality to achieve low power in the system. For more details
     * on the low power implementation, refer to the Low Power Application 
     * Note.
     */
    if(((CyBle_GetState() == CYBLE_STATE_ADVERTISING) || 
        (CyBle_GetState() == CYBLE_STATE_CONNECTED)) &&
        (CapSense_NOT_BUSY == CapSense_IsBusy()))
    {
        /* Request BLE subsystem to enter into Deep-Sleep mode between connection and advertising intervals */
        bleMode = CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
        /* Disable global interrupts */
        interruptStatus = CyEnterCriticalSection();
        /* When BLE subsystem has been put into Deep-Sleep mode */
        if(bleMode == CYBLE_BLESS_DEEPSLEEP)
        {
            /* And it is still there or ECO is on */
            if((CyBle_GetBleSsState() == CYBLE_BLESS_STATE_ECO_ON) || 
               (CyBle_GetBleSsState() == CYBLE_BLESS_STATE_DEEPSLEEP))
            {
                /* Put the CPU into the Deep-Sleep mode when all debug information has been sent */
                if((UART_DEB_GET_TX_BUFF_SIZE() + UART_DEB_GET_TX_FIFO_SR_VALID) == 0u)
                {
                    CySysPmDeepSleep();
                }
                else /* Put the CPU into Sleep mode and let SCB to continue sending debug data */
                {
                    CySysPmSleep();
                }
            }
        }
        else /* When BLE subsystem has been put into Sleep mode or is active */
        {
            /* And hardware doesn't finish Tx/Rx operation - put the CPU into Sleep mode */
            if(CyBle_GetBleSsState() != CYBLE_BLESS_STATE_EVENT_CLOSE)
            {
                CySysPmSleep();
            }
        }
        /* Enable global interrupt */
        CyExitCriticalSection(interruptStatus);
    }
}


/*******************************************************************************
* Function Name: Adc
********************************************************************************
*
* Summary:
*   Handles the CapSense events.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void AdcHandler(void)
{
    static uint16 prevAdcVAlue  = 0;
    adcVAlue = 0;
    
    uint16 validRange[2];
    uint8 i;
    
    adcVAlue = ADC_GetResult16(0);
    adcVAlue = ADC_CountsTo_mVolts(0, adcVAlue);
    

    if ( prevAdcVAlue != adcVAlue )
    { 
        prevAdcVAlue = adcVAlue;
    
        //out7seg(adcVAlue);
        
        DBG_PRINTF("ADC = %4d\r\n ", adcVAlue);
    
        apiResult = CyBle_AiossSetCharacteristicValue(CYBLE_AIOS_ANALOG,
        INSTANCE_ADC, sizeof(adcVAlue), (uint8 *)&adcVAlue );
        
        if(apiResult != CYBLE_ERROR_OK)
        {
           DBG_PRINTF("CyBle_AiossSetCharacteristicValue API Error - %x \r\n", apiResult);
        }
        
        if(CyBle_GetState() == CYBLE_STATE_CONNECTED)
        {
            
            CyBle_AiossGetCharacteristicDescriptor(CYBLE_AIOS_ANALOG,
                INSTANCE_ADC, CYBLE_AIOS_VRD, sizeof(validRange), (uint8 *)&validRange);
            
            
            DBG_PRINTF("DIGITAL %d characteristic Indication. ",i+1);
            DBG_PRINTF("Value - %d  %d. ",validRange[0], validRange[1]);
             
            if (adcVAlue < validRange[1] || adcVAlue > validRange[0]){
                
                apiResult = CyBle_AiossSendIndication(cyBle_connHandle, CYBLE_AIOS_ANALOG, INSTANCE_ADC, sizeof(adcVAlue), (uint8 *)&adcVAlue);

                if(apiResult != CYBLE_ERROR_OK)
                {
                    DBG_PRINTF("Send Indication is failed: ");
                    PrintApiResult();
                }
                else
                {   
                    DBG_PRINTF("Indication was sent successfully.\r\n");
                }
            
            }
        }
    }   
}


/*******************************************************************************
* Function Name: DISPLAY
********************************************************************************
*
* Summary:
*   Handles the CapSense events.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void DisplayHandler(void)
{
    static uint16 prevDisplayVAlue  = 0;
    uint16 displayValue = 1200;
    
    uint16 validRange[2];
    uint8 i;
    
    displayValue = adcVAlue;

    

    if ( prevDisplayVAlue != displayValue )
    { 
        prevDisplayVAlue = adcVAlue;
    
        DBG_PRINTF("ADC = %4d\r\n ", displayValue);
    
        apiResult = CyBle_AiossSetCharacteristicValue(CYBLE_AIOS_ANALOG,
        INSTANCE_ADC, sizeof(displayValue), (uint8 *)&displayValue );
        
        if(apiResult != CYBLE_ERROR_OK)
        {
           DBG_PRINTF("CyBle_AiossSetCharacteristicValue API Error - %x \r\n", apiResult);
        }
        
        if(CyBle_GetState() == CYBLE_STATE_CONNECTED)
        {
            
            CyBle_AiossGetCharacteristicDescriptor(CYBLE_AIOS_ANALOG,
                INSTANCE_DISPLAY, CYBLE_AIOS_CHAR_USER_DESCRIPTION_DESCR, sizeof(displayValue), (uint8 *)&displayValue);
            
            
            DBG_PRINTF("DIGITAL %d characteristic Indication. ",i+1);
            DBG_PRINTF("Value - %d  %d. ",validRange[0], validRange[1]);
             
           
            if (displayValue < validRange[1] || displayValue > validRange[0]){
                
                apiResult = CyBle_AiossSendIndication(cyBle_connHandle, CYBLE_AIOS_ANALOG, INSTANCE_ADC, sizeof(displayValue), (uint8 *)&displayValue);
                out7seg(displayValue);
             
                if(apiResult != CYBLE_ERROR_OK)
                {
                    DBG_PRINTF("Send Indication is failed: ");
                    PrintApiResult();
                }
                else
                {   
                    DBG_PRINTF("Indication was sent successfully.\r\n");
                }
                
            }else
            {   
                DBG_PRINTF("Error! value not in range.\r\n");
                out7seg(0);
            }
        
        
        }
    }   
}

/*******************************************************************************
* Function Name: main()
********************************************************************************
* Summary:
*  Main function for the project.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Theory:
*  The function starts BLE, UART, IDAC and CapSense components.
*  This function process all BLE events and also implements the low power 
*  functionality.
*
*******************************************************************************/
int main()
{
    CyGlobalIntEnable;
    
    Digtal_Output_LED_Write(LED_OFF);
    Advertising_LED_Write(LED_OFF);
    
    /* Start communication component */
    UART_START();               
    
    SPIM_Start();
    PWM_Start();
    
    DBG_PRINTF("\r\n\nAutomation IO Server Example Project \r\n");
    
    /* Start CYBLE component and register generic event handler */
    apiResult = CyBle_Start(AppCallBack);
    if(apiResult != CYBLE_ERROR_OK)
    {
        DBG_PRINTF("CyBle_Start API Error: ");
        PrintApiResult();
    }

    /* Services initialization */
    AiosInit();
    
    PrintStackVersion();
    
    /* Start CapSense block */
    CapSense_Start();
    
    /* Scan all widgets */
    CapSense_ScanAllWidgets();

    SW2_Interrupt_StartEx(&ButtonPressInt);
    
    /* Register Timer_Interrupt() by the WDT COUNTER2 to generate interrupt every second */
    CySysWdtSetInterruptCallback(CY_SYS_WDT_COUNTER2, isr_100Hz);
    /* Enable the COUNTER2 ISR handler. */
    CySysWdtEnableCounterIsr(CY_SYS_WDT_COUNTER2);
    
    /* Init and start sequencing SAR ADC */
    ADC_Start();
    ADC_StartConvert();
    
    /***************************************************************************
    * Main polling loop
    ***************************************************************************/
    while(1u)
    {   
        /*******************************************************************
        *  To achieve low power in the device
        *******************************************************************/
        if(( authState != AUTHENTICATION_PASSKEY_YES_NO)
        && ( authState != AUTHENTICATION_WAITING_FOR_PASSKEY) )
        {   
           // LowPowerImplementation();
        }

        /* Start next scan */
        CapSense_ScanAllWidgets();
        
        /*******************************************************************
        *  Process IDAC handling
        *******************************************************************/
        PWMHandler();
        
        /*******************************************************************
        *  Process output LED handling
        *******************************************************************/
        OutputLedHandler();

        /*******************************************************************
        *  Process CapSense events handling
        *******************************************************************/
        CapSenseHandler();
        
        /*******************************************************************
        *  Process ADC events handling
        *******************************************************************/
        AdcHandler();
        
        /*******************************************************************
        *  Process DISPLAY events handling
        *******************************************************************/
        DisplayHandler();
        
        /*******************************************************************
        *  Process all pending BLE events in the stack
        *******************************************************************/
        CyBle_ProcessEvents();
        
        /*******************************************************************
        *  Process Button SW2 handling
        *******************************************************************/
        ButtonHandler();
        
         /*******************************************************************
        *  Authentication procdure handling
        *******************************************************************/
        AuthenticationHandler();
        
        /* Store bonding data to flash only when all debug information has been sent */
        #if(CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES)
        if((cyBle_pendingFlashWrite != 0u) &&
            ((UART_DEB_GET_TX_BUFF_SIZE() + UART_DEB_GET_TX_FIFO_SR_VALID) == 0u))
            {
                apiResult = CyBle_StoreBondingData(0u);
                DBG_PRINTF("Store bonding data, status: %x \r\n", apiResult);
            }
        #endif /* CYBLE_BONDING_REQUIREMENT == CYBLE_BONDING_YES */    
    }
}

/* [] END OF FILE */
