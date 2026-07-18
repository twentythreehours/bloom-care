#ifndef	__KEY_H
#define __KEY_H
#include "stm32f10x.h"                  								// Device header

/*****************异方辰电子工作室******************
												STM32
											
 * 文件			:	KEY按键例程（包含短按/长按/连按）.h文件
 * 版本	    :	V2.0
 * 日期	    :	2025.9.20
 * MCU	    :	STM32F103C8T6
 * 接口	    :	见代码
 * IP账号		:	异方辰电子（同BILIBILI|抖音|快手|小红书|CSDN|公众号|视频号等）
 * 作者			:	辰哥
 * 工作室		: 异方辰电子工作室
 * 讲解视频	:	https://www.bilibili.com/video/BV1JXU8BuEVJ/?share_source=copy_web&vd_source=097fdeaf6b6ecfed8a9ff7119c32faf2
 * 官方网站	:	www.yfcdz.cn
 * 授权IP	 	:	辰哥单片机设计、异方辰电子、YFC电子、异方辰系列 

**********************BEGIN***********************/	


/*按键定义处*/
#define KEY1_GPIO_PIN	GPIO_Pin_12
#define KEY2_GPIO_PIN	GPIO_Pin_13
#define KEY3_GPIO_PIN	GPIO_Pin_14
#define KEY4_GPIO_PIN	GPIO_Pin_15

#define KEY_PORT	GPIOB
 
#define KEY1	GPIO_ReadInputDataBit(GPIOB, KEY1_GPIO_PIN) // 读取按键0
#define KEY2	GPIO_ReadInputDataBit(GPIOB, KEY2_GPIO_PIN) // 读取按键1
#define KEY3	GPIO_ReadInputDataBit(GPIOB, KEY3_GPIO_PIN) // 读取按键2
#define KEY4	GPIO_ReadInputDataBit(GPIOB, KEY4_GPIO_PIN) // 读取按键2

/*按键阈值*/
#define KEY_DELAY_TIME							10										  //消抖延时			   												10ms
#define KEY_LONG_TIME								1000								    //长按-阈值		   												1000ms

#define KEY_Continue_TIME					  500								  //短按最长停留时长--超过进行连击阈值判断	1000ms		
#define KEY_Continue_Trigger_TIME		5											//连击阈值																10ms		

/*按键码*/
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
