/*******************************************************************************
* File Name: LargeServo.h  
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

#if !defined(CY_PINS_LargeServo_H) /* Pins LargeServo_H */
#define CY_PINS_LargeServo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "LargeServo_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 LargeServo__PORT == 15 && ((LargeServo__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    LargeServo_Write(uint8 value);
void    LargeServo_SetDriveMode(uint8 mode);
uint8   LargeServo_ReadDataReg(void);
uint8   LargeServo_Read(void);
void    LargeServo_SetInterruptMode(uint16 position, uint16 mode);
uint8   LargeServo_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the LargeServo_SetDriveMode() function.
     *  @{
     */
        #define LargeServo_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define LargeServo_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define LargeServo_DM_RES_UP          PIN_DM_RES_UP
        #define LargeServo_DM_RES_DWN         PIN_DM_RES_DWN
        #define LargeServo_DM_OD_LO           PIN_DM_OD_LO
        #define LargeServo_DM_OD_HI           PIN_DM_OD_HI
        #define LargeServo_DM_STRONG          PIN_DM_STRONG
        #define LargeServo_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define LargeServo_MASK               LargeServo__MASK
#define LargeServo_SHIFT              LargeServo__SHIFT
#define LargeServo_WIDTH              1u

/* Interrupt constants */
#if defined(LargeServo__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LargeServo_SetInterruptMode() function.
     *  @{
     */
        #define LargeServo_INTR_NONE      (uint16)(0x0000u)
        #define LargeServo_INTR_RISING    (uint16)(0x0001u)
        #define LargeServo_INTR_FALLING   (uint16)(0x0002u)
        #define LargeServo_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define LargeServo_INTR_MASK      (0x01u) 
#endif /* (LargeServo__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LargeServo_PS                     (* (reg8 *) LargeServo__PS)
/* Data Register */
#define LargeServo_DR                     (* (reg8 *) LargeServo__DR)
/* Port Number */
#define LargeServo_PRT_NUM                (* (reg8 *) LargeServo__PRT) 
/* Connect to Analog Globals */                                                  
#define LargeServo_AG                     (* (reg8 *) LargeServo__AG)                       
/* Analog MUX bux enable */
#define LargeServo_AMUX                   (* (reg8 *) LargeServo__AMUX) 
/* Bidirectional Enable */                                                        
#define LargeServo_BIE                    (* (reg8 *) LargeServo__BIE)
/* Bit-mask for Aliased Register Access */
#define LargeServo_BIT_MASK               (* (reg8 *) LargeServo__BIT_MASK)
/* Bypass Enable */
#define LargeServo_BYP                    (* (reg8 *) LargeServo__BYP)
/* Port wide control signals */                                                   
#define LargeServo_CTL                    (* (reg8 *) LargeServo__CTL)
/* Drive Modes */
#define LargeServo_DM0                    (* (reg8 *) LargeServo__DM0) 
#define LargeServo_DM1                    (* (reg8 *) LargeServo__DM1)
#define LargeServo_DM2                    (* (reg8 *) LargeServo__DM2) 
/* Input Buffer Disable Override */
#define LargeServo_INP_DIS                (* (reg8 *) LargeServo__INP_DIS)
/* LCD Common or Segment Drive */
#define LargeServo_LCD_COM_SEG            (* (reg8 *) LargeServo__LCD_COM_SEG)
/* Enable Segment LCD */
#define LargeServo_LCD_EN                 (* (reg8 *) LargeServo__LCD_EN)
/* Slew Rate Control */
#define LargeServo_SLW                    (* (reg8 *) LargeServo__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define LargeServo_PRTDSI__CAPS_SEL       (* (reg8 *) LargeServo__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define LargeServo_PRTDSI__DBL_SYNC_IN    (* (reg8 *) LargeServo__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define LargeServo_PRTDSI__OE_SEL0        (* (reg8 *) LargeServo__PRTDSI__OE_SEL0) 
#define LargeServo_PRTDSI__OE_SEL1        (* (reg8 *) LargeServo__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define LargeServo_PRTDSI__OUT_SEL0       (* (reg8 *) LargeServo__PRTDSI__OUT_SEL0) 
#define LargeServo_PRTDSI__OUT_SEL1       (* (reg8 *) LargeServo__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define LargeServo_PRTDSI__SYNC_OUT       (* (reg8 *) LargeServo__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(LargeServo__SIO_CFG)
    #define LargeServo_SIO_HYST_EN        (* (reg8 *) LargeServo__SIO_HYST_EN)
    #define LargeServo_SIO_REG_HIFREQ     (* (reg8 *) LargeServo__SIO_REG_HIFREQ)
    #define LargeServo_SIO_CFG            (* (reg8 *) LargeServo__SIO_CFG)
    #define LargeServo_SIO_DIFF           (* (reg8 *) LargeServo__SIO_DIFF)
#endif /* (LargeServo__SIO_CFG) */

/* Interrupt Registers */
#if defined(LargeServo__INTSTAT)
    #define LargeServo_INTSTAT            (* (reg8 *) LargeServo__INTSTAT)
    #define LargeServo_SNAP               (* (reg8 *) LargeServo__SNAP)
    
	#define LargeServo_0_INTTYPE_REG 		(* (reg8 *) LargeServo__0__INTTYPE)
#endif /* (LargeServo__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_LargeServo_H */


/* [] END OF FILE */
