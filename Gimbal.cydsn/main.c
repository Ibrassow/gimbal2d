/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <string.h>
#include <stdio.h>

#include "project.h"
#include "mpu6050.h"
#include "motor_control.h"
#include "utilities.h"







char detect[50];

uint8_t sw1;
uint8_t sw2;
uint8_t mode = 0;  






int main(void)
{   
    
    
    MPU6050_PreInit();
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    
    UART_Start();
    
    InitializeServos();
    Joystick_Start();
    

    MPU6050_Init();
    MPU6050_Calibrate();
    
    
    float roll = 0;
    float pitch = 0;
    
    
    
    MPU6050_Start();


    
    // LCD Initialization 
    LCD_Start();
    LCD_PrintString("Yo mec !");
    CyDelay(1000);
    LCD_ClearDisplay();
    

    
    int ii = 0;
    

    
    for(;;)
    {
            
        
            
            
            sw1 = SW1_Read(); 
            sw2 = SW2_Read();
            
            
            if (sw2)
            {
               MoveServosToStart();
               MPU6050_Calibrate();
               mode = 1;
                
            }
            
            
            
            
            if (sw1)
            {
                switch(mode)
                {
                    case 0:
                        mode = 1;
                        SetOnLEDs();
                        break;

                    case 1:
                        mode = 0;
                        SetOffLEDs();
                        break;
                }
            }
            
            
            
            
            
            switch(mode)
            {
                case 0:
                    
                    ///////// JOYSTICK MODE /////////

                    // COMMAND SERVO 1 
                    
                    Joystick_MoveServo1();
                    
                    // COMMAND SERVO 2
                    
                    Joystick_MoveServo2();
                    
                    break;
                
                case 1:
                    
                    ///////// MPU6050 MODE /////////
            
                    if (MPU6050_DataAvailable() == TRUE)
                    {
                        

                        MPU6050_ReadData();

                        ii++;
            
                        if (ii == 500){
                            MPU6050_PrintData();
                            
                            char orientation[50];
                            sprintf(orientation, "%d -- %d \n", (int)roll, (int)pitch);
                            UART_PutString(orientation);
                        
                        
                            LCD_PrintOrientation(&roll, &pitch);
                            ii = 0;
                        }

                        
                    }
                   
                    MPU6050_MoveServo1(&roll);
                    MPU6050_MoveServo2(&pitch);

          
                    MPU6050_GetRoll(&roll);
                    MPU6050_GetPitch(&pitch);
                    
                    break;
                
            }
            

        
            
            

            
            
            
            
            
            /*
        
            ///////// JOYSTICK MODE /////////
            
            
            // COMMAND SERVO 1 
            
            AMux_Select(0);
            potentio_cmd = ADC_Read16();
            servo_cmd_1 = 3800 + (potentio_cmd - 531)*(SERVO1_POT2PWM);
            
            if (servo_cmd_1 > 6000)
            {
             servo_cmd_1 = 6000;   
            }
            else if (servo_cmd_1 < 1200)
            {
                servo_cmd_1 = 1200;
            }
            
            sprintf(detect, "1 -- POT:: %d -- SERVO1 %d\n", potentio_cmd, servo_cmd_1);
            UART_PutString(detect);
            
            PWM_WriteCompare1(servo_cmd_1);
        
        
            // COMMAND SERVO 2
        
            AMux_Select(1);
            potentio_cmd = ADC_Read16(); // de base à 551 (0 to 1035)
            servo_cmd_2 = 2025 + (potentio_cmd - 551)*(SERVO2_POT2PWM);
            
            if (servo_cmd_2 > 2850)
            {
             servo_cmd_2 = 2850;   
            }
            else if (servo_cmd_2 < 1200)
            {
                servo_cmd_2 = 1200;
            }
            
            sprintf(detect, "2 -- POT:: %d -- SERVO2 %d\n", potentio_cmd, servo_cmd_2);
            UART_PutString(detect);
            
            PWM_WriteCompare2(servo_cmd_2);

        
               */

            

            
}

}






/* [] END OF FILE */
