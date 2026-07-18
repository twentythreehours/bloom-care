#ifndef	__MODULES_H_
#define __MODULES_H_

#include "stm32f10x.h"                  // Device header
 //#include "dht11.h"
#include "adcx.h"


typedef enum
{
    AUTO_MODE = 1,    // 自动模式
    MANUAL_MODE,      // 手动模式（值=2）
    SETTINGS_MODE     // 设置模式（值=3）
} MODE_PAGES;  // 枚举类型名，所有文件可直接使用


typedef struct
{
    int32_t hrAvg;      // 心率
    int32_t spo2Avg;    // 血氧 
    float temp;
		u16 stepCount;
    uint8_t temp_valid;   // 温度有效标志：0=无效（初始85℃），1=有效（真实温度）
	  uint8_t shake;
  	uint16_t bushu;
    uint16_t mileage_bushu;
	
} SensorModules;

typedef struct
{
	float tempValue;
	uint8_t tempmaxValue;
	uint8_t tempminValue;	
	uint16_t hrMin ;     // 心率下限
  uint16_t hrMax;   	 // 心率上限
	uint8_t hrAvgValue;
  uint16_t spo2Min;    // 血氧下限
  uint16_t spo2Max;    // 血氧上限
	
}SensorThresholdValue;

typedef struct
{
	uint8_t LED_Flag;
	uint8_t BEEP_Flag;
	
}DriveModules;
 	// 初始化驱动数据（全局变量）


extern SensorModules sensorData;			//声明传感器模块的结构体变量
extern SensorThresholdValue Sensorthreshold;	//声明传感器阈值结构体变量
extern DriveModules driveData;				//声明驱动器状态的结构体变量
void SensorScan(void);
uint8_t FallDetect(void);
uint8_t GetFallState(void);
#endif
