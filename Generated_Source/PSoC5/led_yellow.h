/*******************************************************************************
* File Name: led_yellow.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_led_yellow_H) /* Pins led_yellow_H */
#define CY_PINS_led_yellow_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "led_yellow_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 led_yellow__PORT == 15 && ((led_yellow__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    led_yellow_Write(uint8 value);
void    led_yellow_SetDriveMode(uint8 mode);
uint8   led_yellow_ReadDataReg(void);
uint8   led_yellow_Read(void);
void    led_yellow_SetInterruptMode(uint16 position, uint16 mode);
uint8   led_yellow_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the led_yellow_SetDriveMode() function.
     *  @{
     */
        #define led_yellow_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define led_yellow_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define led_yellow_DM_RES_UP          PIN_DM_RES_UP
        #define led_yellow_DM_RES_DWN         PIN_DM_RES_DWN
        #define led_yellow_DM_OD_LO           PIN_DM_OD_LO
        #define led_yellow_DM_OD_HI           PIN_DM_OD_HI
        #define led_yellow_DM_STRONG          PIN_DM_STRONG
        #define led_yellow_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define led_yellow_MASK               led_yellow__MASK
#define led_yellow_SHIFT              led_yellow__SHIFT
#define led_yellow_WIDTH              1u

/* Interrupt constants */
#if defined(led_yellow__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in led_yellow_SetInterruptMode() function.
     *  @{
     */
        #define led_yellow_INTR_NONE      (uint16)(0x0000u)
        #define led_yellow_INTR_RISING    (uint16)(0x0001u)
        #define led_yellow_INTR_FALLING   (uint16)(0x0002u)
        #define led_yellow_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define led_yellow_INTR_MASK      (0x01u) 
#endif /* (led_yellow__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define led_yellow_PS                     (* (reg8 *) led_yellow__PS)
/* Data Register */
#define led_yellow_DR                     (* (reg8 *) led_yellow__DR)
/* Port Number */
#define led_yellow_PRT_NUM                (* (reg8 *) led_yellow__PRT) 
/* Connect to Analog Globals */                                                  
#define led_yellow_AG                     (* (reg8 *) led_yellow__AG)                       
/* Analog MUX bux enable */
#define led_yellow_AMUX                   (* (reg8 *) led_yellow__AMUX) 
/* Bidirectional Enable */                                                        
#define led_yellow_BIE                    (* (reg8 *) led_yellow__BIE)
/* Bit-mask for Aliased Register Access */
#define led_yellow_BIT_MASK               (* (reg8 *) led_yellow__BIT_MASK)
/* Bypass Enable */
#define led_yellow_BYP                    (* (reg8 *) led_yellow__BYP)
/* Port wide control signals */                                                   
#define led_yellow_CTL                    (* (reg8 *) led_yellow__CTL)
/* Drive Modes */
#define led_yellow_DM0                    (* (reg8 *) led_yellow__DM0) 
#define led_yellow_DM1                    (* (reg8 *) led_yellow__DM1)
#define led_yellow_DM2                    (* (reg8 *) led_yellow__DM2) 
/* Input Buffer Disable Override */
#define led_yellow_INP_DIS                (* (reg8 *) led_yellow__INP_DIS)
/* LCD Common or Segment Drive */
#define led_yellow_LCD_COM_SEG            (* (reg8 *) led_yellow__LCD_COM_SEG)
/* Enable Segment LCD */
#define led_yellow_LCD_EN                 (* (reg8 *) led_yellow__LCD_EN)
/* Slew Rate Control */
#define led_yellow_SLW                    (* (reg8 *) led_yellow__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define led_yellow_PRTDSI__CAPS_SEL       (* (reg8 *) led_yellow__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define led_yellow_PRTDSI__DBL_SYNC_IN    (* (reg8 *) led_yellow__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define led_yellow_PRTDSI__OE_SEL0        (* (reg8 *) led_yellow__PRTDSI__OE_SEL0) 
#define led_yellow_PRTDSI__OE_SEL1        (* (reg8 *) led_yellow__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define led_yellow_PRTDSI__OUT_SEL0       (* (reg8 *) led_yellow__PRTDSI__OUT_SEL0) 
#define led_yellow_PRTDSI__OUT_SEL1       (* (reg8 *) led_yellow__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define led_yellow_PRTDSI__SYNC_OUT       (* (reg8 *) led_yellow__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(led_yellow__SIO_CFG)
    #define led_yellow_SIO_HYST_EN        (* (reg8 *) led_yellow__SIO_HYST_EN)
    #define led_yellow_SIO_REG_HIFREQ     (* (reg8 *) led_yellow__SIO_REG_HIFREQ)
    #define led_yellow_SIO_CFG            (* (reg8 *) led_yellow__SIO_CFG)
    #define led_yellow_SIO_DIFF           (* (reg8 *) led_yellow__SIO_DIFF)
#endif /* (led_yellow__SIO_CFG) */

/* Interrupt Registers */
#if defined(led_yellow__INTSTAT)
    #define led_yellow_INTSTAT            (* (reg8 *) led_yellow__INTSTAT)
    #define led_yellow_SNAP               (* (reg8 *) led_yellow__SNAP)
    
	#define led_yellow_0_INTTYPE_REG 		(* (reg8 *) led_yellow__0__INTTYPE)
#endif /* (led_yellow__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_led_yellow_H */


/* [] END OF FILE */
