/*******************************************************************************
* File Name: debug.h
*
* Version 1.10
*
* Description:
*  Contains the function prototypes and constants available to the example
*  project.
*
********************************************************************************
* Copyright 2018, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(DBG_H)
#define DBG_H
  
/***************************************
* Conditional Compilation Parameters
***************************************/
#define YES                                 (1u)
#define NO                                  (0u)

#define DEBUG_UART_ENABLED                  (YES)
    
/***************************************
*        Macros
***************************************/
#if (DEBUG_UART_ENABLED == YES)
    #define DBG_PRINTF(...)                 (printf(__VA_ARGS__))
    #define UART_DEB_PUT_CHAR(...)          (UART_DEB_UartPutChar(__VA_ARGS__))
    #define UART_DEB_GET_CHAR(...)          (UART_DEB_UartGetChar(__VA_ARGS__))
    #define UART_DEB_GET_TX_BUFF_SIZE(...)  (UART_DEB_SpiUartGetTxBufferSize(__VA_ARGS__))
    #define UART_START(...)                 (UART_DEB_Start(__VA_ARGS__))
#else
    #define DBG_PRINTF(...)
    #define UART_DEB_PUT_CHAR(...)
    #define UART_DEB_GET_CHAR(...)          (0u)
    #ifndef UART_DEB_GET_TX_FIFO_SR_VALID
        #define UART_DEB_GET_TX_FIFO_SR_VALID   (0u)
    #endif
    #define UART_DEB_GET_TX_BUFF_SIZE(...)
    #define UART_START(...)
#endif /* (DEBUG_UART_ENABLED == ENABLED) */

/***************************************
*      API Function Prototypes
***************************************/
int _write(int file, char *ptr, int len);
void PrintStackVersion(void);
void PrintState(void);
void PrintApiResult(void);

#endif /* DBG_H */

/* [] END OF FILE */
