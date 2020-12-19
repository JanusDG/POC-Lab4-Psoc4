/*******************************************************************************
* File Name: Pin_Buttons.h  
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

#if !defined(CY_PINS_Pin_Buttons_ALIASES_H) /* Pins Pin_Buttons_ALIASES_H */
#define CY_PINS_Pin_Buttons_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Pin_Buttons_0			(Pin_Buttons__0__PC)
#define Pin_Buttons_0_PS		(Pin_Buttons__0__PS)
#define Pin_Buttons_0_PC		(Pin_Buttons__0__PC)
#define Pin_Buttons_0_DR		(Pin_Buttons__0__DR)
#define Pin_Buttons_0_SHIFT	(Pin_Buttons__0__SHIFT)
#define Pin_Buttons_0_INTR	((uint16)((uint16)0x0003u << (Pin_Buttons__0__SHIFT*2u)))

#define Pin_Buttons_1			(Pin_Buttons__1__PC)
#define Pin_Buttons_1_PS		(Pin_Buttons__1__PS)
#define Pin_Buttons_1_PC		(Pin_Buttons__1__PC)
#define Pin_Buttons_1_DR		(Pin_Buttons__1__DR)
#define Pin_Buttons_1_SHIFT	(Pin_Buttons__1__SHIFT)
#define Pin_Buttons_1_INTR	((uint16)((uint16)0x0003u << (Pin_Buttons__1__SHIFT*2u)))

#define Pin_Buttons_2			(Pin_Buttons__2__PC)
#define Pin_Buttons_2_PS		(Pin_Buttons__2__PS)
#define Pin_Buttons_2_PC		(Pin_Buttons__2__PC)
#define Pin_Buttons_2_DR		(Pin_Buttons__2__DR)
#define Pin_Buttons_2_SHIFT	(Pin_Buttons__2__SHIFT)
#define Pin_Buttons_2_INTR	((uint16)((uint16)0x0003u << (Pin_Buttons__2__SHIFT*2u)))

#define Pin_Buttons_INTR_ALL	 ((uint16)(Pin_Buttons_0_INTR| Pin_Buttons_1_INTR| Pin_Buttons_2_INTR))


#endif /* End Pins Pin_Buttons_ALIASES_H */


/* [] END OF FILE */
