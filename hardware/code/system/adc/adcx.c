#include "adcx.h"

/**
  * @brief  
  */
void ADCx_Init(void)
{
  
    RCC_APB2PeriphClockCmd(ADC_CLK, ENABLE);

   
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;        
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;    
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;       
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;            
    ADC_InitStructure.ADC_NbrOfChannel = 1;                   
    ADC_Init(ADCx, &ADC_InitStructure);                       


    ADC_Cmd(ADCx, ENABLE);


    ADC_ResetCalibration(ADCx);
    while(ADC_GetResetCalibrationStatus(ADCx) == SET);
    ADC_StartCalibration(ADCx);
    while(ADC_GetCalibrationStatus(ADCx) == SET);
}

/**
  * @brief  
  */
u16 ADC_GetValue(uint8_t ADC_Channel,uint8_t ADC_SampleTime)
{
  
    ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime);

    ADC_SoftwareStartConvCmd(ADCx, ENABLE); 
    while(ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET); 
    return ADC_GetConversionValue(ADCx);
}

