#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include "stm32f10x.h"
#include "Modules.h"   // 为了能直接传 SensorModules 结构体

void Bluetooth_Init(u32 baud);
void Bluetooth_SendString(char *str);
void Bluetooth_SendSensorData(SensorModules *data);

#endif
