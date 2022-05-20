#include <project.h>
#include <stdio.h>


#include "utilities.h"





char orientation[50] = {0};




uint8 led1_state = 0;
uint8 led2_state = 0;
uint8 led3_state = 0;
uint8 led4_state = 0;




void LCD_PrintOrientation(float* roll, float* pitch)
{   

    char orientation[30] = {0};
    
    LCD_ClearDisplay();

    sprintf(orientation, "%d/%d", (int)*roll, (int)*pitch);
    LCD_PrintString(orientation);

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




    
void MakeSound(float* roll, float* pitch)
{
    
    
    
    
    
}



    
    



        





/* [] END OF FILE */
