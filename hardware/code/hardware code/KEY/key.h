#ifndef	__KEY_H
#define __KEY_H
#include "stm32f10x.h"                  								// Device header



#define KEY1_GPIO_PIN	GPIO_Pin_12
#define KEY2_GPIO_PIN	GPIO_Pin_13
#define KEY3_GPIO_PIN	GPIO_Pin_14
#define KEY4_GPIO_PIN	GPIO_Pin_15

#define KEY_PORT	GPIOB
 
#define KEY1	GPIO_ReadInputDataBit(GPIOB, KEY1_GPIO_PIN) 
#define KEY2	GPIO_ReadInputDataBit(GPIOB, KEY2_GPIO_PIN) 
#define KEY3	GPIO_ReadInputDataBit(GPIOB, KEY3_GPIO_PIN) 
#define KEY4	GPIO_ReadInputDataBit(GPIOB, KEY4_GPIO_PIN) 


#define KEY_DELAY_TIME							10										 
#define KEY_LONG_TIME								1000								  

#define KEY_Continue_TIME					  500								 


#define KEY1_Short								1										    		
#define KEY1_Long								  11									    	

#define KEY2_Short								2										    		
#define KEY2_Long								  2		

#define KEY3_Short								3										    		
#define KEY3_Lianji								3

#define KEY4_Short								4										    		
#define KEY4_Lianji								4

extern u8 KeyNum;

void Key_Init(void);
void Key_scan(void);

#endif
