#ifndef MPU6050_H
#define MPU6050_H
    
#include "stdint.h"
    
#define MPU6050_ADDRESS_AD0_LOW     0x68 // address pin low (GND)
#define MPU6050_ADDRESS_AD0_HIGH    0x69 // address pin high (VCC)     
#define MPU6050_ADDRESS MPU6050_ADDRESS_AD0_LOW
    
#define MPU6050_RA_ACCEL_XOUT_H     0x3B // this
#define MPU6050_RA_ACCEL_XOUT_L     0x3C
#define MPU6050_RA_ACCEL_YOUT_H     0x3D
#define MPU6050_RA_ACCEL_YOUT_L     0x3E
#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
#define MPU6050_RA_ACCEL_ZOUT_L     0x40
    
#define MPU6050_RA_TEMP_OUT_H       0x41
#define MPU6050_RA_TEMP_OUT_L       0x42
    
#define MPU6050_RA_GYRO_XOUT_H      0x43 //this  
#define MPU6050_RA_GYRO_XOUT_L      0x44
#define MPU6050_RA_GYRO_YOUT_H      0x45
#define MPU6050_RA_GYRO_YOUT_L      0x46
#define MPU6050_RA_GYRO_ZOUT_H      0x47
#define MPU6050_RA_GYRO_ZOUT_L      0x48

#define MPU6050_NAK 0
#define MPU6050_ACK 11 //just non-zero

#define MPU6050_SAMPLE_PERIOD_S 0.001 // to change when changing the top design    
#define MPU6050_PWM_1 0x6B
    
#define TRUE 1
#define FALSE 0

#define RAD_TO_DEG 57.295779513
    
    
    


    
struct Data {
    int16_t raw_ax;
    int16_t raw_ay;
    int16_t raw_az;
    int16_t raw_gx;
    int16_t raw_gy;
    int16_t raw_gz;
    int16_t raw_t;
    uint8_t* raw_buffer;
    
    float ax;
    float ay;
    float az;
    float gx;
    float gy;
    float gz;
    float t;
    
    // gyro angles
    float gx_angle; 
    float gy_angle;
    float gz_angle;
    
    // Angle
    float roll;
    float pitch;
    float yaw;
    
    
};




// To put before CyGlobalIntEnable() 
// Starts the Timer and ISR
void MPU6050_PreInit();


void MPU6050_Init();

void MPU6050_Start();



uint8_t MPU6050_DataAvailable();

void MPU6050_Calibrate();
void GetValuesFromCalib(int32_t *calib_array);

void MPU6050_ReadData();


void MPU6050_PrintRawData();
void MPU6050_PrintData();


void MPU6050_GetData(float* roll, float* pitch); 

    
#endif 
