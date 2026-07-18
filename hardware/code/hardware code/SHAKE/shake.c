#include "shake.h"

uint8_t shake = 0;

void shake_Init(void)
{
	#if MODE
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd (shake_AO_GPIO_CLK, ENABLE );	
		GPIO_InitStructure.GPIO_Pin = shake_AO_GPIO_PIN;					
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
		
		GPIO_Init(shake_AO_GPIO_PORT, &GPIO_InitStructure);				

		ADCx_Init();
	}
	#else
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		
		RCC_APB2PeriphClockCmd (shake_DO_GPIO_CLK, ENABLE );	
		GPIO_InitStructure.GPIO_Pin = shake_DO_GPIO_PIN;			
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			
		
		GPIO_Init(shake_DO_GPIO_PORT, &GPIO_InitStructure);				
		
	}
	#endif
	
}

#if MODE
uint16_t shake_ADC_Read(void)
{
	
	return ADC_GetValue(ADC_CHANNEL, ADC_SampleTime_55Cycles5);
}
#endif

uint16_t shake_GetData(void)
{
	
	#if MODE
	uint32_t  tempData = 0;
	for (uint8_t i = 0; i < shake_READ_TIMES; i++)
	{
		tempData += shake_ADC_Read();
		delay_ms(5);
	}

	tempData /= shake_READ_TIMES;
	return tempData;
	
	#else
	uint16_t tempData;
	tempData = !GPIO_ReadInputDataBit(shake_DO_GPIO_PORT, shake_DO_GPIO_PIN);
	return tempData;
	#endif
}

#if MODE
uint8_t shake_UpdateStatus(void)
{
    uint16_t adcValue = shake_GetData();   
    if (adcValue < SHAKE_AO_THRESHOLD)
    {
         return 1;
    }
    else
    {
         return 0;
    }
}
#endif







