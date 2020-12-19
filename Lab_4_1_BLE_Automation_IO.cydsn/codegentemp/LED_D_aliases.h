/*******************************************************************************
* File Name: LED_D.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_LED_D_ALIASES_H) /* Pins LED_D_ALIASES_H */
#define CY_PINS_LED_D_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define LED_D_0			(LED_D__0__PC)
#define LED_D_0_PS		(LED_D__0__PS)
#define LED_D_0_PC		(LED_D__0__PC)
#define LED_D_0_DR		(LED_D__0__DR)
#define LED_D_0_SHIFT	(LED_D__0__SHIFT)
#define LED_D_0_INTR	((uint16)((uint16)0x0003u << (LED_D__0__SHIFT*2u)))

#define LED_D_1			(LED_D__1__PC)
#define LED_D_1_PS		(LED_D__1__PS)
#define LED_D_1_PC		(LED_D__1__PC)
#define LED_D_1_DR		(LED_D__1__DR)
#define LED_D_1_SHIFT	(LED_D__1__SHIFT)
#define LED_D_1_INTR	((uint16)((uint16)0x0003u << (LED_D__1__SHIFT*2u)))

#define LED_D_2			(LED_D__2__PC)
#define LED_D_2_PS		(LED_D__2__PS)
#define LED_D_2_PC		(LED_D__2__PC)
#define LED_D_2_DR		(LED_D__2__DR)
#define LED_D_2_SHIFT	(LED_D__2__SHIFT)
#define LED_D_2_INTR	((uint16)((uint16)0x0003u << (LED_D__2__SHIFT*2u)))

#define LED_D_3			(LED_D__3__PC)
#define LED_D_3_PS		(LED_D__3__PS)
#define LED_D_3_PC		(LED_D__3__PC)
#define LED_D_3_DR		(LED_D__3__DR)
#define LED_D_3_SHIFT	(LED_D__3__SHIFT)
#define LED_D_3_INTR	((uint16)((uint16)0x0003u << (LED_D__3__SHIFT*2u)))

#define LED_D_INTR_ALL	 ((uint16)(LED_D_0_INTR| LED_D_1_INTR| LED_D_2_INTR| LED_D_3_INTR))


#endif /* End Pins LED_D_ALIASES_H */


/* [] END OF FILE */
