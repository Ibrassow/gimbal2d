#include <string.h>
#include <stdio.h>
#include <math.h>

#include "project.h"
#include "mpu6050.h"
#include "motor_control.h"
#include "utilities.h"
#include "keypad.h"



char detect[50];

uint8_t sw1;
uint8_t sw2;
uint8_t mode = 0;  
uint8_t just_switched = 0;




int main(void)
{   
    
    MPU6050_PreInit();
    
   
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();
    
    UART_PutString("Depart");     
    //Audio_Init();
    UART_PutString("Success");   

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
    
    
    // RE-CALIBRATION -----
    
    /*int32_t calib_array[6] = {0};
    
    int32_t ax_offs;
    int32_t ay_offs;
    int32_t az_offs;
    int32_t gx_offs;
    int32_t gy_offs;
    int32_t gz_offs;
    
    int32_t N = 20;

    for (int i = 0; i < N; i++)
    {
        
        MPU6050_Calibrate();
        
        GetValuesFromCalib(calib_array);
        
        ax_offs = ax_offs + calib_array[0];
        ay_offs = ay_offs + calib_array[1];
        az_offs = az_offs + calib_array[2];
        gx_offs = gx_offs + calib_array[3];
        gy_offs = gy_offs + calib_array[4];
        gz_offs = gz_offs + calib_array[5];
        
        CyDelay(1000);
        
    }

        ax_offs = round((float)ax_offs/(float)N);
        ay_offs = round((float)ay_offs/(float)N);
        az_offs = round((float)az_offs/(float)N);
        gx_offs = round((float)gx_offs/(float)N);
        gy_offs = round((float)gy_offs/(float)N);
        gz_offs = round((float)gz_offs/(float)N);
    
    
        char test[50];
        sprintf(test, "FINAL AX OFFSET :: %d \n", ax_offs);
        UART_PutString(test) ;
        
        sprintf(test, "FINAL AY OFFSET :: %d\n",  ay_offs);
        UART_PutString(test) ;
        
        sprintf(test, "FINAL AZ OFFSET :: %d\n",  az_offs);
        UART_PutString(test) ;
        
        sprintf(test, "FINAL GX OFFSET :: %d\n", gx_offs);
        UART_PutString(test) ;
        
        sprintf(test, "FINAL GY OFFSET :: %d\n", gy_offs);
        UART_PutString(test) ;
        
        sprintf(test, "FINAL GZ OFFSET :: %d\n", gz_offs);
        UART_PutString(test) ;

           CyDelay(100000);*/
    
    // RE-CALIBRATION ----- END
    

    
    for(;;)
    {
            
            sw1 = SW1_Read(); // Mode change
            sw2 = SW2_Read(); // Re-calibration
            
            if (sw2)
            {
               MoveServosToStart();
                CyDelay(500);
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
                        just_switched = 1;
                        break;
                }
            }

            
            switch(mode)
            {
                case 0:

                    ///////// JOYSTICK MODE /////////
                
                    MPU6050_GetData(&roll, &pitch);

                    // COMMAND SERVO 1 
                    
                    Joystick_MoveServo1();
                    
                    // COMMAND SERVO 2
                    
                    Joystick_MoveServo2();
                    
                    
                    
                    //MakeSound(&roll, &pitch);
                    
                    break;

                    
                case 1:
                    
                    ///////// MPU6050 MODE /////////
                    
                    if (just_switched)
                    {
                     MPU6050_Calibrate();
                     just_switched = 0;
                    }
                    
                    
                    
            
                    if (MPU6050_DataAvailable() == TRUE)
                    {
                        


                        MPU6050_GetData(&roll, &pitch);
                        
                        MPU6050_MoveServo1(&roll);
                        MPU6050_MoveServo2(&pitch);

                        ii++;
            
                        if (ii == 500){
                            MPU6050_PrintData();
                            
                            char orientation[50];
                            LCD_PrintOrientation(&roll, &pitch);
                            ii = 0;
                        }

                    }

                    

                    break;
                
            }
            

        
        
}

}






/* [] END OF FILE */
