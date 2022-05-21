/*******************************************************************************
* File Name: Timer_Audio_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Audio.h"

static Timer_Audio_backupStruct Timer_Audio_backup;


/*******************************************************************************
* Function Name: Timer_Audio_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Audio_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Audio_SaveConfig(void) 
{
    #if (!Timer_Audio_UsingFixedFunction)
        Timer_Audio_backup.TimerUdb = Timer_Audio_ReadCounter();
        Timer_Audio_backup.InterruptMaskValue = Timer_Audio_STATUS_MASK;
        #if (Timer_Audio_UsingHWCaptureCounter)
            Timer_Audio_backup.TimerCaptureCounter = Timer_Audio_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Audio_UDB_CONTROL_REG_REMOVED)
            Timer_Audio_backup.TimerControlRegister = Timer_Audio_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Audio_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Audio_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Audio_RestoreConfig(void) 
{   
    #if (!Timer_Audio_UsingFixedFunction)

        Timer_Audio_WriteCounter(Timer_Audio_backup.TimerUdb);
        Timer_Audio_STATUS_MASK =Timer_Audio_backup.InterruptMaskValue;
        #if (Timer_Audio_UsingHWCaptureCounter)
            Timer_Audio_SetCaptureCount(Timer_Audio_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Audio_UDB_CONTROL_REG_REMOVED)
            Timer_Audio_WriteControlRegister(Timer_Audio_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Audio_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Audio_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Audio_Sleep(void) 
{
    #if(!Timer_Audio_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Audio_CTRL_ENABLE == (Timer_Audio_CONTROL & Timer_Audio_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Audio_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Audio_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Audio_Stop();
    Timer_Audio_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Audio_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Audio_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Audio_Wakeup(void) 
{
    Timer_Audio_RestoreConfig();
    #if(!Timer_Audio_UDB_CONTROL_REG_REMOVED)
        if(Timer_Audio_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Audio_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
