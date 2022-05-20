
#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H


#define SERVO1_POT2PWM 4.6377 // 4800 / 1035
#define SERVO2_POT2PWM 1.5942 // 1650 / 1035



    
    
void MoveServosToStart();

void InitializeServos();
    



void MPU6050_MoveServo1(float* roll);
void MPU6050_MoveServo2(float* pitch);



void Joystick_Start();  


void Joystick_MoveServo1();
void Joystick_MoveServo2();



    
    

#endif 

/* [] END OF FILE */
