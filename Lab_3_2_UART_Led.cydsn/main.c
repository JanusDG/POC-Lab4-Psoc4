/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>

#define LED_ON  0
#define LED_OFF 1

int main()
{
    uint8 ch;

    CyGlobalIntEnable;

    Pin_D1_Write(LED_OFF);
    Pin_D2_Write(LED_OFF);
    Pin_D3_Write(LED_OFF);
    Pin_D4_Write(LED_OFF);
                    
    /* Start SCB UART TX+RX operation */    
    UART_Start(); 
    
    CyDelay(1000);
    
	UART_UartPutString("LAB 3.2 \r\n");
    
    for(;;)
    {
        ch = UART_UartGetChar();
        
        if (ch==0) continue;
        
        UART_UartPutChar(ch);
        
        switch(ch)
        {   
            case '1' : Pin_D1_Write(~Pin_D1_Read());
                       break;
            
            case '2' : Pin_D2_Write(~Pin_D2_Read()); 
                       break;
            
            case '3' : Pin_D3_Write(~Pin_D3_Read()); 
                       break;
            
            case '4' : Pin_D4_Write(~Pin_D4_Read()); 
                       break;
            
            case ' ' : Pin_D1_Write(LED_OFF);
                       Pin_D2_Write(LED_OFF);
                       Pin_D3_Write(LED_OFF);
                       Pin_D4_Write(LED_OFF);
                       break;
                    
            default  : UART_UartPutString("ERROR\r\n");
        }
    }
}


/* [] END OF FILE */
