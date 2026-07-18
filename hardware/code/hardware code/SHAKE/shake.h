#ifndef __shake_H
#define	__shake_H
#include "stm32f10x.h"
#include "adcx.h"
#include "delay.h"
#include "math.h"


#define SHAKE_AO_THRESHOLD  4000 
#define shake_READ_TIMES	10  
extern uint8_t shake;           // 声明全局变量
#if MODE
void shake_UpdateStatus(void);  // AO模式下的状态更新函数
#endif
//模式选择	
//模拟AO:	1
//数字DO:	0
#define	MODE 	1

/***************根据自己需求更改****************/

#if MODE
#define		shake_AO_GPIO_CLK								RCC_APB2Periph_GPIOA
#define 	shake_AO_GPIO_PORT							GPIOA
#define 	shake_AO_GPIO_PIN								GPIO_Pin_0
#define   ADC_CHANNEL               		ADC_Channel_0// ADC 通道宏定义

#else
#define		shake_DO_GPIO_CLK								RCC_APB2Periph_GPIOA
#define 	shake_DO_GPIO_PORT							GPIOA
#define 	shake_DO_GPIO_PIN								GPIO_Pin_1			

#endif
/*********************END**********************/


void shake_Init(void);
uint16_t shake_GetData(void);
float shake_GetData_PPM(void);
float shake_GetPercent(void);
uint8_t shake_UpdateStatus(void);
#endif /* __ADC_H */

