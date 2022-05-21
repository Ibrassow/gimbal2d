#include "stdlib.h"
#include <stdio.h>

#include <project.h>
#include "motor_control.h"


#define THRESHOLD 0



int potentio_cmd = 0;
int servo_cmd_1 = 0;
int servo_cmd_2 = 0;


int servo_previous_cmd_1 = 0;
int servo_previous_cmd_2 = 0;



static uint8_t Servos_1_flag;
static uint8_t Servos_2_flag;


static unsigned int counter = 0;
static int counter_started = 0;
static float elapsed_time = 0;




void MoveServosToStart()
{
    PWM_WriteCompare1(3800);
    PWM_WriteCompare2(2025);
    
}


void InitializeServos()
{
    

    PWM_Start();
    counter_started = 1; 
    MoveServosToStart();
}







void Joystick_Start()
{
    
    ADC_Start();
    ADC_StartConvert();
    AMux_Start();
    
}



void SetMotorFlags()
{
    
    Servos_1_flag = 1;
    Servos_2_flag = 1;
    
    
}


char detect[50];


static int threshold_angle = 0;


// little servo
void MPU6050_MoveServo1(float* roll)
{
    
    
    //((abs(servo_cmd_1 - servo_previous_cmd_1) > THRESHOLD) && 
    //(abs((int)(*roll - previous_roll))
    if ((Servos_1_flag == 1) && (abs((int)*roll) > threshold_angle))
    {
        

        potentio_cmd = (int)((*roll + 90.0)*5.9);
        servo_cmd_1 = 3800 + ( potentio_cmd - 531.0)*(SERVO1_POT2PWM);
        
        if (servo_cmd_1 > 6000)
        {
         servo_cmd_1 = 6000;   
        }
        else if (servo_cmd_1 < 1200)
        {
            servo_cmd_1 = 1200;
        }
        PWM_WriteCompare1(servo_cmd_1);
        
        int servo_previous_cmd_1 = servo_cmd_1;
        Servos_1_flag = 0;
        
        
        
        //sprintf(detect, "ROLL :: %d  ---- SERVO 111 --> %d\n", (int)*roll, servo_cmd_1);
        //UART_PutString(detect); 
        

        
    }
    
    
    
            

        
        

}



// Big servo
void MPU6050_MoveServo2(float* pitch)
{

        
    
    //(abs(servo_cmd_2 - servo_previous_cmd_2) > THRESHOLD) && 
    if ((Servos_2_flag == 1) && (abs((int)*pitch) > threshold_angle))
    {
        
         /// 0.0375
        //servo_cmd_2 = (2025 - *pitch * 26.666);
         potentio_cmd = (int)((*pitch + 90.0f)*6.1222);
        servo_cmd_2 = 2025 + (potentio_cmd  - 551)*(SERVO2_POT2PWM);
        

        
        if (servo_cmd_2 > 2850)
        {
         servo_cmd_2 = 2850;   
        }
        else if (servo_cmd_2 < 1200)
        {
            servo_cmd_2 = 1200;
        }
        
        PWM_WriteCompare2(servo_cmd_2);
        
        
        int servo_previous_cmd_2 = servo_cmd_2;
        Servos_2_flag = 0;
    
        /*sprintf(detect, "SERVO 222 --> %d\n", servo_cmd_2);
        UART_PutString(detect); */
        
    }
    
    
    
    
}




void Joystick_MoveServo1()
{
        
        AMux_Select(0);
        potentio_cmd = ADC_Read16(); // de base à 551 (0 to 1035)
    
        servo_cmd_1 = 3800 + (potentio_cmd - 531)*(SERVO1_POT2PWM);
            
        if (servo_cmd_1 > 6000)
        {
         servo_cmd_1 = 6000;   
        }
        else if (servo_cmd_1 < 1200)
        {
            servo_cmd_1 = 1200;
        }
        
        PWM_WriteCompare1(servo_cmd_1); 
        
        /*sprintf(detect, "1 -- POT:: %d -- SERVO1 %d\n", cmd, servo_cmd_1);
        UART_PutString(detect);
        */ 
    
}


void Joystick_MoveServo2()
{
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
        
        PWM_WriteCompare2(servo_cmd_2);
        
        /*sprintf(detect, "2 -- POT:: %d -- SERVO2 %d\n", potentio_cmd, servo_cmd_2);
        UART_PutString(detect);
        */
    
}






/* [] END OF FILE */
