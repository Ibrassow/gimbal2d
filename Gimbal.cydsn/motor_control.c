#include <project.h>

#include "motor_control.h"



int potentio_cmd = 0;
int servo_cmd_1 = 0;
int servo_cmd_2 = 0;




void MoveServosToStart()
{
    PWM_WriteCompare1(3800);
    PWM_WriteCompare2(2025);
    
}


void InitializeServos()
{
    
    PWM_Start();
    MoveServosToStart();

    
}




void Joystick_Start()
{
    
    ADC_Start();
    ADC_StartConvert();
    AMux_Start();
    
}
    

void MPU6050_MoveServo1(float* roll)
{
        servo_cmd_1 = 3800 - *roll / 0.0375;
            
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
        UART_PutString(detect);*/ 
}




void MPU6050_MoveServo2(float* pitch)
{

        servo_cmd_2 = 2025 - *pitch / 0.0375;
        
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
        UART_PutString(detect);*/

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
