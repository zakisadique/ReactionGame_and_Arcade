/*******************************************************************************
* File Name: led_red.h  
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

#if !defined(CY_PINS_led_red_H) /* Pins led_red_H */
#define CY_PINS_led_red_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "led_red_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 led_red__PORT == 15 && ((led_red__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    led_red_Write(uint8 value);
void    led_red_SetDriveMode(uint8 mode);
uint8   led_red_ReadDataReg(void);
uint8   led_red_Read(void);
void    led_red_SetInterruptMode(uint16 position, uint16 mode);
uint8   led_red_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the led_red_SetDriveMode() function.
     *  @{
     */
        #define led_red_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define led_red_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define led_red_DM_RES_UP          PIN_DM_RES_UP
        #define led_red_DM_RES_DWN         PIN_DM_RES_DWN
        #define led_red_DM_OD_LO           PIN_DM_OD_LO
        #define led_red_DM_OD_HI           PIN_DM_OD_HI
        #define led_red_DM_STRONG          PIN_DM_STRONG
        #define led_red_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define led_red_MASK               led_red__MASK
#define led_red_SHIFT              led_red__SHIFT
#define led_red_WIDTH              1u

/* Interrupt constants */
#if defined(led_red__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in led_red_SetInterruptMode() function.
     *  @{
     */
        #define led_red_INTR_NONE      (uint16)(0x0000u)
        #define led_red_INTR_RISING    (uint16)(0x0001u)
        #define led_red_INTR_FALLING   (uint16)(0x0002u)
        #define led_red_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define led_red_INTR_MASK      (0x01u) 
#endif /* (led_red__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define led_red_PS                     (* (reg8 *) led_red__PS)
/* Data Register */
#define led_red_DR                     (* (reg8 *) led_red__DR)
/* Port Number */
#define led_red_PRT_NUM                (* (reg8 *) led_red__PRT) 
/* Connect to Analog Globals */                                                  
#define led_red_AG                     (* (reg8 *) led_red__AG)                       
/* Analog MUX bux enable */
#define led_red_AMUX                   (* (reg8 *) led_red__AMUX) 
/* Bidirectional Enable */                                                        
#define led_red_BIE                    (* (reg8 *) led_red__BIE)
/* Bit-mask for Aliased Register Access */
#define led_red_BIT_MASK               (* (reg8 *) led_red__BIT_MASK)
/* Bypass Enable */
#define led_red_BYP                    (* (reg8 *) led_red__BYP)
/* Port wide control signals */                                                   
#define led_red_CTL                    (* (reg8 *) led_red__CTL)
/* Drive Modes */
#define led_red_DM0                    (* (reg8 *) led_red__DM0) 
#define led_red_DM1                    (* (reg8 *) led_red__DM1)
#define led_red_DM2                    (* (reg8 *) led_red__DM2) 
/* Input Buffer Disable Override */
#define led_red_INP_DIS                (* (reg8 *) led_red__INP_DIS)
/* LCD Common or Segment Drive */
#define led_red_LCD_COM_SEG            (* (reg8 *) led_red__LCD_COM_SEG)
/* Enable Segment LCD */
#define led_red_LCD_EN                 (* (reg8 *) led_red__LCD_EN)
/* Slew Rate Control */
#define led_red_SLW                    (* (reg8 *) led_red__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define led_red_PRTDSI__CAPS_SEL       (* (reg8 *) led_red__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define led_red_PRTDSI__DBL_SYNC_IN    (* (reg8 *) led_red__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define led_red_PRTDSI__OE_SEL0        (* (reg8 *) led_red__PRTDSI__OE_SEL0) 
#define led_red_PRTDSI__OE_SEL1        (* (reg8 *) led_red__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define led_red_PRTDSI__OUT_SEL0       (* (reg8 *) led_red__PRTDSI__OUT_SEL0) 
#define led_red_PRTDSI__OUT_SEL1       (* (reg8 *) led_red__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define led_red_PRTDSI__SYNC_OUT       (* (reg8 *) led_red__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(led_red__SIO_CFG)
    #define led_red_SIO_HYST_EN        (* (reg8 *) led_red__SIO_HYST_EN)
    #define led_red_SIO_REG_HIFREQ     (* (reg8 *) led_red__SIO_REG_HIFREQ)
    #define led_red_SIO_CFG            (* (reg8 *) led_red__SIO_CFG)
    #define led_red_SIO_DIFF           (* (reg8 *) led_red__SIO_DIFF)
#endif /* (led_red__SIO_CFG) */

/* Interrupt Registers */
#if defined(led_red__INTSTAT)
    #define led_red_INTSTAT            (* (reg8 *) led_red__INTSTAT)
    #define led_red_SNAP               (* (reg8 *) led_red__SNAP)
    
	#define led_red_0_INTTYPE_REG 		(* (reg8 *) led_red__0__INTTYPE)
#endif /* (led_red__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_led_red_H */


/* [] END OF FILE */
