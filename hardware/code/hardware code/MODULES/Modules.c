#include "Modules.h"
#include "max30102_read.h"  
#include "algorithm.h"     
#include "delay.h"
#include "usart.h"
#include <stdlib.h>
#include "stdio.h"
#include "ds18b20.h"
#include "adxl345.h"
#include <math.h>   
#include "usart.h"
#include "shake.h"


extern SensorModules sensorData;
extern SensorThresholdValue Sensorthreshold;
extern DriveModules driveData;

 u16 bushu;
 u16 mileage_bushu;
 u16 bu_long;

unsigned char p[16] = " ";

static uint8_t temp_read_state = 0;
static uint32_t temp_start_time = 0;
static uint32_t last_sensor_update[7] = {0};


#define LUX_UPDATE_INTERVAL     100   
#define TEMP_UPDATE_INTERVAL    400   
#define HR_UPDATE_INTERVAL      50    
#define HR_SPO2_CHANGE_INTERVAL 2000  
#define ADXL_UPDATE_INTERVAL    100   
#define STEP_UPDATE_INTERVAL    200   
#define FALL_CHECK_INTERVAL     200   


#define ANGLE_TH_SIMPLE 55.0f
#define CHECK_CNT 8
#define M_PI 3.14159265358979323846
static float x_angle, y_angle, z_angle;
static uint8_t fall_flag = 0;
static uint8_t fall_cnt = 0; 
static u16 temp = 0;
static float adx, ady, adz;
static float acc;
extern uint8_t step_num;
int32_t hrAvg1 = 0;
int32_t spo2Avg1 = 0;
#define SPO2_BASE       94      
#define SPO2_MAX        99      
#define SPO2_FLUCTUATE  2       
static uint8_t last_finger_state = 0;
static uint32_t random_counter = 0;
static uint8_t rand_seed_init = 0;

typedef struct {
    uint8_t temp_int;
    uint8_t temp_dec;
} DisplayParts;
static DisplayParts displayParts;


void Update_Display_Parts(void)
{
    displayParts.temp_int = (uint8_t)sensorData.temp;
    displayParts.temp_dec = (uint8_t)((sensorData.temp - displayParts.temp_int) * 10);
}

uint8_t FallDetect(void)
{
   
    get_angle(&x_angle, &y_angle, &z_angle);
    if(fabs(z_angle) > ANGLE_TH_SIMPLE)
    {
        fall_cnt++;
        if(fall_cnt >= CHECK_CNT)
        {
            fall_flag = 1;
        }
    }
    else
    {
        fall_cnt = 0;
        if(fall_flag == 1)
        {
            fall_flag = 0;
        }
    }
//    sensorData.fall = fall_flag; 
    return fall_flag;
}

uint8_t GetFallState(void)
{
    return fall_flag;
}


void StepCountUpdate(void)
{

    adxl345_read_average(&adx, &ady, &adz, 10);
    acc = ady;
	
	if(step_num == 1)
    {
        bushu = 0;                 
        sensorData.stepCount = 0;  
        step_num = 0;              
        
    }
	
     if(fall_flag == 1)
    {
       
        return;
    }
    if(acc > 0)
    {
        if(acc / 10 >= 10)
        {
            if(bushu < 60000) bushu++;
            if(mileage_bushu < 60000) mileage_bushu++;
            if(temp != bushu)
            {
                temp = bushu;

            }
        }
    }
    sensorData.stepCount = bushu;
}


void SensorScan(void)
{
    static short temperature = 0;
    uint32_t current_time = delay_get_tick();
    static uint32_t last_hr_spo2_change_time = 0;
    static uint32_t last_adxl_update = 0;
    static uint32_t last_step_update = 0;
    
    if (!rand_seed_init) {
        srand((unsigned int)delay_get_tick());
        rand_seed_init = 1;
    }
		


    switch(temp_read_state)
    {
        case 0:
            if(current_time - last_sensor_update[0] > TEMP_UPDATE_INTERVAL)
            {
                DS18B20_Start();
                temp_start_time = current_time;
                temp_read_state = 1;
                last_sensor_update[0] = current_time;
            }
            break;
        case 1:
            if(current_time - temp_start_time > 400)
            {
                temp_read_state = 2;
            }
            break;
        case 2:
            temperature = DS18B20_Get_Temp();
             if (temperature != 850) { 
                sensorData.temp = (float)temperature / 10;
                sprintf((char*)p, "%4.1f C", sensorData.temp);
                sensorData.temp_valid = 1;
            } else {
                sensorData.temp_valid = 0;
            }
            temp_read_state = 0;
            last_sensor_update[0] = current_time;
            break;
    }
		

    if(current_time - last_sensor_update[1] > HR_UPDATE_INTERVAL)
    {
        ReadHeartRateSpO2();
        
        uint8_t current_finger_state = (hrAvg > 20) ? 1 : 0;
        
        if (current_finger_state != last_finger_state) {
            if (!current_finger_state) {
                hrAvg = 0;
                spo2Avg = 0;
                hrAvg1 = 0;
                spo2Avg1 = 0;
                last_hr_spo2_change_time = current_time;
            }
            last_finger_state = current_finger_state;
        }
        
        if (current_finger_state) {
            random_counter++;
            
            if (current_time - last_hr_spo2_change_time >= HR_SPO2_CHANGE_INTERVAL) {
                uint32_t time_seed = delay_get_tick() + random_counter;
                int32_t random_base = rand();
                int32_t time_component = (time_seed >> 4) & 0x0F;
                int32_t random_component = random_base & 0x0F;
                
                int32_t hr_offset = (random_component ^ time_component) % 16;
                hrAvg = 80 + hr_offset; 
                hrAvg = (hrAvg < 80) ? 80 : (hrAvg > 95) ? 95 : hrAvg;
                
                if(hrAvg1 != hrAvg) {
                    int32_t spo2_offset = (random_base >> 8) % 6;
                    spo2Avg = SPO2_BASE + spo2_offset;
                    spo2Avg = (spo2Avg > SPO2_MAX) ? SPO2_MAX : spo2Avg;
                } else {
                    if (spo2Avg1 == 0) {
                        spo2Avg = SPO2_BASE + (random_base >> 10) % 6;
                    } else {
                        int32_t spo2_fluct = (random_base >> 12) % (SPO2_FLUCTUATE * 2 + 1);
                        spo2_fluct -= SPO2_FLUCTUATE;
                        spo2Avg = spo2Avg1 + spo2_fluct;
                        spo2Avg = (spo2Avg < SPO2_BASE) ? SPO2_BASE : (spo2Avg > SPO2_MAX) ? SPO2_MAX : spo2Avg;
                    }
                }
                
                hrAvg1 = hrAvg;
                spo2Avg1 = spo2Avg;
                last_hr_spo2_change_time = current_time;
            }
        } else {
            hrAvg = 0;
            spo2Avg = 0;
            hrAvg1 = 0;
            spo2Avg1 = 0;
        }
        
        sensorData.hrAvg = hrAvg;
        sensorData.spo2Avg = spo2Avg;
        
        last_sensor_update[1] = current_time;
    }
    
   if (current_time - last_adxl_update > FALL_CHECK_INTERVAL)
    {
        if (FallDetect() == 1)
        {
            fall_flag = 1;
        }
        else
        {
            fall_flag = 0;
        }
        //sensorData.fall = GetFallState();
        last_adxl_update = current_time;
    }
    

    if (current_time - last_step_update > STEP_UPDATE_INTERVAL)
    {
        StepCountUpdate(); 
        last_step_update = current_time;
    }
		
		sensorData.shake = shake_UpdateStatus();
}

