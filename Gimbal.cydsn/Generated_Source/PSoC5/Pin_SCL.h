/*******************************************************************************
* File Name: Pin_SCL.h  
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

#if !defined(CY_PINS_Pin_SCL_H) /* Pins Pin_SCL_H */
#define CY_PINS_Pin_SCL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin_SCL_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin_SCL__PORT == 15 && ((Pin_SCL__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Pin_SCL_Write(uint8 value);
void    Pin_SCL_SetDriveMode(uint8 mode);
uint8   Pin_SCL_ReadDataReg(void);
uint8   Pin_SCL_Read(void);
void    Pin_SCL_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pin_SCL_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Pin_SCL_SetDriveMode() function.
     *  @{
     */
        #define Pin_SCL_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Pin_SCL_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Pin_SCL_DM_RES_UP          PIN_DM_RES_UP
        #define Pin_SCL_DM_RES_DWN         PIN_DM_RES_DWN
        #define Pin_SCL_DM_OD_LO           PIN_DM_OD_LO
        #define Pin_SCL_DM_OD_HI           PIN_DM_OD_HI
        #define Pin_SCL_DM_STRONG          PIN_DM_STRONG
        #define Pin_SCL_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Pin_SCL_MASK               Pin_SCL__MASK
#define Pin_SCL_SHIFT              Pin_SCL__SHIFT
#define Pin_SCL_WIDTH              1u

/* Interrupt constants */
#if defined(Pin_SCL__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pin_SCL_SetInterruptMode() function.
     *  @{
     */
        #define Pin_SCL_INTR_NONE      (uint16)(0x0000u)
        #define Pin_SCL_INTR_RISING    (uint16)(0x0001u)
        #define Pin_SCL_INTR_FALLING   (uint16)(0x0002u)
        #define Pin_SCL_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Pin_SCL_INTR_MASK      (0x01u) 
#endif /* (Pin_SCL__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin_SCL_PS                     (* (reg8 *) Pin_SCL__PS)
/* Data Register */
#define Pin_SCL_DR                     (* (reg8 *) Pin_SCL__DR)
/* Port Number */
#define Pin_SCL_PRT_NUM                (* (reg8 *) Pin_SCL__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin_SCL_AG                     (* (reg8 *) Pin_SCL__AG)                       
/* Analog MUX bux enable */
#define Pin_SCL_AMUX                   (* (reg8 *) Pin_SCL__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin_SCL_BIE                    (* (reg8 *) Pin_SCL__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin_SCL_BIT_MASK               (* (reg8 *) Pin_SCL__BIT_MASK)
/* Bypass Enable */
#define Pin_SCL_BYP                    (* (reg8 *) Pin_SCL__BYP)
/* Port wide control signals */                                                   
#define Pin_SCL_CTL                    (* (reg8 *) Pin_SCL__CTL)
/* Drive Modes */
#define Pin_SCL_DM0                    (* (reg8 *) Pin_SCL__DM0) 
#define Pin_SCL_DM1                    (* (reg8 *) Pin_SCL__DM1)
#define Pin_SCL_DM2                    (* (reg8 *) Pin_SCL__DM2) 
/* Input Buffer Disable Override */
#define Pin_SCL_INP_DIS                (* (reg8 *) Pin_SCL__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin_SCL_LCD_COM_SEG            (* (reg8 *) Pin_SCL__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin_SCL_LCD_EN                 (* (reg8 *) Pin_SCL__LCD_EN)
/* Slew Rate Control */
#define Pin_SCL_SLW                    (* (reg8 *) Pin_SCL__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin_SCL_PRTDSI__CAPS_SEL       (* (reg8 *) Pin_SCL__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin_SCL_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin_SCL__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin_SCL_PRTDSI__OE_SEL0        (* (reg8 *) Pin_SCL__PRTDSI__OE_SEL0) 
#define Pin_SCL_PRTDSI__OE_SEL1        (* (reg8 *) Pin_SCL__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin_SCL_PRTDSI__OUT_SEL0       (* (reg8 *) Pin_SCL__PRTDSI__OUT_SEL0) 
#define Pin_SCL_PRTDSI__OUT_SEL1       (* (reg8 *) Pin_SCL__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin_SCL_PRTDSI__SYNC_OUT       (* (reg8 *) Pin_SCL__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Pin_SCL__SIO_CFG)
    #define Pin_SCL_SIO_HYST_EN        (* (reg8 *) Pin_SCL__SIO_HYST_EN)
    #define Pin_SCL_SIO_REG_HIFREQ     (* (reg8 *) Pin_SCL__SIO_REG_HIFREQ)
    #define Pin_SCL_SIO_CFG            (* (reg8 *) Pin_SCL__SIO_CFG)
    #define Pin_SCL_SIO_DIFF           (* (reg8 *) Pin_SCL__SIO_DIFF)
#endif /* (Pin_SCL__SIO_CFG) */

/* Interrupt Registers */
#if defined(Pin_SCL__INTSTAT)
    #define Pin_SCL_INTSTAT            (* (reg8 *) Pin_SCL__INTSTAT)
    #define Pin_SCL_SNAP               (* (reg8 *) Pin_SCL__SNAP)
    
	#define Pin_SCL_0_INTTYPE_REG 		(* (reg8 *) Pin_SCL__0__INTTYPE)
#endif /* (Pin_SCL__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin_SCL_H */


/* [] END OF FILE */
