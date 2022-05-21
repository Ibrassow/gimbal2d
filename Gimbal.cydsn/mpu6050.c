#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include <project.h>
#include "mpu6050.h"
#include "motor_control.h"


static uint8_t i2c_buffer[22];

struct Calibration
{
    int32_t ax_offset;
    int32_t ay_offset;
    int32_t az_offset;
    int32_t gx_offset;
    int32_t gy_offset;
    int32_t gz_offset;
    //int16_t t_offset;
};

static struct Calibration calib;

static struct Data data;



static uint8_t MPU6050_flag;


static unsigned int counter = 0;
static int counter_started = 0;
static float elapsed_time = 0;


uint8_t MPU6050_is_calibrated = FALSE;



static uint16_t motor_counter = 0;


// Gyro max sample rate --> 8 kHz
// Accelerometer max sample rate --> 1 kHz

CY_ISR(ISR_1_Handler) // MPU6050_SAMPLE_PERIOD_S
{
    
    if (counter_started == 1)
    {
        counter++;
        motor_counter++;
        
        if (motor_counter == 20)
        {
            SetMotorFlags();
            motor_counter = 0;
        }
        
    }
    
    MPU6050_flag = TRUE;
    Timer_ReadStatusRegister();
    

    
}


static void GetElapsedTimeS(float *elapsed_t)
{
    *elapsed_t = (float)counter / 1000.0;  
}



void ResetCounter()
{
    counter = 0;
}



void MPU6050_PreInit()
{
    ISR_StartEx(ISR_1_Handler);
    Timer_Start();
    
    UART_PutString("Timer and ISR Started\n");
    
}



void MPU6050_Init()
{

    
    
    UART_PutString("Entered MPU6050 Initialization... \n");

    I2C_MPU6050_Start();
    UART_PutString("I2C Started\n");
    UART_PutString("Beginnig Initialization of MPU... \n");
    UART_PutString("Writing to Power Management Register... \n");
    
    
    uint8 pwmt_cmd[2];
    pwmt_cmd[0]  = MPU6050_PWM_1; // writing to the register 107 - Power Management
    pwmt_cmd[1] = 0x00;
    I2C_MPU6050_MasterWriteBuf(MPU6050_ADDRESS, pwmt_cmd, 2, I2C_MPU6050_MODE_COMPLETE_XFER); // writing to the register 107 - Power Management
    

    
    while((I2C_MPU6050_MasterStatus() & I2C_MPU6050_MSTAT_WR_CMPLT) == 0){}
        
    UART_PutChar('R');
    UART_PutChar(I2C_MPU6050_MasterClearStatus());
    UART_PutChar(I2C_MPU6050_MasterStatus());
    

    
    // Accelerometer configuration - default +/- 2g
    UART_PutString("Configuration: Writing to accelerometer register... \n");
    uint8_t accel_config[2];
    accel_config[0] = 0x1C; // accelerometer register
    accel_config[1] = 0x00; // set full Scale Range to +/- 2g
    I2C_MPU6050_MasterWriteBuf(MPU6050_ADDRESS, accel_config, 2, I2C_MPU6050_MODE_COMPLETE_XFER);
    UART_PutString("\nR");
    UART_PutChar(I2C_MPU6050_MasterClearStatus());
    UART_PutChar(I2C_MPU6050_MasterStatus());
    UART_PutString("Done.\n");
    
    // Gyroscope configuration - default +/- 250 deg/s
    UART_PutString("Configuration: Writing to gyroscope register... \n");
    uint8_t gyro_config[2];
    gyro_config[0] =  0x1B; // gyroscope register
    gyro_config[1] =  0x00; // set full Scale Range to 250deg/s
    I2C_MPU6050_MasterWriteBuf(MPU6050_ADDRESS, gyro_config, 2, I2C_MPU6050_MODE_COMPLETE_XFER);
    UART_PutString("\nR");
    UART_PutChar(I2C_MPU6050_MasterClearStatus());
    UART_PutChar(I2C_MPU6050_MasterStatus());
    UART_PutString("Done.\n");
    


    UART_PutString("MPU6050 Initialized. \n");
}






static void MPU6050_GetRawData()
{
    
    uint8_t cmd[1];
    cmd[0] = MPU6050_RA_ACCEL_XOUT_H;
    I2C_MPU6050_MasterWriteBuf(MPU6050_ADDRESS, cmd, 1, I2C_MPU6050_MODE_COMPLETE_XFER); // Sending cmd to read
    while ((I2C_MPU6050_MasterStatus() & I2C_MPU6050_MSTAT_WR_CMPLT)==0){}
    I2C_MPU6050_MasterGetWriteBufSize();
    I2C_MPU6050_MasterReadBuf(MPU6050_ADDRESS, i2c_buffer, 14, I2C_MPU6050_MODE_COMPLETE_XFER); // Reading raw data values from the register


    data.raw_ax = (((int16_t)i2c_buffer[0]) << 8) | i2c_buffer[1];
    data.raw_ay = (((int16_t)i2c_buffer[2]) << 8) | i2c_buffer[3];
    data.raw_az = (((int16_t)i2c_buffer[4]) << 8) | i2c_buffer[5];
    data.raw_t  = (((int16_t)i2c_buffer[6]) << 8) | i2c_buffer[7];
    data.raw_gx = (((int16_t)i2c_buffer[8]) << 8) | i2c_buffer[9];
    data.raw_gy = (((int16_t)i2c_buffer[10]) << 8) | i2c_buffer[11];
    data.raw_gz = (((int16_t)i2c_buffer[12]) << 8) | i2c_buffer[13];
    
}


void MPU6050_Calibrate(){
    
    data.raw_ax = 0;
    data.raw_ay = 0;
    data.raw_az = 0;
    data.raw_gx = 0;
    data.raw_gy = 0;
    data.raw_gz = 0;
    
    calib.ax_offset = 0;
    calib.ay_offset = 0;
    calib.az_offset = 0;
    calib.gx_offset = 0;
    calib.gy_offset = 0;
    calib.gz_offset = 0;
    
    data.ax = 0;
    data.ay = 0;
    data.az = 0;
    data.gx = 0;
    data.gy = 0;
    data.gz = 0;
    data.gx_angle = 0;
    data.gy_angle = 0;
    data.gz_angle = 0;
    

    /*int32_t n_calib = 2000;
    
    for (int32_t i = 0; i < n_calib; i++) {
        
        MPU6050_GetRawData();
        
        calib.ax_offset += data.raw_ax; 
        calib.ay_offset += data.raw_ay; 
        calib.az_offset += data.raw_az; 
        calib.gx_offset += data.raw_gx; 
        calib.gy_offset += data.raw_gy;
        calib.gz_offset += data.raw_gz;
        CyDelay(1);

    }
    

    calib.ax_offset /= n_calib; 
    calib.ay_offset /= n_calib; 
    calib.az_offset /= n_calib; 
    calib.gx_offset /= n_calib; 
    calib.gy_offset /= n_calib; 
    calib.gz_offset /= n_calib; */
    
    /*calib.ax_offset -= 10939; 
    calib.ay_offset += 9367; 
    calib.az_offset -= 32766; 
    calib.gx_offset += 440; 
    calib.gy_offset += 333; 
    calib.gz_offset += 956;*/
    
    
     calib.ax_offset -= 11007; 
    calib.ay_offset += 10018; 
    calib.az_offset -= 32746; 
    calib.gx_offset += 433; 
    calib.gy_offset += 357; 
    calib.gz_offset += 1642;

    
    /*char test[50];
    sprintf(test, "AX OFFSET :: %d \n", calib.ax_offset);
    UART_PutString(test) ;
    
    sprintf(test, "AY OFFSET :: %d\n", calib.ay_offset);
    UART_PutString(test) ;
    
    sprintf(test, "AZ OFFSET :: %d\n", calib.az_offset);
    UART_PutString(test) ;
    
    sprintf(test, "GX OFFSET :: %d\n", calib.gx_offset);
    UART_PutString(test) ;
    
    sprintf(test, "GY OFFSET :: %d\n", calib.gy_offset);
    UART_PutString(test) ;
    
    sprintf(test, "GZ OFFSET :: %d\n", calib.gz_offset);
    UART_PutString(test) ;*/
    
    

    MPU6050_is_calibrated = TRUE;
    UART_PutString("CALIBRATION DONE!\n");

}




void GetValuesFromCalib(int32_t *calib_array)
{
    calib_array[0] = calib.ax_offset;
    calib_array[1] = calib.ay_offset;
    calib_array[2] = calib.az_offset;
    calib_array[3] = calib.gx_offset;
    calib_array[4] = calib.gy_offset;
    calib_array[5] = calib.gz_offset;

}







void MPU6050_Start()
{
    counter_started = 1; 
}



uint8_t MPU6050_DataAvailable()
{
    return MPU6050_flag;
}



float alpha = 0.75;



void MPU6050_ReadData()
{

    MPU6050_flag = FALSE;
    MPU6050_GetRawData();
    
    // Process everything now
    data.raw_ax -= calib.ax_offset;
    data.raw_ay -= calib.ay_offset;
    data.raw_az -= calib.az_offset;
    data.raw_gx -= calib.gx_offset;
    data.raw_gy -= calib.gy_offset;
    //data->raw_gz -= calib.gz_offset;
   
    
    data.ax = ((float)data.raw_ax) / 16384; // X-axis value
    data.ay = ((float)data.raw_ay) / 16384; // Y-axis value
    data.az = ((float)data.raw_az) / 16384; // Z-axis value
    
    data.gx = ((float)data.raw_gx) / 131;
    data.gy = ((float)data.raw_gy) / 131;
    //data->gz = ((float)data.raw_gz) / 131;
    

    // Calculating Roll and Pitch from the accelerometers
    data.ax = (atan2(data.ay, data.az) * RAD_TO_DEG) ; //+ 0.28
    data.ay = (atan2(-data.ax, sqrt(pow(data.ay, 2) + pow(data.az, 2))) * RAD_TO_DEG) ; 
    
    // Getting time elapsed
    GetElapsedTimeS(&elapsed_time);
    ResetCounter();


    // Getting gyro angles - Integration
    data.gx_angle = data.gx_angle + data.gx * elapsed_time; // deg/s * s = deg
    data.gy_angle = data.gy_angle + data.gy * elapsed_time;
    //data->gz_angle = data->gz_angle + data->gz * elapsed_time;
    
    // Complementary filter
    data.roll = data.gx_angle * 0.98 + data.ax * 0.02;   
    data.pitch = data.gy_angle * 0.98 + data.ay * 0.02;        
    

    
}



void MPU6050_GetData(float* roll, float* pitch)
{
     


    
    
    MPU6050_ReadData();
    
    
    
    *roll = data.roll;
    *pitch = data.pitch;
    
}


void MPU6050_PrintRawData()
{
    // Prints //
    
    char buff[10];
    
    UART_PutString("Ax:: ");
    itoa(data.raw_ax, buff, 10);
    UART_PutString(buff);
    UART_PutChar('\n');
    memset(buff, 0, 10);  
    
    UART_PutString("Ay:: ");
    itoa(data.raw_ay, buff, 10);
    UART_PutString(buff);
    UART_PutChar('\n');
    memset(buff, 0, 10); 
    
    UART_PutString("Az:: ");
    itoa(data.raw_az, buff, 10);
    UART_PutString(buff);
    UART_PutChar('\n');
    memset(buff, 0, 10); 
    
    UART_PutString("Gx:: ");
    itoa(data.raw_gx, buff, 10);
    UART_PutString(buff);
    UART_PutChar('\n');
    memset(buff, 0, 10); 
    
    UART_PutString("Gy:: ");
    itoa(data.raw_gy, buff, 10);
    UART_PutString(buff);
    UART_PutChar('\n');
    memset(buff, 0, 10); 
    
    UART_PutString("Gz:: ");
    itoa(data.raw_gz, buff, 10);
    UART_PutString(buff);
    UART_PutChar('\n');
    memset(buff, 0, 10); 
    
    UART_PutString("T:: ");
    itoa(data.raw_t, buff, 10);
    UART_PutString(buff);
    UART_PutChar('\n');
    memset(buff, 0, 10); 
    

    UART_PutString("CALIB::Gx:: ");
    itoa(calib.gx_offset, buff, 10);
    UART_PutString(buff);
    UART_PutChar('\n');
    memset(buff, 0, 10); 
    
}




char str[128];

void MPU6050_PrintData()
{
    // Prints //
    //UART_PutString("::::::::DATA::::::::\n");
    
    /*sprintf(str, "Ax:: %d.%02d  ", (int)data->ax, ((uint)(data->ax * 100.0 + 0.5))%100);
    UART_PutString(str) ;

    sprintf(str, "Ay:: %d.%02d  ", (int)data->ay, ((uint)(data->ay * 100.0 + 0.5))%100);
    UART_PutString(str) ;
    
    sprintf(str, "Az:: %d.%02d  ", (int)data->az, ((uint)(data->az * 100.0 + 0.5))%100);
    UART_PutString(str) ;
    
    UART_PutChar('\n');
    
    sprintf(str, "Gx:: %d.%02d  ", (int)data->gx, ((uint)(data->gx * 100.0 + 0.5))%100);
    UART_PutString(str) ;
    
    sprintf(str, "Gy:: %d.%02d  ", (int)data->gy, ((uint)(data->gy * 100.0 + 0.5))%100);
    UART_PutString(str) ;
    
    sprintf(str, "Gz:: %d.%02d  ", (int)data->gz, ((uint)(data->gz * 100.0 + 0.5))%100);
    UART_PutString(str) ;
    
    UART_PutChar('\n');
    
    sprintf(str, "Gx:: %d.%02d  (angle)", (int)data->gx_angle, ((uint)(data->gx * 100.0 + 0.5))%100);
    UART_PutString(str) ;
    
    sprintf(str, "Gy:: %d.%02d  (angle)", (int)data->gy_angle, ((uint)(data->gy * 100.0 + 0.5))%100);
    UART_PutString(str) ;
    
    sprintf(str, "Gz:: %d.%02d  (angle)", (int)data->gz_angle, ((uint)(data->gz * 100.0 + 0.5))%100);
    UART_PutString(str) ;
    
    UART_PutChar('\n');*/
 
    sprintf(str, "ROLL:: %d.%02d  (angle) ", (int)data.roll, ((uint)(data.roll * 100.0 + 0.5))%100);
    UART_PutString(str) ;
    
    sprintf(str, "PITCH:: %d.%02d  (angle) ", (int)data.pitch, ((uint)(data.pitch * 100.0 + 0.5))%100);
    UART_PutString(str) ;
    
    /*sprintf(str, "YAW:: %d.%02d  (angle) ", (int)data->yaw, ((uint)(data->yaw * 100.0 + 0.5))%100);
    UART_PutString(str) ;*/
    
    UART_PutChar('\n');

}




    
    
    
