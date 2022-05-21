#include <project.h>
#include <stdio.h>
#include "math.h"

#include "utilities.h"

char lcd_orientation[50] = {0};

static uint16 counter = 0;
static float N = 1000;
static float vec_sine[1000]; 
static float val_out;
static double freq = 2*M_PI;
static int harm = 1;


CY_ISR(ISR_Audio_Handler)
{
    val_out = 128 +128*vec_sine[counter];
    VDAC8_SetValue(val_out);
    counter = counter + harm;
    Timer_ReadStatusRegister();   
}




void Audio_Init()
{
    
    
    
    ISR_Audio_StartEx(ISR_Audio_Handler);
    Timer_Audio_Start();
    VDAC8_Start();
    
    for (int i = 0; i < N; i++){
        vec_sine[i] = sin((freq*i)/N);
    }
    
}


    
void MakeSound(float* roll, float* pitch)
{
    harm = (int)*roll + (int)*pitch;
}






void LCD_PrintOrientation(float* roll, float* pitch)
{   

    LCD_ClearDisplay();
    sprintf(lcd_orientation, "%d/%d", (int)*roll, (int)*pitch);
    LCD_PrintString(lcd_orientation);

}





void audi(){
        LED1_Write(1);
        CyDelay(125);
        LED2_Write(1);
        CyDelay(125);
        LED3_Write(1);
        CyDelay(125);
        LED4_Write(1);
        CyDelay(125);
        
        

        LED1_Write(0);
        CyDelay(125);
        LED2_Write(0);
        CyDelay(125);
        LED3_Write(0);
        CyDelay(125);
        LED4_Write(0);
        CyDelay(125);
}



void SetOnLEDs()
{
    
    LED1_Write(1);
    LED2_Write(1);
    LED3_Write(1);
    LED4_Write(1);

}


void SetOffLEDs()
{
    
    LED1_Write(0);
    LED2_Write(0);
    LED3_Write(0);
    LED4_Write(0);

}



/* [] END OF FILE */
