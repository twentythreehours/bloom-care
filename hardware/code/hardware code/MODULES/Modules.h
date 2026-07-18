#ifndef	__MODULES_H_
#define __MODULES_H_

#include "stm32f10x.h"                  // Device header
 //#include "dht11.h"
#include "adcx.h"


typedef enum
{
    AUTO_MODE = 1,    
    MANUAL_MODE,      
    SETTINGS_MODE    
} MODE_PAGES;  


typedef struct
{
    int32_t hrAvg;     
    int32_t spo2Avg;   
    float temp;
		u16 stepCount;
    uint8_t temp_valid;   
	  uint8_t shake;
  	uint16_t bushu;
    uint16_t mileage_bushu;
	
} SensorModules;

typedef struct
{
	float tempValue;
	uint8_t tempmaxValue;
	uint8_t tempminValue;	
	uint16_t hrMin ;     
  uint16_t hrMax;   	
	uint8_t hrAvgValue;
  uint16_t spo2Min;    
  uint16_t spo2Max;    
	
}SensorThresholdValue;

typedef struct
{
	uint8_t LED_Flag;
	uint8_t BEEP_Flag;
	
}DriveModules;



extern SensorModules sensorData;		
extern SensorThresholdValue Sensorthreshold;	
extern DriveModules driveData;				
void SensorScan(void);
uint8_t FallDetect(void);
uint8_t GetFallState(void);
#endif
