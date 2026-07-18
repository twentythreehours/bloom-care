#include "delay.h"
#include "timer.h"
#include "adcx.h"
#include "led.h"
#include "string.h"


//extern u16 msHcCount;
void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 			
	
	
	TIM_TimeBaseStructure.TIM_Period = arr; 						ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 						
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 		
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 				
 
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);  
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); 						
	

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  				
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 		
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;  			
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;					
	NVIC_Init(&NVIC_InitStructure); 								

	TIM_Cmd(TIM4,DISABLE);    				 
}


void TIM4_IRQHandler(void)   	
{
   if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  
   {
       TIM_ClearITPendingBit(TIM4, TIM_IT_Update  ); 
      // msHcCount++;
   }
}


